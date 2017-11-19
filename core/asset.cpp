#include "asset.hpp"

asset_url::asset_url( const std::string& t, const asset_path& p )
	: m_type( t ),
	m_path( p ) { }

asset_url::asset_url( const std::string & type, const std::string & path ) {
	this->set_type( type );
	this->set_path( path );
}

asset_url::asset_url( const std::string & url ) {
	this->set_type( _get_type( url ) );
	this->set_path( _get_path( url ) );
}

asset_url asset_url::make_complete( const asset_url & url ) const {
	asset_url res( *this );
	res.m_path = res.m_path.make_complete( url.m_path );
	return res;
}

void asset_url::remove_type( void ) {
	m_type.clear();
}

const std::string & asset_url::get_type( void ) const {
	return m_type;
}

const std::string & asset_url::get_name( void ) const {
	return m_path.get_name();
}

void asset_url::set_name( const std::string & v ) {
	m_path.set_name( v );
}

std::string asset_url::get_path( void ) const {
	return m_path.format();
}

std::string asset_url::get_path( char pathsep ) const {
	return m_path.format( pathsep );
}

void asset_url::set_type( const std::string & v ) {
	m_type = _trim( v, SEPARATOR_TOKENS );
}

void asset_url::set_path( const std::string & v ) {
	m_path.set_string( _trim( v, { TYPE_SEPARATOR_TOKEN } ) );
}

std::string asset_url::format( void ) const {
	return m_type + TYPE_SEPARATOR_TOKEN + m_path.format();
}

bool asset_url::has_type( void ) const {
	return !m_type.empty();
}

bool asset_url::is_complete( void ) const {
	return m_path.is_complete();
}

bool asset_url::operator==( const asset_url & o ) const {
	return m_type == o.m_type && m_path == o.m_path;
}

bool asset_url::operator!=( const asset_url & o ) const {
	return m_type != o.m_type || m_path != o.m_path;
}

asset_url::asset_path& asset_url::path()
{
	return m_path;
}

const asset_url::asset_path& asset_url::path() const
{
	return m_path;
}

size_t asset_url::_get_incomplete( const std::string & v ) const {
	return v.find( INCOMPLETE_TOKEN );
}

std::string asset_url::_trim( const std::string & v, const std::string & toks ) const {
	std::string r = v;
	for( size_t i = 0; i < toks.length(); ++i ) {
		size_t sep = r.find( toks[ i ], 0 );
		if( sep != std::string::npos ) {
			r.erase( sep - 1 );
		}
	}
	return r;
}

std::string asset_url::_get_path( const std::string & v ) const {
	size_t sep = v.find( TYPE_SEPARATOR_TOKEN );
	if( sep == std::string::npos ) {
		return v;
	} else {
		return v.substr( sep + 1 );
	}
}

std::string asset_url::_get_type( const std::string & v ) const {
	size_t sep = v.find( TYPE_SEPARATOR_TOKEN );
	if( sep == std::string::npos ) {
		return "";
	} else {
		return v.substr( 0, sep );
	}
}

