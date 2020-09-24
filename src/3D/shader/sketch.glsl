#vertex
#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;
uniform vec3 scale;

out vec2 uv;

void main() {
	
	gl_Position = proj * view * model * vec4(aPos * scale, 1.0);

}



#fragment
#version 330 core

out vec3 FragColor;

uniform vec3 color;

void main() {

	FragColor = color;
}
