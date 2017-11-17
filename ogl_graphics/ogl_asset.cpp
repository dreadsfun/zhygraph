#include "ogl_asset.hpp"
namespace asset {

// texture asset

texture::texture( const asset_url& url )
	: asset_base( url ) { }

GLuint texture::get_name( void ) const {
	return m_gl_name;;
}

void texture::upload_data( void ) {
	if( !m_data.empty() ) {
		glBindTexture( GL_TEXTURE_2D, m_gl_name );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &m_data[ 0 ] );
		_set_filter_mode();
		_set_wrap_mode();
		_set_aniso();
		if( this->get_load_param( "generate_mipmap" ) == "true" ) {
			glGenerateMipmap( GL_TEXTURE_2D );
		}
		m_data.clear();
		m_data.swap( decltype( m_data )( ) );
	}
}

void texture::bind( unsigned int unit ) {
	glActiveTexture( GL_TEXTURE0 + unit );
	this->upload_data();
}

bool texture::load( const std::string & data, std::string & err ) {
	bool r = false;
	unsigned int error = lodepng::decode( m_data, m_width, m_height,
		reinterpret_cast< const unsigned char* >( data.c_str() ), data.size() );

	if( error == 0 ) {
		glGenTextures( 1, &m_gl_name );
		r = true;
	} else {
		err = "image decoder error: ";
		err.append( lodepng_error_text( error ) );
	}
	return r;
}

bool texture::unload( std::string & err ) {
	glDeleteTextures( 1, &m_gl_name );
	m_data.clear();
	return true;
}

void texture::_set_wrap_mode( void ) const {
	if( this->get_load_param( "wrap_mode" ) == "clamp" ) {
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
	} else {
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	}
}

void texture::_set_filter_mode( void ) const {
	std::string fm = this->get_load_param( "filter_mode" );
	if( fm == "point" ) {
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	}

	if( fm == "bilinear" ) {
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	}

	if( fm == "trilinear" ) {
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	}
}

void texture::_set_aniso( void ) const {
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, m_params.get_< int >( "aniso_level" ) );
}


// mesh asset

mesh::mesh( const asset_url & url )
	: asset_base( url ) { }

size_t mesh::get_submesh_count( void ) const {
	return m_indices.size();
}

void mesh::draw_submesh( size_t i ) {
	if( i < this->get_submesh_count() ) {
		_create_vaos();
		glBindVertexArray( m_buffer_names.vaos[ i ] );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_buffer_names.indices[ i ] );
		glDrawElements( m_topologies[ i ], m_indices[ i ].size(), GL_UNSIGNED_INT, nullptr );
	}
}

