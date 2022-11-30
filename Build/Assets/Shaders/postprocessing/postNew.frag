#version 430 core 
  
in vec2 texcoord; 
  
out vec4 fcolor; 
  
uniform sampler2D textureMap; 
  
void main() 
{ 
	vec3 color = texture(textureMap, texcoord).rgb; 
	// black / white 
	vec3 prToning = vec3((color.r + color.g + color.b) / 5); 
		
	prToning = vec3(prToning.x + .33f, prToning.y + .22f, prToning.z + .12f);
	
	//fcolor = vec4(color, 1);
	fcolor = vec4(prToning, 1);
} 