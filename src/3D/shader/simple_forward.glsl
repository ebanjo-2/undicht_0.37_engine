#vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;
layout (location = 2) in vec3 aNormal;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;
uniform float scale = 10.0f;

out vec2 uv;

void main() {
	
	//uv = aUv;
    uv = aPos.xy + 0.5;
	gl_Position = proj * view * model * vec4(aPos, 1.0);

}



#fragment
#version 330 core

out vec4 FragColor;

in vec2 uv;

uniform sampler2D mesh_texture;

void main() {

	FragColor = texture(mesh_texture, uv);
	//FragColor = vec4(1.0,1.0,1.0,1.0);
}
