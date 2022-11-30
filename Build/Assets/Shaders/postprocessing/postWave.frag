#version 430 core 
  
in vec2 texcoord; 
  
out vec4 fcolor; 

uniform float offset;
  
uniform sampler2D textureMap; 
  
void main() 
{ 
	// wave 
	vec2 ttexcoord = texcoord; 
	ttexcoord.x += sin(ttexcoord.y * 30.0 + offset) / 100.0; 
	fcolor = texture(textureMap, ttexcoord);
} 