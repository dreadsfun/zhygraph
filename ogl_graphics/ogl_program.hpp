#pragma once
#include <GL\glew.h>
#include <string>
class shader_program {
private:
	GLuint m_gl_name;
	GLuint m_vertex;
	GLuint m_fragment;
	std::string m_log;

public:
	shader_program( void );
	shader_program( shader_program&& m );
	shader_program( const shader_program& ) = delete;
	shader_program& set_vertex_program( GLuint v );
	shader_program& set_fragment_program( GLuint v );
	shader_program& link( void );
	shader_program& validate( void );
	shader_program& use( void );
	bool has_error( void ) const;
	const std::string& get_log( void ) const;

	template< typename T >
	shader_program& set( const std::string& uni, const T& v );

private:
	bool _attach_sh_validate( GLuint sh ) const;
};