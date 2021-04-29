#include "OctSpatialPartion.h"
int OctNode::childNum = 0;

OctNode::OctNode(glm::vec3 position_, float size_, OctNode* parent_): children()
{
	octBounds = nullptr;
	parent = nullptr;
	objectList = std::vector<GameObject*>();
	objectList.reserve(10);
	octBounds = new BoundingBox();
	octBounds->minVert = position_;
	octBounds->maxVert = position_ + glm::vec3(size_);

	size = size_;
	parent = parent_;

	for (int i = 0; i < CHILDERN_NUMBER; i++) {
		children[i] = nullptr;
	}
	
}

OctNode::~OctNode()
{
	delete octBounds;
	octBounds = nullptr;

	if (objectList.size() > 0) {
		for (auto obj : objectList) {
			obj = nullptr;
		}
		objectList.clear();
	}

	for (int i = 0; i < CHILDERN_NUMBER; i++) {
		if (children[i] != nullptr) {
			delete children[i];
		}
		children[i] = nullptr;
	}
}

void OctNode::Octify(int depth_)
{
	if (depth_ > 0 && this) {
		//child is half the size of parent
		float half = size / 2.0f;
		children[static_cast<int>(OctChildren::OCT_TLF)] = new OctNode(
			glm::vec3(octBounds->minVert.x, octBounds->minVert.y + half,
				octBounds->minVert.z + half), half, this);
		//this specific octnode is creating its children

		{
		children[static_cast<int>(OctChildren::OCT_BLF)] = new OctNode(
			glm::vec3(octBounds->minVert.x, octBounds->minVert.y,
				octBounds->minVert.z + half), half, this);

		children[static_cast<int>(OctChildren::OCT_BRF)] = new OctNode(
			glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y ,
				octBounds->minVert.z + half), half, this);

		children[static_cast<int>(OctChildren::OCT_TRF)] = new OctNode(
			glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y + half,
				octBounds->minVert.z + half), half, this);

		children[static_cast<int>(OctChildren::OCT_TLR)] = new OctNode(
			glm::vec3(octBounds->minVert.x, octBounds->minVert.y + half,
				octBounds->minVert.z), half, this);

		children[static_cast<int>(OctChildren::OCT_BLR)] = new OctNode(
			glm::vec3(octBounds->minVert.x, octBounds->minVert.y ,
				octBounds->minVert.z ), half, this);

		children[static_cast<int>(OctChildren::OCT_BRR)] = new OctNode(
			glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y ,
				octBounds->minVert.z ), half, this);

		children[static_cast<int>(OctChildren::OCT_TRR)] = new OctNode(
			glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y + half,
				octBounds->minVert.z ), half, this);
	}

		childNum += 8;
	}


	//verify depth exists
	if (depth_ > 0 && this) {
		//each child
		for (int i = 0; i < CHILDERN_NUMBER; i++) {
			//line 45 depth=1 -1 =0 if statement will stop

			children[i]->Octify(depth_ - 1);
		}
	}
}

OctNode* OctNode::GetParent()
{
	return parent;
}

OctNode* OctNode::GetChild(OctChildren childPos_)
{
	return children[static_cast<int>(childPos_)];
}

void OctNode::AddCollisionObject(GameObject* obj_)
{
	objectList.push_back(obj_);
}

int OctNode::GetObjectCount() const
{
	return objectList.size();
}

bool OctNode::IsLeaf() const
{
	if (children[0] == nullptr) {
		return true;
	}
	return false;
}

BoundingBox* OctNode::GetBoundingBox() const
{
	return octBounds;
}

int OctNode::GetChildCount() const
{
	return childNum;
}

OctSpatialPartion::OctSpatialPartion(float worldSize_)
{
	root = nullptr;
	rayIntersectionList = std::vector<OctNode*>();
	//oct node pos, size, parent
	root = new OctNode(glm::vec3(-(worldSize_ / 2.0f)), worldSize_, nullptr);
	root->Octify(3);
	std::cout << "There are " << root->GetChildCount() << " child nodes" << std::endl;
	rayIntersectionList.reserve(20);
}

OctSpatialPartion::~OctSpatialPartion()
{
	if (rayIntersectionList.size() > 0) {
		for (auto cell : rayIntersectionList) {
			cell = nullptr;
		}
		rayIntersectionList.clear();
	}

	delete root;
	root = nullptr;
}
//call private function
void OctSpatialPartion::AddObject(GameObject* obj_)
{
	AddObjectToCell(root, obj_);
}

GameObject* OctSpatialPartion::GetCollision(Ray ray_)
{
	//clearing out prev collision
	if (rayIntersectionList.size() > 0) {
		for (auto cell : rayIntersectionList) {
			cell = nullptr;
		}
		rayIntersectionList.clear();
	}
	PrepareCollisionQuery(root, ray_);

	//create game object pointer represent result
	GameObject* result = nullptr;
	float shortestDistance = FLT_MAX;

	for (auto cell : rayIntersectionList) {
		for (auto obj : cell->objectList) {
			//if ray collided with bounding box
			BoundingBox b;
			b = obj->GetBoundingBox();
			if (ray_.IsColliding(&b)) {
				if (ray_.intersectionDist < shortestDistance) {
					result = obj;
					shortestDistance = ray_.intersectionDist;
				}
			}
		}
		if(result!=nullptr){
			return result;
		}
	}
	return nullptr;
}

void OctSpatialPartion::AddObjectToCell(OctNode* cell_, GameObject* obj_)
{
	//leaf
	if (cell_ != nullptr) {
		BoundingBox* b = cell_->GetBoundingBox();
		BoundingBox c = obj_->GetBoundingBox();
		if(b->Intersects(&c)){
		
			if (cell_->IsLeaf() == true) {
				//if game obj bounding box collide with that node bounding box
				cell_->AddCollisionObject(obj_);
			}
			//leaf not node
			else {
				for (size_t i = 0; i < CHILDERN_NUMBER; i++)
				{
					AddObjectToCell(cell_->children[i], obj_);
				}
			}
		
		}
		
	}
	
	
}

void OctSpatialPartion::PrepareCollisionQuery(OctNode* cell_, Ray ray_)
{
	////leaf
	if (cell_!=nullptr) {
		if (ray_.IsColliding(cell_->GetBoundingBox())) {
			//node get added to rayintersectionlist vector;
			if (cell_->IsLeaf() == true) {
			
				rayIntersectionList.push_back(cell_);
			
			}
			else {
				for (size_t i = 0; i < CHILDERN_NUMBER; i++) {
					PrepareCollisionQuery(cell_->children[i], ray_);
				}
			}
		}
	}

	//[static_cast<int>(
}
