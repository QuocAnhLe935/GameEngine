#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>
#include "BoundingBox.h"
#include"CollisionDetection.h"

struct Ray {
	glm::vec3 origin;
	glm::vec3 direction;
	float intersectionDist;
	inline Ray() {
		//default all 0
		origin = glm::vec3();
		direction = glm::vec3();
		intersectionDist = 0.0f;
	}
	//set
	inline Ray(glm::vec3 origin_, glm::vec3 direction_) {
		origin = origin_;
		direction = direction_;
		intersectionDist = 0.0f;
	}
	//overload define special things for operators
	inline Ray& operator=(const Ray& ray_) {
		origin = ray_.origin;
		direction = ray_.direction;
		intersectionDist = 0.0f;
	}

	inline bool IsColliding(BoundingBox* box_) {
		intersectionDist = -1.0f;
		return CollisionDetection::RayObbIntersection(this, box_);
	}
};



#endif