#include <di_rtlib/define_dependency.hpp>
#include <sys\stat.h>
class asset_type_manager
	: public i_asset_type_manager, public di::component {
private:
	component_dependency( m_logger, i_logger );
	component_dependencies( m_managers, i_asset_manager );
	std::unordered_map< std::string, std::shared_ptr< i_asset_manager > > m_lu_managers;

	virtual void initialize_component( void ) override {
		info( "collecting asset managers..." );
		for( i_asset_manager* ms : m_managers ) {
			auto fit = m_lu_managers.find( ms->get_type() );
			if( fit == m_lu_managers.end() ) {
				m_lu_managers.insert( std::make_pair( ms->get_type(), ms ) );
				sinfo << "\"" << ms->get_type() << "\" manager linked";
			} else {
				swarn << "asset type \"" << ms->get_type() << "\" has multiple manager defined, using only the first one";
			}
		}
	}

public:
	virtual std::shared_ptr< i_asset_manager > get( const std::string& ty ) const override {
		std::shared_ptr< i_asset_manager > r;
		auto fit = m_lu_managers.find( ty );
		if( fit == m_lu_managers.end() ) {
			serror << "requested asset type \"" << ty << "\" has no manager defined";
		} else {
			r = fit->second;
		}
		return r;
	}

	virtual std::vector< asset_manager_ptr > get_all( void ) const override {
		std::vector< asset_manager_ptr > r;
		for( const auto& pp : m_lu_managers ) {
			r.emplace_back( pp.second );
		}
		return r;
	}

	virtual std::vector< std::string > get_types( void ) const override {
		std::vector< std::string > r;
		for( const auto& pp : m_lu_managers ) {
			r.emplace_back( pp.second->get_type() );
		}
		return r;
	}
};

class filesystem_streamer
	: public i_asset_streamer, public di::component {
private:
	// opens a stream to the asset found on the specified url if it exists
	// returns the opened stream if successful
	virtual std::stringstream open_data_stream( const asset_url& url ) override {
		std::stringstream s;
		return s;
	}

	// opens and fully loads the data of the asset, found on the url
	virtual std::string load_data( const asset_url& url ) override {
		std::string r;
		struct stat b;
		const std::string& upath = url_to_path(url);
		stat( upath.c_str(), &b );
		if( b.st_size > 0 ) {
			FILE* f = nullptr;
			fopen_s( &f, upath.c_str(), "rb" );
			r.resize( b.st_size );
			fread_s( &r [ 0 ], b.st_size, sizeof( char ), b.st_size, f );
			fclose( f );
		}
		return r;
	}

	// opens and begins asynchronous loading of the data of the asset, found on the url
	virtual std::future< std::string > load_data_async( const asset_url& url ) override {
		return std::async( &filesystem_streamer::load_data, this, url );
	}

	// returns true if the asset exists and is openable
	virtual bool check_asset( const asset_url& url ) override {
		struct stat buf;
		return ( stat( url_to_path( url ).c_str(), &buf ) == 0 );
	}

	std::string url_to_path( const asset_url& u ) {
		std::string p = u.get_path();
		for( size_t i = 0; i < p.length(); ++i ) {
			if( p [ i ] == PATH_SEPARATOR_TOKEN ) {
				p [ i ] = '/';
			}
		}
		return p;
	}
};

class text_file_manager
	: public asset_manager_base {
private:
	// Returns the type string that identifies the 
	// asset type, managed by the manager implementation
	virtual const char* get_type( void ) const override {
		return "text";
	}

	// Creates a new asset with the type of the asset
	// that the manager implementation manages
	// This is called when inserting new assets during initialization
	virtual asset_ptr create_asset( const asset_url& url ) override {
		return std::make_shared< text_asset>( url );
	}
};

#include <di_rtlib/register_class.hpp>
register_class( text_file_manager );
register_class( filesystem_streamer );
register_class( asset_type_manager );

asset_url::asset_path::asset_path( const std::string & p ) {
	this->set_string( p );
}

asset_url::asset_path & asset_url::asset_path::set_string( const std::string & p ) {
	m_path.clear();
	size_t l = 0;
	size_t i = 0;
	for( ; i < p.size(); ++i ) {
		if( p[ i ] == PATH_SEPARATOR_TOKEN ) {
			m_path.emplace_back( std::move( p.substr( l, i - l ) ) );
			l = i + 1;
		}

		if( p[ i ] == INCOMPLETE_TOKEN ) {
			m_complete = false;
			m_incompleteness = i;
		}
	}
	m_path.emplace_back( std::move( p.substr( l, i - l ) ) );
	return *this;
}

bool asset_url::asset_path::is_complete( void ) const {
	return m_complete;
}

