#pragma once
#include <unordered_map>
#include <string>
#include <sstream>
#include <memory>
#include "export.hpp"
#include "dependency.hpp"
#include "attribute.hpp"
#include "exception.hpp"
#include "meta_class.hpp"
namespace di {
class component {
#pragma region types
private:
	struct component_id {
		component* cmp { nullptr };
	};

public:
	template< typename T >
	class attribute
		: public i_attribute {
	private:
		T m_value;

	public:
		attribute( const component_id& cid, const std::string& name ) {
			cid.cmp->_register_attribute( name, this );
		}

		attribute( const component_id& cid, const std::string& name, const T& def )
			: m_value( def ) {
			cid.cmp->_register_attribute( name, this );
		}

		virtual void parse_string( const std::string& v ) override {
			std::istringstream str( v );
			str >> m_value;
		}

		virtual std::string format_string( void ) const override {
			return std::to_string( m_value );
		}

		const T& get_value( void ) const {
			return m_value;
		}

		void set_value( const T& v ) {
			m_value = v;
		}

		operator T ( void ) {
			return m_value;
		}
	};

	template< typename T >
	class attributes
		: public i_attribute {
	private:
		std::vector< T > m_values;

	public:
		attributes( const component_id& cid, const std::string& name ) {
			cid.cmp->_register_attribute( name, this );
		}

		virtual void parse_string( const std::string& v ) override {
			std::istringstream str( v );
			std::string tmp;
			do {
				str >> tmp;
				if( tmp != "[" && tmp != "]" && !tmp.empty() ) {
					m_values.emplace_back( std::move( tmp ) );
				}
			} while( !tmp.empty() );
		}

		virtual std::string format_string( void ) const override {
			std::string r = "[ ";
			std::ostringstream s;
			for( const T& v : m_values ) {
				s << v;
				r.append( s.str() + " " );
				s.clear();
			}
			r.append( "]" );
			return r;
		}

		typename std::vector< T >::iterator begin( void ) {
			return m_values.begin();
		}

		typename std::vector< T >::iterator end( void ) {
			return m_values.end();
		}

		T operator [] ( size_t s ) const {
			return m_values[ s ];
		}

		const std::vector< T >& get_values( void ) const {
			return m_values;
		}
	};

	template< typename T >
	class dependency
		: public i_dependency {
	private:
		T* m_component { nullptr };

	public:
		dependency( const component_id& cid, const std::string& name ) {
			cid.cmp->_register_dependency( name, this );
		}

		virtual void set_component( component* c ) {
			m_component = dynamic_cast< T* >( c );
		}

		T* get( void ) {
			return m_component;
		}

		const T* get( void ) const {
			return m_component;
		}

		T* operator -> ( void ) {
			return m_component;
		}

		const T* operator -> ( void ) const {
			return m_component;
		}

		operator T* ( void ) {
			return m_component;
		}

		operator const T* ( void ) const {
			return m_component;
		}
	};

	template< typename T >
	class dependencies
		: public i_dependency {
	private:
		std::vector< T* > m_components;

	public:
		dependencies( const component_id& cid, const std::string& name ) {
			cid.cmp->_register_dependency( name, this );
		}

		virtual void set_component( component* c ) {
			T* pt = dynamic_cast< T* >( c );
			if( pt != nullptr ) m_components.push_back( pt );
		}

		typename std::vector< T* >::iterator begin( void ) {
			return m_components.begin();
		}

		typename std::vector< T* >::iterator end( void ) {
			return m_components.end();
		}

		typename std::vector< T* >::const_iterator begin( void ) const {
			return m_components.begin();
		}

		typename std::vector< T* >::const_iterator end( void ) const {
			return m_components.end();
		}

		T* operator [] ( size_t s ) {
			return m_components[ s ];
		}

		const T* operator [] ( size_t s ) const {
			return m_components[ s ];
		}
	};
#pragma endregion

#pragma region data members
private:
	std::unordered_map< std::string, i_dependency* > m_dependencies;
	std::unordered_map< std::string, i_attribute* > m_attributes;

	meta_class m_meta;
#pragma endregion

#pragma region member functions
public:
	virtual ~component( void ) = default;

	template< typename T >
	void set_attribute( const std::string& name, const T& val ) {
		auto fit = m_attributes.find( name );
		if( fit == m_attributes.end() ) throw attribute_not_found( name, m_meta.get_class_name() );
		std::ostringstream str;
		if( !( str << std::boolalpha << val ) ) throw wrong_type( name, m_meta.get_class_name() );
		fit->second->parse_string( str.str() );
	}

	void set_meta_class( const meta_class& m ) {
		m_meta = m;
	}

	const meta_class& get_meta_class( void ) const {
		return m_meta;
	}

	template< typename T >
	void set_attribute( const std::string& name, const std::vector< T >& val ) {

	}

	DI_SHARED void inject( const std::string& dep, component* cmp );
	DI_SHARED std::string get_attribute( const std::string& name ) const;

	virtual DI_SHARED void initialize_component( void ) { }

protected:
	void _register_attribute( const std::string& name, i_attribute* a ) {
		m_attributes[ name ] = a;
	}

	void _register_dependency( const std::string& name, i_dependency* d ) {
		m_dependencies[ name ] = d;
	}

	component_id _create_id( void ) {
		component_id id;
		id.cmp = this;
		return id;
	}
#pragma endregion
};

template<>
void component::attribute< std::string >::parse_string( const std::string& val ) {
	m_value = val;
}

template<>
void component::attribute< std::wstring >::parse_string( const std::string& val ) {
	m_value = std::wstring( val.begin(), val.end() );
}

template<>
std::string component::attribute< std::string >::format_string( void ) const {
	return m_value;
}

template<>
std::string component::attribute< std::wstring >::format_string( void ) const {
	return std::string( m_value.begin(), m_value.end() );
}


}