bool mesh::load( const std::string & data, std::string & err ) {
	using namespace Assimp;

	Importer imp;
	const aiScene* sc = imp.ReadFileFromMemory( &data[ 0 ], data.size(),
		aiProcess_CalcTangentSpace
		| aiProcess_Triangulate
		| aiProcess_SortByPType
	);

	if( sc == nullptr ) {
		err = imp.GetErrorString();
		return false;
	}

	if( !sc->HasMeshes() ) {
		err = "no mesh was found in mesh data";
		return false;
	}

	unsigned int ind_offset = 0;
	m_indices.resize( sc->mNumMeshes );
	m_topologies.resize( sc->mNumMeshes );

	glm::vec3 cminpoint;
	glm::vec3 cmaxpoint;

	if (sc->mNumMeshes > 0 && sc->mMeshes[0]->mNumVertices > 0) {
		const auto& cp = sc->mMeshes[0]->mVertices[0];
		cmaxpoint = cminpoint = glm::vec3(cp.x, cp.y, cp.z);
	}

	for( unsigned int i = 0; i < sc->mNumMeshes; ++i ) {
		aiMesh* cmesh = sc->mMeshes[ i ];

		if( !cmesh->HasPositions() ) {
			continue;
		}
		if( !cmesh->HasFaces() ) {
			continue;
		}

		// top_mult (topology multiplier) is the number of vertices, that the current
		// type of face contains. default is 3, as the most common situation is to have
		// triangles in the mesh, then check if it consists of lines or points yet
		unsigned int top_mult = 3;
		m_topologies[ i ] = GL_TRIANGLES;
		if( cmesh->mPrimitiveTypes & aiPrimitiveType::aiPrimitiveType_LINE ) {
			top_mult = 2;
			m_topologies[ i ] = GL_LINES;
		} else if( cmesh->mPrimitiveTypes & aiPrimitiveType::aiPrimitiveType_POINT ) {
			top_mult = 1;
			m_topologies[ i ] = GL_POINTS;
		}
		// the number of indices required for this mesh is numberoffaces*topologymultiplier,
		// so allocate that much space for the ith indice vector
		m_indices[ i ].resize( cmesh->mNumFaces * top_mult );
		// copy offset indice data of the current mesh
		for( unsigned int iind = 0; iind < cmesh->mNumFaces; ++iind ) {
			for( unsigned int find = 0; find < cmesh->mFaces[ iind ].mNumIndices; ++find ) {
				m_indices[ i ][ iind * cmesh->mFaces[ iind ].mNumIndices + find ] = cmesh->mFaces[ iind ].mIndices[ find ] + ind_offset;
			}
		}

		// allocate vertice count space for vertex position vector
		m_positions.resize( m_positions.size() + cmesh->mNumVertices );
		// copy the position data of the current mesh
		for( unsigned int vind = ind_offset; vind < ( ind_offset + cmesh->mNumVertices ); ++vind ) {
			m_positions[ vind ][ 0 ] = cmesh->mVertices[ vind - ind_offset ].x;
			m_positions[ vind ][ 1 ] = cmesh->mVertices[ vind - ind_offset ].y;
			m_positions[ vind ][ 2 ] = cmesh->mVertices[ vind - ind_offset ].z;

			cminpoint = glm::min(cminpoint, m_positions[vind]);
			cmaxpoint = glm::max(cmaxpoint, m_positions[vind]);
		}

		// allocate vertice count space for vertex texture coordinate data and copy the loaded data
		// if this mesh has texture coordinate data associated with it
		if( cmesh->HasTextureCoords( 0 ) ) {
			m_uvs.resize( m_uvs.size() + cmesh->mNumVertices );
			size_t uv_size = m_uvs.size();
			for( unsigned int uvcind = ind_offset; uvcind < uv_size; ++uvcind ) {
				m_uvs[ uvcind ][ 0 ] = cmesh->mTextureCoords[ 0 ][ uvcind - ind_offset ].x;
				m_uvs[ uvcind ][ 1 ] = cmesh->mTextureCoords[ 0 ][ uvcind - ind_offset ].y;
			}
		}


		// allocate vertice count space for vertex normal data and copy the loaded data
		// if this mesh has normal data associated with it
		if( cmesh->HasNormals() ) {
			m_normals.resize( m_normals.size() + cmesh->mNumVertices );
			size_t norm_size = m_normals.size();
			for( unsigned int nind = ind_offset; nind < norm_size; ++nind ) {
				m_normals[ nind ][ 0 ] = cmesh->mNormals[ nind - ind_offset ].x;
				m_normals[ nind ][ 1 ] = cmesh->mNormals[ nind - ind_offset ].y;
				m_normals[ nind ][ 2 ] = cmesh->mNormals[ nind - ind_offset ].z;
			}
		}

		// allocate vertice count space for vertex tangent data and copy the loaded data
		// if this mesh has tangent data associated with it
		if( cmesh->HasTangentsAndBitangents() ) {
			m_tangents.resize( m_tangents.size() + cmesh->mNumVertices );
			size_t tan_size = m_tangents.size();
			for( unsigned int tind = ind_offset; tind < tan_size; ++tind ) {
				m_tangents[ tind ][ 0 ] = cmesh->mTangents[ tind - ind_offset ].x;
				m_tangents[ tind ][ 1 ] = cmesh->mTangents[ tind - ind_offset ].y;
				m_tangents[ tind ][ 2 ] = cmesh->mTangents[ tind - ind_offset ].z;
			}

			m_bitangents.resize( m_bitangents.size() + cmesh->mNumVertices );
			size_t bitan_size = m_bitangents.size();
			for( unsigned int btind = ind_offset; btind < bitan_size; ++btind ) {
				m_bitangents[ btind ][ 0 ] = cmesh->mBitangents[ btind - ind_offset ].x;
				m_bitangents[ btind ][ 1 ] = cmesh->mBitangents[ btind - ind_offset ].y;
				m_bitangents[ btind ][ 2 ] = cmesh->mBitangents[ btind - ind_offset ].z;
			}
		}

		//if( cmesh->HasBones() ) {
		//	vector4i def_bi;
		//	// initialize the new index elements with all values of -1, this
		//	// signals that the bone index was not set up yet
		//	def_bi.data[ 0 ] = def_bi.data[ 1 ] = def_bi.data[ 2 ] = def_bi.data[ 3 ] = -1;
		//	m_bone_indices.resize( m_bone_indices.size() + cmesh->mNumVertices, def_bi );
		//	m_bone_weights.resize( m_bone_weights.size() + cmesh->mNumVertices );

		//	// store the bone names
		//	for( unsigned int i = 0; i < cmesh->mNumBones; ++i ) {
		//		m_bone_name_index_map[ cmesh->mBones[ i ]->mName.C_Str() ].m_bone = cmesh->mBones[ i ];
		//	}

		//	_fill_bone_transforms( sc->mRootNode, nullptr );

		//	for( const pair< string, bone_info >& bone_pr : m_bone_name_index_map ) {
		//		for( unsigned int i = 0; i < bone_pr.second.m_bone->mNumWeights; ++i ) {
		//			// search for a bone index that was not set up yet
		//			// i.e. its value is -1

		//			for( unsigned int j = 0; j < 4; ++j ) {
		//				const aiVertexWeight& c_weight_data = bone_pr.second.m_bone->mWeights[ i ];
		//				int& c_bone_index_ref = m_bone_indices[ c_weight_data.mVertexId + ind_offset ].data[ j ];
		//				// if the bone index and weight were not set yet, then set them..
		//				if( c_bone_index_ref == -1 ) {
		//					c_bone_index_ref = bone_pr.second.m_index;
		//					m_bone_weights[ c_weight_data.mVertexId + ind_offset ].data[ j ] = c_weight_data.mWeight;
		//					break;
		//				}

		//				// if all of the indices was already set, then simply ignore the new one
		//				// this is the constraint on the number of bones affecting a single vertex ( 4 )
		//			}
		//		}
		//	}
		//}

		// offset the indices stored in the indice array, loaded by assimp
		// as assimp has per-mesh position arrays, but we store one position
		// array for every mesh loaded here
		ind_offset += cmesh->mNumVertices;
	}

	auto csum = cminpoint + cmaxpoint;
	auto cmid = glm::vec3(csum.x / 2, csum.y / 2, csum.z / 2);
	mboundingvolume = aabb(cmid, cmid - cminpoint );

	return true;
}