size_t asset_url::asset_path::get_incomplete_index( void ) const {
	return m_incompleteness;
}

std::string asset_url::asset_path::format( void ) const {
	return this->format( PATH_SEPARATOR_TOKEN );
}

std::string asset_url::asset_path::format( char pathsep ) const {
	std::string r;
	if( !m_path.empty() ) {
		r = m_path.front();
		for( size_t i = 1; i < m_path.size(); ++i ) {
			r += pathsep + m_path[ i ];
		}
	}
	return r;
}

const std::string & asset_url::asset_path::get_name( void ) const {
	return m_path.back();
}

void asset_url::asset_path::set_name( const std::string & v ) {
	m_path.back() = v;
}

asset_url::asset_path asset_url::asset_path::make_complete( const asset_path & p ) const {
	asset_path res( *this );
	if( !m_complete ) {
		std::string s = this->format();
		std::string n = p.format();
		s.replace( m_incompleteness, 1, n );
		res.set_string( s );
		res.m_complete = true;
		res.m_incompleteness = std::string::npos;
	}
	return res;
}

asset_url::asset_path& asset_url::asset_path::insert_front_part(const std::string& part)
{
	m_path.insert(m_path.begin(), part);
	return *this;
}

asset_url::asset_path & asset_url::asset_path::insert_back_part(const std::string & part)
{
	m_path.push_back(part);
	return *this;
}

bool asset_url::asset_path::operator==( const asset_path & o ) const {
	bool r = m_path.size() == o.m_path.size();
	if( r ) {
		for( size_t i = 0; i < m_path.size(); ++i ) {
			if( m_path[ i ] != o.m_path[ i ] ) {
				r = false;
				break;
			}
		}
	}
	return r;
}

bool asset_url::asset_path::operator!=( const asset_path & o ) const {
	bool r = m_path.size() != o.m_path.size();
	if( !r ) {
		for( size_t i = 0; i < m_path.size(); ++i ) {
			if( m_path[ i ] != o.m_path[ i ] ) {
				r = true;
				break;
			}
		}
	}
	return r;
}

std::ostream & operator<<( std::ostream & op, const asset_url & url ) {
	op << url.format();
	return op;
}

asset_params::asset_params( const std::string & source )
	: m_source( source ) { }

bool asset_params::parse( void ) {
	std::string tmp;
	std::stringstream s( m_source );
	while( !s.eof() ) {
		s >> tmp;
		size_t eq = tmp.find( '=' );
		if( eq == std::string::npos ) {
			std::string& nv = m_params[ tmp ];
			s >> tmp;
			if( tmp == "=" ) {
				s >> nv;
			} else {
				nv = tmp.substr( 1 );
			}
		} else {
			if( tmp.back() == '=' ) {
				s >> m_params[ tmp.substr( 0, tmp.size() - 1 ) ];
			} else {
				m_params[ tmp.substr( 0, eq ) ] = tmp.substr( eq + 1 );
			}
		}
	}
	return true;
}

const std::unordered_map<std::string, std::string>& asset_params::get_params( void ) const {
	return m_params;
}

std::string asset_params::get_value( const std::string & name ) const {
	std::string r;
	auto fit = m_params.find( name );
	if( fit != m_params.end() ) {
		r = fit->second;
	}
	return r;
}

void asset_params::set_value( const std::string & name, const std::string & value ) {
	m_params[ name ] = value;
}

