#version 460 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPosition;


//uniform sampler2D inputTexture;
uniform vec3 viewPosition;
uniform vec3 cameraPosistion;
uniform sampler2D diffuseMap;

out vec4 fColor;


struct Light{

vec3 lightPos;
float ambient;
float diffuse;
float specular;
vec3 lightColor;

};

struct Material{
	int diffuseMap;
	float shininess; //Ns
	float transparency; //d

	vec3 ambient;//ka
	vec3 diffuse; //kd
	vec3 specular; //ks
};

uniform Light light;
uniform Material material;

void main(){
	
	//ambient
	vec3 ambient = light.ambient* material.ambient* texture(diffuseMap, TexCoords).rgb* light.lightColor;
	//Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos - FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff* material.diffuse)* texture(diffuseMap, TexCoords).rgb* light.lightColor;

	//Specular
	vec3 viewDir = normalize(viewPosition-FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (spec* material.specular)* light.lightColor;

	vec3 result = ambient + diffuse + specular;

	fColor = vec4(result, material.transparency);
}