void mesh::post_load( void ) {
	if( !m_positions.empty() ) {
		glGenBuffers( 1, &m_buffer_names.position );
		glBindBuffer( GL_ARRAY_BUFFER, m_buffer_names.position );
		glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * 3 * m_positions.size(), &m_positions[ 0 ], GL_STATIC_DRAW );
		m_positions.clear();
	}

	if( !m_normals.empty() ) {
		glGenBuffers( 1, &m_buffer_names.normal );
		glBindBuffer( GL_ARRAY_BUFFER, m_buffer_names.normal );
		glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * 3 * m_normals.size(), &m_normals[ 0 ], GL_STATIC_DRAW );
		m_normals.clear();
	}

	if( !m_tangents.empty() ) {
		glGenBuffers( 1, &m_buffer_names.tangent );
		glBindBuffer( GL_ARRAY_BUFFER, m_buffer_names.tangent );
		glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * 3 * m_tangents.size(), &m_tangents[ 0 ], GL_STATIC_DRAW );
		m_tangents.clear();
	}

	if( !m_bitangents.empty() ) {
		glGenBuffers( 1, &m_buffer_names.bitangent );
		glBindBuffer( GL_ARRAY_BUFFER, m_buffer_names.bitangent );
		glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * 3 * m_bitangents.size(), &m_bitangents[ 0 ], GL_STATIC_DRAW );
		m_bitangents.clear();
	}

	if( !m_uvs.empty() ) {
		glGenBuffers( 1, &m_buffer_names.uv );
		glBindBuffer( GL_ARRAY_BUFFER, m_buffer_names.uv );
		glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * 2 * m_uvs.size(), &m_uvs[ 0 ], GL_STATIC_DRAW );
		m_uvs.clear();
	}

	m_buffer_names.indices.resize( m_indices.size() );
	for( size_t i = 0; i < m_indices.size(); ++i ) {
		if( !m_indices[ i ].empty() ) {
			GLuint& cind = m_buffer_names.indices[ i ];
			glGenBuffers( 1, &cind );
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, cind );
			glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( unsigned int ) * m_indices[ i ].size(), &m_indices[ i ][ 0 ], GL_STATIC_DRAW );
		}
	}

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

