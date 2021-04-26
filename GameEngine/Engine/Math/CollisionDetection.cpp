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

	//object world pos last column of model matrix of the box
	glm::vec3 worldPos(modelMatrix[3].x, modelMatrix[3].y, modelMatrix[3].z);
	glm::vec3 delta = worldPos - rayOrigin;

	//x axis
	glm::vec3 xAxis(modelMatrix[0].x, modelMatrix[0].y, modelMatrix[0].z);
	float dotDelta = glm::dot(delta, xAxis);
	float dotDir = glm::dot(rayDirection, xAxis);


	glm::vec3 yAxis(modelMatrix[1].x, modelMatrix[1].y, modelMatrix[1].z);
	float dotDelta1 = glm::dot(delta, yAxis);
	float dotDir1 = glm::dot(rayDirection, yAxis);

	glm::vec3 zAxis(modelMatrix[2].x, modelMatrix[2].y, modelMatrix[2].z);
	float dotDelta2 = glm::dot(delta, zAxis);
	float dotDir2 = glm::dot(rayDirection, zAxis);

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

	/*{
		float t3 = (dotDelta1 + boxMin.y) / dotDir1;
		float t4 = (dotDelta1 + boxMax.y) / dotDir1;

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


		float t5 = (dotDelta2 + boxMin.z) / dotDir2;
		float t6 = (dotDelta2 + boxMax.z) / dotDir2;

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
	}*/
	if (fabs(dotDir1) > 0.001f) {
		float t3 = (dotDelta1 + boxMin.y) / dotDir1;
		float t4 = (dotDelta1 + boxMax.y) / dotDir1;

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
	}
	else {

		if (-dotDelta1 + boxMin.y > 0.0f || -dotDelta1 + boxMax.y < 0.0f) {
			return false;
		}
	}



	if (fabs(dotDir2) > 0.001f) {


		float t5 = (dotDelta2 + boxMin.z) / dotDir2;
		float t6 = (dotDelta2 + boxMax.z) / dotDir2;

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
	else {

		if (-dotDelta2 + boxMin.z > 0.0f || -dotDelta2 + boxMax.z < 0.0f) {
			return false;
		}
	}



	ray_->intersectionDist = tMin;
	return true;
}
