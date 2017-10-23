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
				stringstream mstream;
				string& mwhat;
			public:
				_auto_close( string& str )
					: mwhat( str ) { }
				_auto_close( _auto_close&& m )
					: mstream( move( m.mstream ) ),
					mwhat( m.mwhat ) { }
				~_auto_close() {
					mwhat = mstream.str();
				}
				template< typename T >
				_auto_close& operator << ( const T& v ) {
					mstream << v;
					return *this;
				}
			};
			string mwhat;
		protected:
			exception( const char* file, int line ) {
				_s() << "exception at " << file << " " << line << ": ";
			}
			exception() = default;
			_auto_close _s() {
				return _auto_close( mwhat );
			}
		public:
			virtual const char* what() const override {
				return mwhat.c_str();
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