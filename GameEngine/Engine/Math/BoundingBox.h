#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

struct BoundingBox {
	glm::vec3 maxVert, minVert;
	glm::mat4 transform;

	//default maxmintrans emmpty vector
	inline BoundingBox() {
		maxVert = minVert = glm::vec3();
		transform = glm::mat4();
	}

	inline BoundingBox(glm::vec3 maxVert_, glm::vec3 minVert_, glm::mat4 transform_) {
		maxVert = maxVert_;
		minVert = minVert_;
		transform = transform_;
	}

	inline bool Intersects(BoundingBox* b_) {
		glm::vec3 minCorner = GetTransformedPoint(minVert, transform);
		glm::vec3 maxCorner = GetTransformedPoint(maxVert, transform);

		glm::vec3 otherMinCorner= GetTransformedPoint(b_->minVert, b_->transform);
		glm::vec3 otherMaxCorner = GetTransformedPoint(b_->maxVert, b_->transform);

		return true;
	}
private:
	//tranformation matrix
	inline glm::vec3 GetTransformedPoint(glm::vec3 point_, glm::mat4 transform_){
		return glm::vec3(transform_[3].x, transform_[3].y, transform_[3].z) + point_;
	}
};
#endif // !BOUNDINGBOX_H

