#vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;
layout (location = 2) in vec3 aNormal;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;
uniform float scale = 10.0f;

out vec3 positional_color;

void main() {
	
	positional_color = normalize(aPos);
	gl_Position = proj * view * model * vec4(10 * aPos, 1.0);

}



#fragment
#version 330 core

out vec4 FragColor;

in vec3 positional_color;

void main() {

	FragColor = vec4(positional_color.xxz, 1.0);
	//FragColor = vec4(1.0,1.0,1.0,1.0);
}