#pragma once
#include "export.hpp"
#include "component.hpp"
#include "meta_class.hpp"
namespace di {
class component_registry {
public:
	class use_expression {
	public:
		class as_expression {
		private:
			use_expression* m_owner { nullptr };

		public:
			as_expression( use_expression* o )
				: m_owner( o ) { }

			void of( const std::string& of ) {
				m_owner->m_of_str = of;
			}

			void of( component* cmp ) {
				m_owner->m_of = cmp;
				m_owner->_inject();
			}
		};

	private:
		component_registry* m_owner { nullptr };
		as_expression m_as;

		component* m_use { nullptr };
		component* m_of { nullptr };

		std::string m_of_str;
		std::string m_as_str;

		void _inject( void ) {
			component* of = nullptr;
			if( m_of == nullptr ) component* of = m_owner->get_component( m_of_str );
			else of = m_of;
			of->inject( m_as_str, m_use );
		}

	public:
		use_expression( component_registry* owner, const std::string& use )
			: m_as( this ),
			m_owner( owner ) {
			m_use = owner->get_component( use );
		}

		use_expression( component_registry* owner, component* cmp )
			: m_as( this ),
			m_owner( owner ) {
			m_use = cmp;
		}

		as_expression& as( const std::string& as ) {
			m_as_str = as;
			return m_as;
		}
	};

private:
	std::unordered_map< std::string, std::unique_ptr< component > > m_components;

public:
	template< typename T >
	T* get_( const std::string& id ) {
		return dynamic_cast< T* >( this->get_component( id ) );
	}

	use_expression use( const std::string& use ) {
		return use_expression( this, use );
	}

	use_expression use( component* cmp ) {
		return use_expression( this, cmp );
	}

	auto begin( void ) {
		return m_components.begin();
	}

	auto end( void ) {
		return m_components.end();
	}

	DI_SHARED void purge( void );
	DI_SHARED component* get_component( const std::string& id );
	DI_SHARED component* create( const std::string& id, const std::string& clname );
	DI_SHARED void initialize_components( void );
};
}