void asset_manager_base::_insert_asset( const asset_url & url ) {
	auto fit = m_asset_map.find( url );
	asset_url tmp = url;
	unsigned int c = 0;
	while( fit != m_asset_map.end() ) {
		tmp.set_name( tmp.get_name() + std::to_string( c++ ) );
		fit = m_asset_map.find( tmp );
	}
	asset_ptr nass = this->create_asset( tmp );
	nass->get_state().exchange( asset_state::initializing );
	std::string formattedurl = url.format();
	formattedurl += ".meta";
	asset_url metaurl( formattedurl );
	if( m_streamer->check_asset( metaurl ) ) {
		asset_params prs( m_streamer->load_data( metaurl ) );
		if( prs.parse() ) {
			for( const auto& pp : prs.get_params() ) {
				nass->set_load_param( pp.first, pp.second );
				sinfo << "asset \"" << url.get_name() << "\" param: " << pp.first << " value: " << pp.second;
			}
		}
	}
	m_asset_map[ tmp ] = nass;
	nass->get_state().exchange( asset_state::initialized );
	sinfo << "new asset with url \"" << tmp << "\" inserted";
	if( tmp != url ) {
		swarn << "the original url was \"" << url << "\", but got mangled due to name collision";
	}
}

void asset_manager_base::_load_asset( asset_ptr a ) {
	asset_state exp = asset_state::initialized;
	if( a->get_state().compare_exchange_strong( exp, asset_state::loading ) ) {
		sinfo << "loading asset \"" << a->get_path() << "\"";
		a->pre_load();
		std::string error;
		if( a->load( m_streamer->load_data( a->get_path() ), error ) ) {
			a->post_load();
			a->get_state().exchange( asset_state::loaded );
		} else {
			a->get_state().exchange( asset_state::initialized );
			serror << "asset with url \"" << a->get_path() << "\" failed to load:\n\t\t" << error;
		}
	} else {
		swarn << "asset with url \"" << a->get_path() << "\" is already loading or loaded";
	}
}

void asset_manager_base::_unload_asset( asset_ptr a ) {
	asset_state exp = asset_state::loaded;
	if( a->get_state().compare_exchange_strong( exp, asset_state::unloading ) ) {
		sinfo << "unloading asset \"" << a->get_path() << "\"";
		a->pre_unload();
		std::string error;
		if( a->unload( error ) ) {
			a->post_unload();
			a->get_state().exchange( asset_state::initialized );
		} else {
			a->get_state().exchange( asset_state::loaded );
			serror << "asset with url \"" << a->get_path() << "\" failed to unload:\n\t\t" << error;
		}
	} else {
		swarn << "asset with url \"" << a->get_path() << "\" is not loaded";
	}
}

void asset_manager_base::_resolve_asset( const asset_url & aurl ) { 
	if( aurl.get_type() == this->get_type() ) {
		const std::list< asset_url >& final_urls = _possible_matches(aurl, m_search_urls.get_values());
		for( const asset_url& a : final_urls ) {
			if( m_streamer->check_asset( a ) ) {
				_insert_asset( a );
			} else {
				swarn << "asset with url \"" << a << "\" does not match any asset with current settings";
			}
		}
	} else {
		swarn << "asset with url \"" << aurl << "\" has type mismatch, gets ignored";
	}
}

void asset_manager_base::_init( void ) {
	for( const std::string& url : m_assets ) {
		_resolve_asset( asset_url( url ) );
	}
}

void asset_manager_base::_create_loader_thread( asset_ptr a, const i_asset_listener * l ) {
	std::thread(
		[ this ]( asset_ptr a, const i_asset_listener* l ) {
		_load_asset( a );
		if( l != nullptr ) {
			l->load_ready( a );
		}
	}, a, l ).detach();
}

std::list<asset_url> asset_manager_base::_possible_matches(const asset_url& base, const string_vector& search)
{
	std::list<asset_url> result;

	if (base.is_complete()) {
		result.push_back(base);
	}

	for (const std::string& sp : search) {
		if (!sp.empty()) {
			if (base.is_complete()) {
				asset_url nurl = base;
				nurl.path().insert_front_part(sp);
				result.push_back(nurl);
			}
			else {
				result.push_back(base.make_complete(asset_url(sp)));
			}
		}
	}

	return move(result);
}

