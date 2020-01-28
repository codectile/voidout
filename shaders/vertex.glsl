#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

flat out vec3 outColor;


uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

uniform vec3 lightPos; 
uniform vec3 lightColor;



void main()
{
	vec3 fragPos = vec3(model * vec4(pos, 1.0));
	outColor = color;


	// ambient
     float ambientStrength = 0.2;
     vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
     
     vec3 lightDir = normalize(lightPos - fragPos);
     float diff = max(dot(normal, lightDir), 0.0);
     vec3 diffuse = diff * lightColor;
            
    outColor = (ambient + diffuse) * color;
	gl_Position = proj * view * vec4(fragPos, 1.0);
	
}
