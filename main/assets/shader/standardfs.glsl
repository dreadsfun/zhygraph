#version 430

struct directional_light {
	vec3 direction;
	float intensity;
	vec4 color;
};

struct point_light {
	vec3 position;
	float intensity;
	vec4 color;
	float range;
};

struct spot_light {
	vec3 position;
	float intensity;
	vec4 color;
	float range;
	float angle;
};

uniform sampler2D g_albedo_map;
uniform sampler2D g_specular_map;
uniform sampler2D g_emission_map;
uniform sampler2D g_normal_map;

uniform vec4 g_albedo_color;
uniform vec4 g_specular_color;
uniform vec4 g_emission_color;
uniform float g_shininess;
uniform float g_x_tiling;
uniform float g_y_tiling;
uniform float g_x_offset;
uniform float g_y_offset;

uniform vec4 g_ambient_scene_light = vec4(1.0, 0.9803, 0.8039, 0.125);

uniform vec3 g_camera_position;

uniform directional_light g_dir_light;

uniform int g_point_light_count;
uniform point_light g_point_lights[5];

in vec2 uv1_fs;
in vec3 normal_fs;
in vec3 tangent_fs;
in vec3 bitangent_fs;
in vec3 world_position_fs;

out vec4 final_color;

vec3 fetch_bumped_normal() {
	return normalize(mat3(normalize(tangent_fs), normalize(bitangent_fs), normalize(normal_fs)) * normalize((2.0 * texture2D(g_normal_map, vec2( uv1_fs.x * g_x_tiling + g_x_offset, uv1_fs.y * g_y_tiling + g_y_offset )).xyz - vec3(1.0, 1.0, 1.0))));
}

vec3 calculate_specular_contribution(vec3 light_color, float light_intensity, vec3 light_direction, vec3 normal) {
	vec3 c_spec = vec3(0, 0, 0);
	
	vec3 reflected = normalize(reflect(light_direction, normal));
	vec3 fragment_to_camera = normalize(world_position_fs - g_camera_position);
	float specular_factor = max(0.0, dot(fragment_to_camera, reflected));
	c_spec = light_color * light_intensity * g_specular_color.xyz * (g_specular_color.w * pow(specular_factor, g_shininess));
	
	return c_spec;
}

vec3 calculate_diffuse_contribution(vec3 light_color, float light_intensity, vec3 light_direction, vec3 normal, vec3 diffuse_color) {
	vec3 c_diff = vec3(0, 0, 0);
	
	float diffuse_factor = max( 0.0, dot(normal, -light_direction) );
	
	c_diff = light_color * diffuse_color * (diffuse_factor * light_intensity) + g_ambient_scene_light.xyz * g_ambient_scene_light.w * diffuse_color * light_intensity * light_color;

	return c_diff;
}

vec3 calculate_diffuse_contribution_point_light(int index, vec3 normal, vec3 diffuse_color) {
	vec3 pt_direction = normalize(g_point_lights[index].position - world_position_fs);
	float src_distance = length(pt_direction);
	if(src_distance < g_point_lights[index].range) {
		float attenuation = 1 - (src_distance * src_distance) / (g_point_lights[index].range * g_point_lights[index].range);
		return calculate_diffuse_contribution(g_point_lights[index].color.xyz,
		g_point_lights[index].intensity * attenuation, pt_direction, normal, diffuse_color);
	} else {
		return vec3(0.0, 0.0, 0.0);
	}
}

vec3 calculate_specular_contribution_point_light(int index, vec3 normal) {
	vec3 pt_direction = normalize(g_point_lights[index].position - world_position_fs);
	float src_distance = length(pt_direction);
	if(src_distance < g_point_lights[index].range) {
		float attenuation = 1 - (src_distance * src_distance) / (g_point_lights[index].range * g_point_lights[index].range);
		return calculate_specular_contribution(g_point_lights[index].color.xyz,
		g_point_lights[index].intensity * attenuation, pt_direction, normal);
	} else {
		return vec3(0.0, 0.0, 0.0);
	}
}

void main() {
	vec3 face_normal = fetch_bumped_normal();
	
	vec4 final_albedo = g_albedo_color + texture2D( g_albedo_map, vec2( uv1_fs.x * g_x_tiling + g_x_offset, uv1_fs.y * g_y_tiling + g_y_offset ) );
	
	vec3 norm_dirlight_direction = normalize(g_dir_light.direction);
	
	vec3 total_spec_contrib = calculate_specular_contribution(g_dir_light.color.xyz, g_dir_light.intensity, norm_dirlight_direction, face_normal);
	vec3 total_diff_contrib = calculate_diffuse_contribution(g_dir_light.color.xyz, g_dir_light.intensity, norm_dirlight_direction, face_normal, final_albedo.xyz);
	
	for(int i = 0; i < g_point_light_count; ++i) {
		total_spec_contrib += calculate_specular_contribution_point_light(i, face_normal);
		total_diff_contrib += calculate_diffuse_contribution_point_light(i, face_normal, final_albedo.xyz);
	}
	
	final_color = vec4( total_spec_contrib + total_diff_contrib + g_emission_color.xyz, 1.0);
	//final_color = vec4(face_normal, 1.0);
}