#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H
#include <glm/glm.hpp>

class LightSource
{
public:
	LightSource();
	~LightSource();

	float getAmbient() const;
	float getDiffuse() const;
	float getSpecular() const;
	glm::vec3 getPosition() const;
	glm::vec3 getLightColor() const;

	void setAmbient(float Ambient_);
	void setDiffuse(float Diffuse_);
	void setSpecular(float Specular_);
	void setPosition(glm::vec3 position_);
	void setLightColor(glm::vec3 lightcolor_);

private:
	glm::vec3 position;
	float ambient;
	float diffuse;
	float specular;
	glm::vec3 lightColor;

};

#endif 