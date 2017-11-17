#pragma once
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <GL\glew.h>
#include <core/asset.hpp>
#include <core/aabb.hpp>
#include "lodepng.h"
namespace asset {
class texture
	: public asset_base {
private:
	GLuint m_gl_name;
	std::vector< unsigned char > m_data;
	unsigned int m_width;
	unsigned int m_height;

public:
	texture( const asset_url& url );
	GLuint get_name( void ) const;
	void upload_data( void );
	void bind( unsigned int unit );

private:
	virtual bool load( const std::string& data, std::string& err ) override;
	virtual bool unload( std::string& err ) override;
	void _set_wrap_mode( void ) const;
	void _set_filter_mode( void ) const;
	void _set_aniso( void ) const;
};

typedef std::shared_ptr< texture > texture_ptr;
}

#include <glm\glm.hpp>
namespace asset {
class mesh
	: public asset_base {
private:
	std::vector< glm::vec3 > m_positions;
	std::vector< glm::vec2 > m_uvs;
	std::vector< glm::vec3 > m_normals;
	std::vector< glm::vec3 > m_tangents;
	std::vector< glm::vec3 > m_bitangents;
	std::vector< std::vector< GLuint > > m_indices;
	std::vector< GLenum > m_topologies;

	// are non-shareable objects created?
	bool m_ns_obj { false };

	struct {
		GLuint position { 0 };
		GLuint uv { 0 };
		GLuint normal { 0 };
		GLuint tangent { 0 };
		GLuint bitangent { 0 };
		std::vector< GLuint > indices;
		std::vector< GLuint > vaos;
	} m_buffer_names;

	aabb mboundingvolume;

public:
	mesh( const asset_url& url );
	size_t get_submesh_count( void ) const;
	void draw_submesh( size_t i );
	virtual bool load( const std::string& data, std::string& err ) override;
	virtual void post_load( void ) override;
	virtual bool unload( std::string& err ) override;
	const aabb& boundingvolume() const;

private:
	void _create_vaos( void );
};

typedef std::shared_ptr< mesh > mesh_ptr;
}

namespace asset {
class shader
	: public asset_base {
private:
	GLuint m_gl_name;

public:
	shader( const asset_url& url );
	GLuint get_name( void ) const;
	virtual bool load( const std::string& data, std::string& err ) override;
	virtual bool unload( std::string& err ) override;
	static GLenum string_to_shader_type( const std::string& st );
};

typedef std::shared_ptr< shader > shader_ptr;
}