bool mesh::unload( std::string & err ) {
	glDeleteBuffers( 5 + m_buffer_names.indices.size(), &m_buffer_names.position );
	glDeleteVertexArrays( m_buffer_names.vaos.size(), &m_buffer_names.vaos[ 0 ] );
	memset( &m_buffer_names.position, 0, sizeof( GLuint ) * 5 );
	m_buffer_names.indices.clear();
	m_buffer_names.vaos.clear();
	return true;
}

const aabb& mesh::boundingvolume() const
{
	return mboundingvolume;
}

void mesh::_create_vaos( void ) {
	if( m_ns_obj ) return;
	m_buffer_names.vaos.resize( m_indices.size() );
	for( size_t i = 0; i < m_indices.size(); ++i ) {

		if( !m_indices[ i ].empty() ) {
			GLuint& cvao = m_buffer_names.vaos[ i ];
			glGenVertexArrays( 1, &cvao );
			glBindVertexArray( cvao );

			glBindBuffer( GL_ARRAY_BUFFER, m_buffer_names.position );
			glEnableVertexAttribArray( 0 );
			glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

			glBindBuffer( GL_ARRAY_BUFFER, m_buffer_names.uv );
			glEnableVertexAttribArray( 1 );
			glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, nullptr );

			glBindBuffer( GL_ARRAY_BUFFER, m_buffer_names.normal );
			glEnableVertexAttribArray( 2 );
			glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

			glBindBuffer( GL_ARRAY_BUFFER, m_buffer_names.tangent );
			glEnableVertexAttribArray( 3 );
			glVertexAttribPointer( 3, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

			glBindBuffer( GL_ARRAY_BUFFER, m_buffer_names.bitangent );
			glEnableVertexAttribArray( 4 );
			glVertexAttribPointer( 4, 3, GL_FLOAT, GL_FALSE, 0, nullptr );
		}
	}
	m_ns_obj = true;
}

shader::shader( const asset_url & url )
	: asset_base( url ) { }

GLuint shader::get_name( void ) const {
	return m_gl_name;
}

bool shader::load( const std::string & data, std::string & err ) {
	bool r = false;
	try {
		m_gl_name = glCreateShader( string_to_shader_type( this->get_load_param( "shader_type" ) ) );
		const char* src = data.c_str();
		GLint lt = data.length();
		glShaderSource( m_gl_name, 1, &src, &lt );
		glCompileShader( m_gl_name );

		GLint ccst = 0;
		glGetShaderiv( m_gl_name, GL_COMPILE_STATUS, &ccst );

		if( ccst != GL_TRUE ) {
			GLint llt = 0;
			glGetShaderiv( m_gl_name, GL_INFO_LOG_LENGTH, &llt );
			err.resize( llt );
			glGetShaderInfoLog( m_gl_name, llt, nullptr, &err[ 0 ] );
			glDeleteShader( m_gl_name );
			m_gl_name = 0;
			err.insert( 0, "failed to compile shader: " );
		} else {
			r = true;
		}
	} catch( const std::out_of_range& ) {
		err = "failed to create gl shader, provided type was \"" + this->get_load_param( "shader_type" ) + "\"";
	} catch( const std::exception& e ) {
		err = e.what();
	}
	return r;
}

bool shader::unload( std::string & err ) {
	glDeleteShader( m_gl_name );
	return true;
}

GLenum shader::string_to_shader_type( const std::string & st ) {
	static const std::unordered_map< std::string, GLenum > names = {
		{ "vertex", GL_VERTEX_SHADER },
		{ "fragment", GL_FRAGMENT_SHADER }
	};
	return names.at( st );
}
}

