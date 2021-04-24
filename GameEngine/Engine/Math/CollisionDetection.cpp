#include "CollisionDetection.h"
#include "Ray.h"
#include "../Core/MEngine.h"
CollisionDetection::~CollisionDetection()
{
}

Ray CollisionDetection::MousePosToWorldRay(glm::vec2 mouseCoords_, float screenWidth_, float screenHeight_, Camera* camera_)
{
	//find ray start and end pos
	//moseu coord in ndc(normal device coordinate) get into world space
	glm::vec4 rayStartNDC((mouseCoords_.x / screenWidth_ - 0.5f) * 2.0f, (mouseCoords_.y / screenHeight_ - 0.5f) * 2.0f,
		-1.0f, 1.0f);

	glm::vec4 rayEndNDC((mouseCoords_.x / screenWidth_ - 0.5f) * 2.0f, (mouseCoords_.y / screenHeight_ - 0.5f) * 2.0f,
		-1.0f, 1.0f);

	//ndc backward to world
	glm::mat4 inverse = glm::inverse(camera_->GetPerspective() * camera_->GetView());

	glm::vec4 rayStartWorld = inverse * rayStartNDC;
	rayStartWorld /= rayStartWorld.w;

	glm::vec4 rayEndWorld = inverse * rayEndNDC;
	rayEndWorld /= rayEndWorld.w;

	glm::vec3 rayDirWorld(rayEndWorld - rayStartWorld);
	rayDirWorld = glm::normalize(rayDirWorld);

	return Ray(glm::vec3(rayStartWorld), rayDirWorld);
}

bool CollisionDetection::RayObbIntersection(Ray* ray_, BoundingBox* box_)
{
	//hold box transformation matrix
	glm::mat4 modelMatrix = box_->transform;

	glm::vec3 rayOrigin = ray_->origin;
	glm::vec3 rayDirection = ray_->direction;
	//hold box min max 
	glm::vec3 boxMin = box_->minVert;
	glm::vec3 boxMax = box_->maxVert;

	float tMin = MEngine::GetInstance()->GetCamera()->GetNearPlane();
	float tMax = MEngine::GetInstance()->GetCamera()->GetFarPlane();


	glm::vec3 worldPos(modelMatrix[3].x, modelMatrix[3].y, modelMatrix[3].z);
	glm::vec3 delta = worldPos - rayOrigin;

	//x axis
	glm::vec3 xAxis(modelMatrix[0].x, modelMatrix[0].y, modelMatrix[0].z);
	float dotDelta = glm::dot(delta, xAxis);
	float dotDir = glm::dot(rayDirection, xAxis);

	//ensure not divide by 9 fab(absolute of a float)
	if (fabs(dotDir) > 0.001f) {
		//left and right plane
		float t1 = (dotDelta + boxMin.x) / dotDir;
		float t2 = (dotDelta + boxMax.x) / dotDir;

		if (t1 > t2) {
			
			float w = t1;
			//std::swap(t1, t2);
			t1 = t2;
			t2 = w;
		}

		if (t2 < tMax) {
			tMax = t2;
		}

		if (t1 > tMin) {
			tMin = t1;
		}

		if (tMin > tMax) {
			return false;
		}


	}
	else {
		if (-dotDelta + boxMin.x > 0.0f || -dotDelta + boxMax.x < 0.0f) {
			return false;
		}
	}
	//if (fabs(dotDir) > 0.001f) {}
	{
		float t3 = (dotDelta + boxMin.y) / dotDir;
		float t4 = (dotDelta + boxMax.y) / dotDir;

		if (t3 > t4) {
			float w = t3;
			t3 = t4;
			t4 = w;
		}

		if (t4 < tMax) {
			tMax = t4;
		}

		if (t3 > tMin) {
			tMin = t3;
		}


		float t5 = (dotDelta + boxMin.z) / dotDir;
		float t6 = (dotDelta + boxMax.z) / dotDir;

		if (t5 > t6) {
			float w = t5;
			t5 = t6;
			t6 = w;
		}

		if (t6 < tMax) {
			tMax = t6;
		}
		if (t5 > tMin) {
			tMin = t5;
		}
	}
	
	ray_->intersectionDist = tMin;
	return true;
}
