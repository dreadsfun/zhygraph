#pragma once
#include <exception>
#include <sstream>
#include <string>
namespace zhygraph {
	namespace core {
		using namespace std;
		class exception
			: public std::exception {
		private:
			class _auto_close {
			private:
				stringstream m_stream;
				string& m_what;
			public:
				_auto_close( string& str )
					: m_what( str ) { }
				_auto_close( _auto_close&& m )
					: m_stream( move( m.m_stream ) ),
					m_what( m.m_what ) { }
				~_auto_close() {
					m_what = m_stream.str();
				}
				template< typename T >
				_auto_close& operator << ( const T& v ) {
					m_stream << v;
					return *this;
				}
			};
			string m_what;
		protected:
			exception( const char* file, int line ) {
				_s() << "exception at " << file << " " << line << ": ";
			}
			exception() = default;
			_auto_close _s() {
				return _auto_close( m_what );
			}
		public:
			virtual const char* what() const override {
				return m_what.c_str();
			}
		};
#ifdef _DEBUG
#  define _exception_source __FILE__ << " " << __LINE__
#  define _exception(type, ...) type(__FILE__, __LINE__, __VA_ARGS__)
#  define dbg_throw_if(cond, type, ...) throw_if(cond, type, __VA_ARGS__)
#else
#  define _exception_source ""
#  define _exception(type, ...) type(_VA_ARGS_)
#  define dbg_throw_if(cond, type, ...)
#endif
#define throw_if(cond, type, ...) if(cond) throw _exception(type, __VA_ARGS__)
	}
}