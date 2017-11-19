#version 430
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

uniform mat4 g_full_vertex_transform;
uniform mat4 g_model_to_world_transform;

out vec2 uv_fs;
out vec3 normal_fs;
out vec3 tangent_fs;
out vec3 bitangent_fs;
out vec3 world_position_fs;

void main() {
	uv_fs = uv;
	normal_fs = ( g_model_to_world_transform * vec4( normal, 0.0 ) ).xyz;
	tangent_fs = ( g_model_to_world_transform * vec4( tangent, 0.0 ) ).xyz;
	bitangent_fs = ( g_model_to_world_transform * vec4( bitangent, 0.0 ) ).xyz;
	world_position_fs = ( g_model_to_world_transform * vec4( pos, 1.0 ) ).xyz;
	gl_Position = g_full_vertex_transform * vec4( pos, 1.0 );
}