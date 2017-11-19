#include <chrono>
#include <thread>
#include <di_rtlib/define_dependency.hpp>
#include "logger.hpp"
#include "time.hpp"
class logger
	: public i_logger, public di::component {
private:
	component_dependencies( m_channels, i_log_channel );
	std::chrono::high_resolution_clock m_clock;

	mutable std::thread::id m_last_thread;
	mutable std::string m_last_class;

private:
	std::string _format_time( void ) const {
		double secs = engine_time::elapsed_seconds();
		int hours = static_cast< int >( secs ) / 3600;
		int minutes = static_cast< int >( secs ) % 3600 / 60;
		double secr = secs - hours * 3600.0 - minutes * 60.0;

		std::ostringstream s;
		s << ( hours == 0 ? "" : std::to_string( hours ) + "h " ) <<
			( hours != 0 || minutes != 0 ? std::to_string( minutes ) + "m " : "" ) << secr << "s";
		return s.str();
	}

	void _set_thread_class( std::ostringstream& str, std::thread::id id, const std::string& cl ) const {
		if( m_last_thread != id || m_last_class != cl ) {
			m_last_thread = id;
			m_last_class = cl;

			str << std::endl << "[" << m_last_thread << "][" << cl << "]" << std::endl;
		}
	}

	void _write_log( std::ostringstream& str, priority p, const std::string& msg ) const {
		str << "\t[" << this->priority_to_string( p ) << "][" << _format_time() << "] " << msg << std::endl;
	}

	virtual void log( priority p, const std::string& m, const std::string& cl ) const override {
		unsigned int nlc = 0;
		for( unsigned int i = m.length() - 1; i > 0 && m[ i ] == '\n'; --i && ++nlc );

		std::ostringstream s;
		_set_thread_class( s, std::this_thread::get_id(), cl );
		_write_log( s, p, m.substr( 0, m.length() - nlc ) );

		for( const i_log_channel* c : m_channels ) {
			c->log( p, s.str() );
		}
	}

	virtual log_stream init_stream( priority p, const std::string& cl ) const override {
		return log_stream( p, cl, this );
	}

	virtual std::string priority_to_string( priority p ) const override {
		switch( p ) {
			case priority::debug: return "-";
			case priority::info: return "+";
			case priority::warn: return "!";
			case priority::error: return "!!";
			case priority::fatal: return "!!!";
			default:
				return "?";
		}
	}
};

#include <iostream>
#include <mutex>
typedef std::unique_lock< std::mutex > unique_lock;
class stdout_channel
	: public i_log_channel, public di::component {
public:
	virtual void log( priority, const std::string& m ) const override {
		unique_lock lck ( cout_lock );
		std::cout << m;
	}

private:
	static std::mutex cout_lock;
};
std::mutex stdout_channel::cout_lock;

#include <Windows.h>
class win32messagebox
	: public i_log_channel, public di::component {
public:
	virtual void log( priority p, const std::string& m ) const override {
		if( p == priority::error || p == priority::fatal ) {
			MessageBoxA( NULL, m.c_str(), "Error Log", MB_OK | MB_ICONERROR );
		}
	}
};

#include <di_rtlib/define_attribute.hpp>
#include <fstream>
class file_channel
	: public i_log_channel, public di::component {
private:
	component_attribute( m_file, std::string );
	mutable std::mutex m_stream_lock;
	mutable std::ofstream m_fstream;

public:
	file_channel( void ) = default;

	~file_channel( void ) {
		m_fstream.flush();
		m_fstream.close();
	}

	virtual void initialize_component() override {
		m_fstream.open( m_file.get_value() );
	}

	virtual void log( priority, const std::string& m ) const override {
		{
			unique_lock lck( m_stream_lock );
			m_fstream << m;
			m_fstream.flush();
		}
	}
};

#include <di_rtlib/register_class.hpp>
register_class( logger );
register_class( stdout_channel );
register_class( file_channel );
register_class( win32messagebox );

log_stream::log_stream( log_stream && m )
	: m_owner( m.m_owner ),
	m_stream( std::move( m.m_stream ) ) {
	m.m_owner = nullptr;
}

log_stream::log_stream( priority p, const std::string & cl, const i_logger * l )
	: m_owner( l ),
	m_cl( cl ),
	m_pr( p ) { }

log_stream::~log_stream( void ) {
	m_owner->log( m_pr, m_stream.str(), m_cl );
	m_stream.clear();
}