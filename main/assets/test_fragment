#version 430

uniform sampler2D albedo_map;

in vec2 uv_fs;

out vec4 fragment_color;

void main() {
	fragment_color = texture2D(albedo_map, uv_fs);
}