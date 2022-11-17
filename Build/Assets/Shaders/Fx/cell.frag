#version 430 core
 
#define POINT		0
#define DIRECTIONAL	1
#define SPOTLIGHT	2
 
in vec3 position;
in vec3 normal;
in vec2 texcoord;
 
out vec4 fcolor; // pixel to draw
 
uniform struct Light
{
	int type; 
	vec3 ambient;
	vec3 color;
	vec4 position;
	vec3 direction;
	float cutoff;
	float exponent;
} light;
 
uniform struct Material
{
	vec3 color;
	float shininess;
	vec2 uv_tiling;
	vec2 uv_offset;
} material; 

int levels = 5;
const float scaleFactor = 1.0 / levels;
 
void toon(vec3 position, vec3 normal, out vec3 ambient, out vec3 diffuse, out vec3 specular)
{
	// direction vector to light
	// calculate light direction (unit vector)
	vec3 light_dir = (light.type == 1) ? normalize(-light.direction) : normalize(vec3(light.position) - position);
 
	// if spotlight, compute intensity based on angle to cutoff
	float spot_intensity = 1;
	if (light.type == 2)
	{
		// get cosine of light direction and direction vector from light
		float cosine = dot(light.direction, -light_dir);
		// get angle
		float angle = acos(cosine);
 
		// if inside of cutoff, set spot intensity
		spot_intensity = (angle < light.cutoff) ? pow(cosine, light.exponent) : 0;
		//spot_intensity = 0;
	}
 
	// AMBIENT
	ambient = light.ambient * material.color;
 
	// DIFFUSE
	// calculate light intensity with dot product (normal * light direction)
	float intensity = max(dot(light_dir, normal), 0) * spot_intensity;
	intensity = floor(intensity * levels) * scaleFactor;
	

	// calculate diffuse color
	diffuse = light.color * material.color * intensity;
 
	// SPECULAR
	specular = vec3(0);
}
 
void main()
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
 
	toon(position, normal, ambient, diffuse, specular);
 
	vec2 ttexcoord = (texcoord * material.uv_tiling) + material.uv_offset;
 
	fcolor = vec4(ambient + diffuse, 1) + vec4(specular, 1);
	//fcolor = vec4(1,.5,.5,1);
}