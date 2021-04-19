#version 460 core
//layout is a key word that saying it comes for VAO and VBO
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;


out vec3 Normal;
out vec2 TexCoords;
out vec3 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
//gl pos what is the vertex pos should be
	gl_Position = projection * view * model * vec4(position, 1.0f);
	Color = vec3(1.0f);
}