std::shared_ptr<i_asset> asset_manager_base::load_asset( const asset_url & url ) {
	std::shared_ptr< i_asset > r = this->get_asset( url );
	if( r ) {
		_load_asset( r );
	} else {
		swarn << "asset with url " << url << " was not found as a created asset";
	}
	return r;
}

std::shared_ptr<i_asset> asset_manager_base::load_asset( const std::string & name ) {
	std::shared_ptr< i_asset > r = this->get_asset( name );
	if( r ) {
		_load_asset( r );
	} else {
		swarn << "asset with name " << name << " was not found as a created asset";
	}
	return r;
}

asset_ptr asset_manager_base::load_asset( const asset_url & url, const i_asset_listener * l ) {
	asset_ptr r = this->get_asset( url );
	if( r ) {
		_create_loader_thread( r, l );
	} else {
		swarn << "asset with url " << url << " was not found as a created asset";
	}
	return r;
}

asset_ptr asset_manager_base::load_asset( const std::string & name, const i_asset_listener * l ) {
	asset_ptr r = this->get_asset( name );
	if( r ) {
		_create_loader_thread( r, l );
	} else {
		swarn << "asset with name \"" << name << "\" was not found as a created asset";
	}
	return r;
}

void asset_manager_base::unload_asset( const asset_url & url ) {
	asset_ptr a = this->get_asset( url );
	if( a ) {
		_unload_asset( a );
	} else {
		swarn << "asset with url \"" << url << "\" was not found as a created asset";
	}
}

void asset_manager_base::unload_asset( const std::string & name ) { 
	asset_ptr a = this->get_asset( name );
	if( a ) {
		_unload_asset( a );
	} else {
		swarn << "asset with name \"" << name << "\" was not found as a created asset";
	}
}

void asset_manager_base::unload_unreferenced( void ) { 
	for( const auto& pp : m_asset_map ) {
		if( pp.second.use_count() == manager_ref_list::manager_ref_count ) {
			_unload_asset( pp.second );
		}
	}
}

std::shared_ptr<i_asset> asset_manager_base::get_asset(const asset_url& url) {
	std::shared_ptr< i_asset > r;

	const auto& alternatives = _possible_matches(url, m_search_urls.get_values());
	auto fit = m_asset_map.end();
	for (auto alternative = alternatives.begin(); alternative != alternatives.end()
		&& fit == m_asset_map.end(); ++alternative)
		fit = m_asset_map.find(*alternative);

	if (fit == m_asset_map.end())
		swarn << "asset at \"" << url << "\" was not found as a preinitialized asset";
	else
		r = fit->second;

	return r;
}

std::shared_ptr<i_asset> asset_manager_base::get_asset( const std::string & name ) {
	std::shared_ptr< i_asset > r;
	for( const auto& assp : m_asset_map ) {
		if( assp.first.get_name() == name ) {
			r = assp.second;
			break;
		}
	}
	return r;
}

void asset_manager_base::initialize_component( void ) { 
	_init();
}

asset_base::asset_base( const asset_url & url )
	: m_path( url ) { }

std::atomic<asset_state>& asset_base::get_state( void ) {
	return m_state;
}

asset_url asset_base::get_path( void ) const {
	return m_path;
}

void asset_base::pre_load( void ) { }

bool asset_base::load( const std::string & data, std::string & err ) {
	return true;
}

void asset_base::post_load( void ) { }

void asset_base::pre_unload( void ) { }

bool asset_base::unload( std::string & err ) {
	return true;
}

void asset_base::post_unload( void ) { }

void asset_base::set_load_param( const std::string & par, const std::string & val ) {
	m_params.set_value( par, val );
}

std::string asset_base::get_load_param( const std::string & par ) const {
	return m_params.get_value( par );
}

text_asset::text_asset( const asset_url & url )
	: asset_base( url ) { }

const std::string & text_asset::get_text( void ) const {
	return m_text;
}

bool text_asset::load( const std::string & data, std::string & err ) {
	m_text = data;
	return true;
}