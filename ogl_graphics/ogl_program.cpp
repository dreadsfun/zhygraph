#include <glm\glm.hpp>
#include "ogl_program.hpp"
template<>
shader_program& shader_program::set< int >( const std::string& uni, const int& v ) {
	glProgramUniform1i( m_gl_name, glGetUniformLocation( m_gl_name, uni.c_str() ), v );
	return *this;
}

template<>
shader_program& shader_program::set< float >( const std::string& uni, const float& v ) {
	glProgramUniform1f( m_gl_name, glGetUniformLocation( m_gl_name, uni.c_str() ), v );
	return *this;
}

template<>
shader_program& shader_program::set< glm::vec2 >( const std::string& uni, const glm::vec2& v ) {
	glProgramUniform2f( m_gl_name, glGetUniformLocation( m_gl_name, uni.c_str() ), v.x, v.y );
	return *this;
}

template<>
shader_program& shader_program::set< glm::vec3 >( const std::string& uni, const glm::vec3& v ) {
	glProgramUniform3f( m_gl_name, glGetUniformLocation( m_gl_name, uni.c_str() ), v.x, v.y, v.z );
	return *this;
}

template<>
shader_program& shader_program::set< glm::vec4 >( const std::string& uni, const glm::vec4& v ) {
	glProgramUniform4f( m_gl_name, glGetUniformLocation( m_gl_name, uni.c_str() ), v.x, v.y, v.z, v.w );
	return *this;
}

template<>
shader_program& shader_program::set< glm::mat4 >( const std::string& uni, const glm::mat4& v ) {
	glProgramUniformMatrix4fv( m_gl_name, glGetUniformLocation( m_gl_name, uni.c_str() ), 1, GL_FALSE, &v[ 0 ][ 0 ] );
	return *this;
}

shader_program::shader_program( void ) {
	m_gl_name = glCreateProgram();
}

shader_program::shader_program( shader_program && m )
	: m_gl_name( m.m_gl_name ),
	m_vertex( m.m_vertex ),
	m_fragment( m.m_fragment ),
	m_log( std::move( m.m_log ) ) {
	m.m_gl_name = 0;
	m.m_vertex = 0;
	m.m_fragment = 0;
}

shader_program & shader_program::set_vertex_program( GLuint v ) {
	m_vertex = v;
	return *this;
}

shader_program & shader_program::set_fragment_program( GLuint v ) {
	m_fragment = v;
	return *this;
}

shader_program & shader_program::link( void ) {
	_attach_sh_validate( m_vertex );
	_attach_sh_validate( m_fragment );
	glLinkProgram( m_gl_name );
	GLint lst = 0;
	glGetProgramiv( m_gl_name, GL_LINK_STATUS, &lst );
	if( lst == GL_TRUE ) {

	} else {
		GLint llt = 0;
		glGetProgramiv( m_gl_name, GL_INFO_LOG_LENGTH, &llt );
		m_log.resize( llt );
		glGetProgramInfoLog( m_gl_name, llt, nullptr, &m_log[ 0 ] );
	}
	return *this;
}

shader_program & shader_program::validate( void ) {
	glValidateProgram( m_gl_name );
	return *this;
}

shader_program & shader_program::use( void ) {
	glUseProgram( m_gl_name );
	return *this;
}

bool shader_program::has_error( void ) const {
	return !m_log.empty();
}

const std::string & shader_program::get_log( void ) const {
	return m_log;
}

bool shader_program::_attach_sh_validate( GLuint sh ) const {
	if( sh != 0 ) {
		glAttachShader( m_gl_name, sh );
		return true;
	} else {
		return false;
	}
}
