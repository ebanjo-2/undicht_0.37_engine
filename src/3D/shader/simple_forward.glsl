#vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;
layout (location = 2) in vec3 aNormal;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

void main() {

	gl_Position = proj * view * model * vec4(aPos, 1.0);

}


#fragment
#version 330 core

out vec4 FragColor;

void main() {

	FragColor = vec4(0.8, 0.2, 0.0, 1.0);
	
}
