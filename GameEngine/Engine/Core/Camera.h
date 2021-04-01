#ifndef  CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../FX/LightSource.h"
#include <vector>

class Camera
{
public:
	Camera();
	~Camera();
	
	void SetPosition(glm::vec3 position_);
	void SetRotation(float yaw_, float pitch_);

	glm::mat4 GetView() const;
	glm::mat4 GetPerspective() const;
	glm::mat4 GetOrthographic()const;
	glm::vec3 GetPosition() const;


	//void Getlights(std::string name);
	void Addlight(LightSource* lightsource_);
	 std::vector<LightSource*> get_light() const;
	
	
	

private:
	void UpdateCameraVectors();
	glm::vec3 position;
	glm::mat4 perspective, orthorgraphic, view;
	float fieldOfView;
	float yaw, pitch;
	float nearPlane, farPlane;
	//camera upward direction(forward), worldup is a ref to what dir is
	glm::vec3 forward, up, right, worldUp;

	std::vector<LightSource*> lightS;
	
};

#endif // ! CAMERA_H