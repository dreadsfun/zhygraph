#pragma once
#include <string>
#include <vector>
#include "export.hpp"
#define TYPE_SEPARATOR_TOKEN '@'
#define PATH_SEPARATOR_TOKEN '.'
#define SEPARATOR_TOKENS std::string( "@." )
#define INCOMPLETE_TOKEN '*'
class asset_url {
#pragma region types
private:
	class asset_path {
	private:
		typedef std::vector< std::string > path_vector;
		typedef path_vector::const_iterator path_iterator;

		path_vector m_path;
		bool m_complete { true };
		size_t m_incompleteness { std::string::npos };
		
	public:
		asset_path( void ) = default;
		asset_path( const std::string& p );
		asset_path& set_string( const std::string& p );
		bool is_complete( void ) const;
		size_t get_incomplete_index( void ) const;
		std::string format( void ) const;
		const std::string& get_name( void ) const;
		void set_name( const std::string& v );
		asset_path make_complete( const asset_path& p ) const;
		bool operator == ( const asset_path& o ) const;
		bool operator != ( const asset_path& o ) const;
	};
#pragma endregion

#pragma region data members
private:
	std::string m_type;
	asset_path m_path;
#pragma endregion

#pragma region member functions
private:
	asset_url( const std::string& t, const asset_path& p );

public:
	CORE_SHARED asset_url( void ) = default;
	CORE_SHARED asset_url( const std::string& type, const std::string& path );
	explicit CORE_SHARED asset_url( const std::string& url );
	CORE_SHARED asset_url make_complete( const asset_url& url ) const;
	CORE_SHARED void remove_type( void );
	CORE_SHARED const std::string& get_type( void ) const;
	CORE_SHARED const std::string& get_name( void ) const;
	CORE_SHARED void set_name( const std::string& v );
	CORE_SHARED std::string get_path( void ) const;
	CORE_SHARED void set_type( const std::string& v );
	CORE_SHARED void set_path( const std::string& v );
	CORE_SHARED std::string format( void ) const;
	CORE_SHARED bool has_type( void ) const;
	CORE_SHARED bool is_complete( void ) const;
	CORE_SHARED bool operator == ( const asset_url& o ) const;
	CORE_SHARED bool operator != ( const asset_url& o ) const;
	friend CORE_SHARED  std::ostream& operator << ( std::ostream& op, const asset_url& url );

private:
	size_t _get_incomplete( const std::string& v ) const;
	std::string _trim( const std::string& v, const std::string& toks ) const;
	std::string _get_path( const std::string& v ) const;
	std::string _get_type( const std::string& v ) const;
#pragma endregion
};

namespace std {
	template<>
	struct hash< asset_url > {
		size_t operator ()( const asset_url& u ) const {
			return std::hash< std::string >()( u.format() );
		}
	};
}

#include <memory>
#include <sstream>
enum class asset_state {
	created,
	initializing,
	initialized,
	streaming,
	loading,
	loaded,
	unloading
};
#include <atomic>
// a resource that needs to be loaded or streamed
// before using it, base class for any kind of digital content
// or asset e.g. textures, meshes, effects etc.
class i_asset {
public:
	virtual ~i_asset( void ) = default;
	// returns the current state of the asset
	virtual std::atomic< asset_state >& get_state( void ) = 0;
	// called by the asset manager just before calling load
	virtual void pre_load( void ) = 0;
	// called by the asset manager when loading the asset
	// this is the main logic of loading and initializing
	// a specific asset type
	// returns true if successful, false otherwise
	// sets err to error message if unsuccessful
	virtual bool load( const std::string& data, std::string& err ) = 0;
	// called by the asset manager after load, only if
	// load was successful ( returned true )
	virtual void post_load( void ) = 0;
	// called by the asset manager just before calling unload
	virtual void pre_unload( void ) = 0;
	// called by the asset manager when unloading the asset
	// this is the main logic of unloading a specific asset type
	// returns true if successful, false otherwise
	// sets err to error message if unsuccessful
	virtual bool unload( std::string& err ) = 0;
	// called by the asset manager after unload, only if unload was successful
	virtual void post_unload( void ) = 0;
	// returns the path of the asset
	virtual asset_url get_path( void ) const = 0;
	// sets the specified parameter to the specified value
	virtual void set_load_param( const std::string& par, const std::string& val ) = 0;
	// returns the specified parameter's value
	virtual std::string get_load_param( const std::string& par ) const = 0;
};

