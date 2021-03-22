#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;
layout(location = 3) in vec3 color;

out vec3 Normal;
out vec2 TexCoords;
out vec3 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
gl_Position = projection * view * model * vec4(position, 1.0f);
Color = color;
TexCoords = texCoords;
Normal = normal;

}