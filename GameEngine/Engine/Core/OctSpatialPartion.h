#ifndef OCTSPATIALPARTION_H
#define OCTSPATIALPARTION_H

#include "../Math/Ray.h"
#include "../Rendering/3D/GameObject.h"

constexpr auto CHILDERN_NUMBER = 8;

enum class OctChildren {
	//T=top L=left R=right or rear after second T r is rear
	OCT_TLF, OCT_BLF, OCT_BRF, OCT_TRF, OCT_TLR, OCT_BLR, OCT_BRR, OCT_TRR
};

class OctNode {
public:
	OctNode(glm::vec3 position_, float size_, OctNode* parent_);
	~OctNode();
	void Octify(int depth_);
	OctNode* GetParent();
	OctNode* GetChild(OctChildren childPos_);
	//any colliable add to the list
	void AddCollisionObject(GameObject* obj_);
	//get numb of object from specific node
	int GetObjectCount() const;
	bool IsLeaf() const;
	BoundingBox* GetBoundingBox() const;
	int GetChildCount() const;

private:
	friend class OctSpatialPartion;
	
	BoundingBox* octBounds;
	OctNode* parent;
	
	OctNode* children[CHILDERN_NUMBER];
	std::vector<GameObject*>objectList;
	float size;
	static int childNum;
};

class OctSpatialPartion
{
public:
	OctSpatialPartion(float worldSize_);
	~OctSpatialPartion();
	void AddObject(GameObject* obj_);
	GameObject* GetCollision(Ray ray_);
private:
	OctNode* root;
	std::vector<OctNode*> rayIntersectionList;
	//if game object collide with leaf oct node then add game object to leaf node
	void AddObjectToCell(OctNode* cell_, GameObject* obj_);
	void PrepareCollisionQuery(OctNode* cell_, Ray ray_);
};

#endif // OCTSPATIALPARTION