#include <core/windowing.hpp>
#include <core/multi_thread.hpp>
#include <core/graphics.hpp>
namespace asset {
class resource_context_handle
	: public di::component {
	friend class rch_initializer;
private:
	component_dependency( m_windowing, i_windowing_library );
	component_dependency( m_resource_context, i_graphics_context );
	component_dependency( m_main_context, i_graphics_context );
	component_dependency( m_logger, i_logger );

	bool m_available { false };
	multi_thread m_worker;

	static resource_context_handle* instance;

public:
	static bool is_available( void ) {
		return instance->m_available;
	}

	static multi_thread& get_worker( void ) {
		return instance->m_worker;
	}

	static bool is_main_thread( void ) {
		return instance->m_windowing->get_context_guard()->is_main_thread();
	}

private:
	virtual void initialize_component( void ) override {
		if( instance == nullptr ) {
			instance = this;
		}
	}

	void _init_context( void ) {
		if( m_resource_context->create( m_windowing->get_render_window(), m_main_context ) ) {
			m_worker.push_job( []( i_context_guard* g, i_graphics_context* rctx ) { 
				g->make_current( rctx );
				return 0;
			}, m_windowing->get_context_guard(), m_resource_context.get() );
			m_available = true;
		} else {
			error( "failed to create ogl resource context, asynchronous resource loading is not possible" );
		}
	}
};

class rch_initializer
	: public i_initialization_end_listener, public di::component {
private:
	component_dependency( m_owner, resource_context_handle );
private:
	virtual void respond( void ) {
		m_owner->_init_context();
	}
};

resource_context_handle* resource_context_handle::instance = nullptr;
}

namespace asset {
class ogl_asset_manager_base
	: public asset_manager_base {
private:
	template< typename T >
	asset_ptr _t_load_asset( const T& id ) {
		asset_ptr r;
		if( resource_context_handle::is_available() ) {
			auto h = resource_context_handle::get_worker().push_job( [ this, &id ] {
				return asset_manager_base::load_asset( id );
			} );
			h->wait();
			r = h->get_result();
		} else if( resource_context_handle::is_main_thread() ) {
			r = asset_manager_base::load_asset( id );
		} else {
			serror << "when ogl resource context is not available, only the main thread can load resources\n\ttried to load asset \"" << id << "\"";
		}
		return r;
	}

	template< typename T >
	asset_ptr _t_load_asset_async( const T& id, const i_asset_listener* l ) {
		asset_ptr r = this->get_asset( id );
		if( r ) {
			if( resource_context_handle::is_available() ) {
				resource_context_handle::get_worker().push_job( [ this, &r, l ] {
					this->_load_asset( r );
					if( l != nullptr ) {
						l->load_ready( r );
					}
					return 0;
				} );
			} else {
				serror << "asynchronous load of ogl asset \"" << id << "\" is not possible, due to the unavailability of the resource context";
			}
		} else {
			swarn << "asset with identifier \"" << id << "\" was not found as a created asset";
		}
		return r;
	}

	virtual asset_ptr load_asset( const asset_url& url ) {
		return _t_load_asset( url );
	}

	virtual asset_ptr load_asset( const std::string& name ) {
		return _t_load_asset( name );
	}

	virtual asset_ptr load_asset( const asset_url& url, const i_asset_listener* l ) {
		return _t_load_asset_async( url, l );
	}

	virtual asset_ptr load_asset( const std::string& name, const i_asset_listener* l ) {
		return _t_load_asset_async( name, l );
	}
};
}

namespace asset {
class texture_manager
	: public ogl_asset_manager_base {
private:
	virtual const char* get_type( void ) const override {
		return "texture";
	}

	virtual asset_ptr create_asset( const asset_url& url ) override {
		return std::make_shared< texture >( url );
	}
};
}

namespace asset {
class mesh_manager
	: public ogl_asset_manager_base {
private:
	virtual const char* get_type( void ) const override {
		return "mesh";
	}

	virtual asset_ptr create_asset( const asset_url& url ) override {
		return std::make_shared< mesh >( url );
	}
};
}

namespace asset {
class shader_manager
	: public ogl_asset_manager_base {
private:
	virtual const char* get_type( void ) const override {
		return "shader";
	}

	virtual asset_ptr create_asset( const asset_url& url ) override {
		return std::make_shared< shader >( url );
	}
};
}

#include <di_rtlib/register_class.hpp>
namespace asset {
register_class( rch_initializer );
register_class( resource_context_handle );
register_class( texture_manager );
register_class( mesh_manager );
register_class( shader_manager );
}