#version 460 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Color;

uniform sampler2D inputTexture;

out vec4 fColor;

void main(){
	fColor = texture(inputTexture, TexCoords);
}