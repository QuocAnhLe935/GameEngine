#version 460 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Color;
in vec3 FragPosition;


uniform sampler2D inputTexture;
uniform vec3 viewPosition;
uniform vec3 cameraPosistion;
out vec4 fColor;



struct Light{

vec3 lightPos[2];
float ambient[2];
float diffuse[2];
float specular[2];
vec3 lightColor[2];


};

uniform Light light;

void main(){
	vec3 lightDir[2];
	float diff[2];
	float spec[2];

	//ambient
	vec3 ambient= light.ambient[0] *texture(inputTexture, TexCoords).rgb* light.lightColor[0];
	vec3 ambient2= light.ambient[1] *texture(inputTexture, TexCoords).rgb* light.lightColor[1];

	//Diffuse
	vec3 norm=normalize(Normal);
	
	lightDir[0] = normalize(light.lightPos[0]-FragPosition);
	lightDir[1] = normalize(light.lightPos[1]-FragPosition);

	diff[0]= max(dot(norm, lightDir[0]), 0.0);
	diff[1]= max(dot(norm, lightDir[1]), 0.0);

	vec3 diffuse = (diff[0]* light.diffuse[0])* texture(inputTexture, TexCoords).rgb* light.lightColor[0];
	vec3 diffuse2 = (diff[1]* light.diffuse[1])* texture(inputTexture, TexCoords).rgb* light.lightColor[1];


	//Specular
	vec3 viewDir= normalize(viewPosition-FragPosition);

	vec3 reflectDir= reflect(-lightDir[0], norm);
	vec3 reflectDir2 = reflect(-lightDir[1], norm);

	spec[0]= pow(max(dot(viewDir, reflectDir), 0.0), 32);
	spec[1]= pow(max(dot(viewDir, reflectDir2), 0.0), 32);

	vec3 specular = (spec[0]* light.specular[0])* light.lightColor[0];
	vec3 specular2 = (spec[1]* light.specular[1])* light.lightColor[1];

	vec3 result = vec3((ambient[0]*ambient[1]) + (diffuse[0]* diffuse[1]) + (specular[0]* specular[1]));
	
	
	fColor = vec4(result, 1.0f);
	
}