typedef std::shared_ptr< i_asset > asset_ptr;

#include <future>
// represents any kind of data source, that is available
// to open a stream into
// e.g. raw filesystem files, databases, network locations etc.
class i_asset_streamer {
public:
	// opens a stream to the asset found on the specified url if it exists
	// returns the opened stream if successful
	virtual std::stringstream open_data_stream( const asset_url& url ) = 0;
	// opens and fully loads the data of the asset, found on the url
	virtual std::string load_data( const asset_url& url ) = 0;
	// opens and begins asynchronous loading of the data of the asset, found on the url
	virtual std::future< std::string > load_data_async( const asset_url& url ) = 0;
	// returns true if the asset exists and is openable
	virtual bool check_asset( const asset_url& url ) = 0;
};

typedef std::shared_ptr< i_asset_streamer > asset_streamer_ptr;

class i_asset_listener {
public:
	virtual void load_ready( asset_ptr a ) const = 0;
};

// manages a collection of a specific type of assets
// and their search paths
// e.g. there could be a texture_manager for textures
class i_asset_manager {
public:
	// Returns the type string that identifies the 
	// asset type, managed by the manager implementation
	virtual const char* get_type( void ) const = 0;
	// returns the asset found on the specified url or name if it exists
	// and makes sure that the asset is loaded
	virtual asset_ptr load_asset( const asset_url& url ) = 0;
	virtual asset_ptr load_asset( const std::string& name ) = 0;
	// returns the asset found on the specified url or name if it exists
	// and begins the loading of the asset, listener is called when loading is ready
	virtual asset_ptr load_asset( const asset_url& url, const i_asset_listener* l ) = 0;
	virtual asset_ptr load_asset( const std::string& name, const i_asset_listener* l ) = 0;
	// unloads the asset found on the specified url or name if it exists
	virtual void unload_asset( const asset_url& url ) = 0;
	virtual void unload_asset( const std::string& name ) = 0;
	// unloads every asset that is only referenced by the manager
	virtual void unload_unreferenced( void ) = 0;
	// returns the asset found on the specified url or name if it exists
	virtual asset_ptr get_asset( const asset_url& url ) = 0;
	virtual asset_ptr get_asset( const std::string& name ) = 0;
};

typedef std::shared_ptr< i_asset_manager > asset_manager_ptr;

#include <unordered_map>
class asset_params {
#pragma region data members
private:
	std::unordered_map< std::string, std::string > m_params;
	std::string m_source;
#pragma endregion

#pragma region member functions
public:
	CORE_SHARED asset_params( void ) = default;
	CORE_SHARED asset_params( const std::string& source );
	CORE_SHARED bool parse( void );
	CORE_SHARED const std::unordered_map< std::string, std::string >& get_params( void ) const;
	CORE_SHARED std::string get_value( const std::string& name ) const;
	CORE_SHARED void set_value( const std::string& name, const std::string& value );

	template< typename T >
	T get_( const std::string& name ) const {
		T val;
		std::istringstream s( this->get_value( name ) );
		s >> val;
		return val;
	}
#pragma endregion
};

