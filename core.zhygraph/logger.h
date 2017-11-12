#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <mutex>
#include <iostream>
#include <memory>
#include "export.h"
#include "time.h"
namespace zhygraph {
	namespace core {
		enum class log_priority {
			debug,
			info,
			warn,
			error,
			fatal
		};

		class i_log_channel {
		public:
			virtual void log( const std::string& m ) const = 0;
		};

		using logchannelptr = std::unique_ptr<i_log_channel>;

		class log_stream;

		class logger {
		private:
			std::vector< logchannelptr > m_channels;
			std::chrono::high_resolution_clock m_clock;
			
			mutable std::thread::id m_last_thread;
			mutable std::string m_last_class;

		public:
			void channel( logchannelptr c ) {
				m_channels.emplace_back( move( c ) );
			}

			void log( log_priority p, const std::string& m, const std::string& cl ) const {
				unsigned int nlc = 0;
				for( unsigned int i = m.length() - 1; i > 0 && m[ i ] == '\n'; --i && ++nlc );

				std::ostringstream s;
				_set_thread_class( s, std::this_thread::get_id(), cl );
				_write_log( s, p, m.substr( 0, m.length() - nlc ) );

				for( const logchannelptr& c : m_channels ) {
					c->log( s.str() );
				}
			}

			log_stream init_stream( log_priority p, const std::string& cl ) const;

			static std::string priority_to_string( log_priority p ) {
				switch( p ) {
					case log_priority::debug: return "-";
					case log_priority::info: return "+";
					case log_priority::warn: return "!";
					case log_priority::error: return "!!";
					case log_priority::fatal: return "!!!";
					default:
						return "?";
				}
			}

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

			void _write_log( std::ostringstream& str, log_priority p, const std::string& msg ) const {
				str << "\t[" << logger::priority_to_string( p ) << "][" << _format_time() << "] " << msg << std::endl;
			}
		};

		using logger_ptr = std::unique_ptr<logger>;

		class log_stream {
		private:
			const logger* m_owner { nullptr };
			log_priority m_pr { log_priority::debug };
			std::string m_cl;
			std::stringstream m_stream;

		public:
			log_stream( log_stream&& m );
			log_stream( log_priority p, const std::string& cl, const logger* l );
			core_shared ~log_stream( void );

			template< typename T >
			log_stream& operator << ( const T& v ) {
				m_stream << v;
				return *this;
			}
		};

		typedef std::unique_lock< std::mutex > unique_lock;

		class file_channel
			: public i_log_channel {
		private:
			std::string m_file;
			mutable std::mutex m_stream_lock;
			mutable std::ofstream m_fstream;

		public:
			file_channel( const std::string& file )
				: m_file( file ) {
				m_fstream.open( m_file );
			}

			~file_channel( void ) {
				m_fstream.flush();
				m_fstream.close();
			}

			virtual void log( const std::string& m ) const override {
				{
					unique_lock lck( m_stream_lock );
					m_fstream << m;
					m_fstream.flush();
				}
			}
		};

		class stdout_channel
			: public i_log_channel {
		public:
			virtual void log( const std::string& m ) const override {
				unique_lock lck ( cout_lock );
				std::cout << m;
			}

		private:
			static std::mutex cout_lock;
		};

#define debug( m ) mlogger->log( log_priority::debug, m, typeid( *this ).name() );
#define info( m ) mlogger->log( log_priority::info, m, typeid( *this ).name() );
#define warn( m ) mlogger->log( log_priority::warn, m, typeid( *this ).name() );
#define error( m ) mlogger->log( log_priority::error, m, typeid( *this ).name() );
#define fatal( m ) mlogger->log( log_priority::fatal, m, typeid( *this ).name() );

#define sdebug mlogger->init_stream( log_priority::debug, typeid( *this ).name() )
#define sinfo mlogger->init_stream( log_priority::info, typeid( *this ).name() )
#define swarn mlogger->init_stream( log_priority::warn, typeid( *this ).name() )
#define serror mlogger->init_stream( log_priority::error, typeid( *this ).name() )
#define sfatal mlogger->init_stream( log_priority::fatal, typeid( *this ).name() )
	}
}