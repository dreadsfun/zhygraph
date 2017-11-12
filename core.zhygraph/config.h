#pragma once
#include <string>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include "exception.h"
namespace zhygraph {
	namespace core {
		using namespace std;
		class config {
		private:
			typedef unordered_map< string, string > name_value_map;
			typedef unordered_map< string, name_value_map > ini_map;
		public:
			class _group {
			private:
				const name_value_map& m_grps_map;
			public:
				_group( const name_value_map& nv )
					: m_grps_map( nv ) { }
				const string& value( const string& name, const string& def = "" ) const {
					auto f = m_grps_map.find( name );
					if( f == m_grps_map.end() )
						return def;
					else
						return f->second;
				}
				const name_value_map& values() const {
					return m_grps_map;
				}
				int integer( const string& name, int def = 0 ) const {
					const string& v = this->value( name );
					if( v.empty() )
						return def;
					else
						return atoi( v.c_str() );
				}
				double number( const string& name, double def = 0 ) const {
					const string& v = this->value( name );
					if( v.empty() )
						return def;
					else
						return atof( v.c_str() );
				}
				bool test( const string& name, bool def = false ) const {
					const string& v = this->value( name );
					if( v.empty() )
						return def;
					else
						return v == "true" || v == "1";
				}
			};
		private:
			ini_map m_map;
		public:
			class ini_exception
				: public core::exception {
			public:
				ini_exception( uint32_t ln, uint32_t col, const string& msg )
					: ini_exception( nullptr, 0, ln, col, msg ) { }
				ini_exception( const char* file, int line, uint32_t ln, uint32_t col, const string& msg )
					: core::exception( file, line ) {
					_s() << "config exception at " << ln << " " << col << ": " << msg;
				}
			};
			void load( const string& path ) {
				ifstream fs( path );
				if( fs.is_open() ) {
					this->clear();
					string ln;
					uint32_t lnc = 0;
					bool grp = false;
					string cgrp;
					while( getline( fs, ln ) ) {
						lnc++;
						if( ln.empty() ) {
							grp = false;
						} else {
							if( ln.front() == '[' ) {
								throw_if_not( ln.back() == ']', ini_exception, lnc, ln.size(), "expected matching bracket at end of group declaration" );
								grp = true;
								cgrp = ln.substr( 1, ln.size() - 2 );
							} else {
								throw_if_not( grp, ini_exception, lnc, 0, "expected a group declaration" );
								size_t pos = ln.find( '=' );
								throw_if( pos == string::npos, ini_exception, lnc, ln.size(), "expected a name-value declaration separated by '='" );
								auto& grpnv = m_map[ cgrp ];
								grpnv[ ln.substr( 0, pos ) ] = ln.substr( pos + 1 );
							}
						}
					}
				}
			}
			void clear() {
				m_map.clear();
			}
			_group group( const string& grp ) const {
				static name_value_map em;
				auto f = m_map.find( grp );
				if( f == m_map.end() )
					return _group( em );
				else
					return _group( f->second );
			}
			_group client_group() {
				return this->group( "client" );
			}
		};
	}
}