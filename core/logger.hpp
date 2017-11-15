#pragma once
#include <string>
#include "export.hpp"
enum class priority {
	debug,
	info,
	warn,
	error,
	fatal
};

class log_stream;

#include <memory>
class i_logger {
public:
	virtual void log( priority p, const std::string& m, const std::string& cl ) const = 0;
	virtual log_stream init_stream( priority p, const std::string& cl ) const = 0;
	virtual std::string priority_to_string( priority p ) const = 0;
};

typedef i_logger* logger_ptr;

#include <sstream>
class log_stream {
#pragma region data members
private:
	const i_logger* m_owner { nullptr };
	priority m_pr { priority::debug };
	std::string m_cl;
	std::stringstream m_stream;
#pragma endregion

#pragma region member functions
public:
	log_stream( log_stream&& m );
	log_stream( priority p, const std::string& cl, const i_logger* l );
	CORE_SHARED ~log_stream( void );

	template< typename T >
	log_stream& operator << ( const T& v ) {
		m_stream << v;
		return *this;
	}
#pragma endregion
};

class i_log_channel {
public:
	virtual void log( const std::string& m ) const = 0;
};

#define debug( m ) m_logger->log( priority::debug, m, typeid( *this ).name() );
#define info( m ) m_logger->log( priority::info, m, typeid( *this ).name() );
#define warn( m ) m_logger->log( priority::warn, m, typeid( *this ).name() );
#define error( m ) m_logger->log( priority::error, m, typeid( *this ).name() );
#define fatal( m ) m_logger->log( priority::fatal, m, typeid( *this ).name() );

#define sdebug m_logger->init_stream( priority::debug, typeid( *this ).name() )
#define sinfo m_logger->init_stream( priority::info, typeid( *this ).name() )
#define swarn m_logger->init_stream( priority::warn, typeid( *this ).name() )
#define serror m_logger->init_stream( priority::error, typeid( *this ).name() )
#define sfatal m_logger->init_stream( priority::fatal, typeid( *this ).name() )