#include "../di_rtlib/define_dependency.hpp"
#include "../di_rtlib/define_attribute.hpp"
#include "logger.hpp"
class asset_manager_base
	: public i_asset_manager, public di::component {
#pragma region types
protected:
	typedef std::vector< std::string > string_vector;
	typedef std::unordered_map< asset_url, asset_ptr > asset_url_map;
#pragma endregion

#pragma region data members
protected:
	component_dependency( m_logger, i_logger );
	component_dependency( m_streamer, i_asset_streamer );
	component_attributes( m_assets, std::string );
	component_attributes( m_search_urls, std::string );

	asset_url_map m_asset_map;
#pragma endregion

#pragma region member functions
protected:
	// Creates a new asset with the type of the asset
	// that the manager implementation manages
	// This is called when inserting new assets during initialization
	virtual asset_ptr create_asset( const asset_url& url ) = 0;

private:
	enum manager_ref_list {
		asset_map = 0,
		manager_ref_count
	};

	virtual CORE_SHARED void initialize_component( void ) override;

protected:
	// inserts a new asset into this manager with the specified url
	// called during initialization
	// on name collision the new asset with the existing name will
	// be appended with an increasing number
	void CORE_SHARED _insert_asset( const asset_url& url );
	void CORE_SHARED _load_asset( asset_ptr a );
	void CORE_SHARED _unload_asset( asset_ptr a );
	void CORE_SHARED _resolve_asset( const asset_url& aurl );
	void CORE_SHARED _init( void );
	void CORE_SHARED _create_loader_thread( asset_ptr a, const i_asset_listener* l );

	virtual CORE_SHARED std::shared_ptr< i_asset > load_asset( const asset_url& url ) override;
	virtual CORE_SHARED std::shared_ptr< i_asset > load_asset( const std::string& name ) override;
	virtual CORE_SHARED asset_ptr load_asset( const asset_url& url, const i_asset_listener* l ) override;
	virtual CORE_SHARED asset_ptr load_asset( const std::string& name, const i_asset_listener* l ) override;
	virtual CORE_SHARED void unload_asset( const asset_url& url ) override;
	virtual CORE_SHARED void unload_asset( const std::string& name ) override;
	virtual CORE_SHARED void unload_unreferenced( void ) override;
	virtual CORE_SHARED std::shared_ptr< i_asset > get_asset( const asset_url& url ) override;
	virtual CORE_SHARED std::shared_ptr< i_asset > get_asset( const std::string& name ) override;
#pragma endregion
};

#include <mutex>
class asset_base
	: public i_asset {
#pragma region data members
private:
	std::mutex m_mutex;
	asset_url m_path;
	std::atomic< asset_state > m_state { asset_state::created };

protected:
	asset_params m_params;
#pragma endregion

#pragma region member functions
protected:
	CORE_SHARED asset_base( const asset_url& url );
	
public:
	virtual CORE_SHARED std::atomic< asset_state >& get_state( void ) override;
	virtual CORE_SHARED asset_url get_path( void ) const override;
	virtual CORE_SHARED void pre_load( void ) override;
	virtual CORE_SHARED bool load( const std::string& data, std::string& err ) override;
	virtual CORE_SHARED void post_load( void ) override;
	virtual CORE_SHARED void pre_unload( void ) override;
	virtual CORE_SHARED bool unload( std::string& err ) override;
	virtual CORE_SHARED void post_unload( void ) override;
	virtual CORE_SHARED void set_load_param( const std::string& par, const std::string& val ) override;
	virtual CORE_SHARED std::string get_load_param( const std::string& par ) const override;
#pragma endregion
};

class text_asset
	: public asset_base {
#pragma region data members
private:
	std::string m_text;
#pragma endregion

#pragma region member functions
public:
	CORE_SHARED text_asset( const asset_url& url );
	CORE_SHARED const std::string& get_text( void ) const;

private:
	virtual bool load( const std::string& data, std::string& err ) override;
#pragma endregion
};

typedef std::shared_ptr< text_asset > text_asset_ptr;

class i_asset_type_manager {
public:
	virtual asset_manager_ptr get( const std::string& ty ) const = 0;
	virtual std::vector< asset_manager_ptr > get_all( void ) const = 0;
	virtual std::vector< std::string > get_types( void ) const = 0;
};

typedef i_asset_type_manager* type_manager_ptr;