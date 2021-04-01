#include "LightSource.h"

LightSource::LightSource()
{
}

LightSource::~LightSource()
{
}

float LightSource::getAmbient() const
{
    return ambient;
}

float LightSource::getDiffuse() const
{
    return diffuse;
}

float LightSource::getSpecular() const
{
    return specular;
}

glm::vec3 LightSource::getPosition() const
{
    return position;
}

glm::vec3 LightSource::getLightColor() const
{
    return lightColor;
}

void LightSource::setAmbient(float Ambient_)
{
    ambient = Ambient_;
    
}

void LightSource::setDiffuse(float Diffuse_)
{
    diffuse = Diffuse_;
}

void LightSource::setSpecular(float Specular_)
{
    specular = Specular_;
}

void LightSource::setPosition(glm::vec3 position_)
{
    position = position_;
}

void LightSource::setLightColor(glm::vec3 lightcolor_)
{
    lightColor = lightcolor_;
}
