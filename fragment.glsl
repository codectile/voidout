#version 330 core

flat in vec3 outColor;




out vec4 FragColor;
void main()
{
	
	//FragColor = vec4(result, 1.0);
	FragColor = vec4(outColor, 1.0);
}