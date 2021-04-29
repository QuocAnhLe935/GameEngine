#include "CollisionHandler.h"
#include "../Core/MEngine.h"

std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
//std::vector<GameObject*> CollisionHandler::colliders = std::vector<GameObject*>();
std::vector<GameObject*> CollisionHandler::prevCollisions = std::vector<GameObject*>();
OctSpatialPartion* CollisionHandler::scenePartition = nullptr;


CollisionHandler* CollisionHandler::GetInstance()
{
    if (collisionInstance.get() == nullptr) {
        collisionInstance.reset(new CollisionHandler);

    }

    return collisionInstance.get();
}

void CollisionHandler::OnCreate(float worldsize_)
{
    scenePartition = new OctSpatialPartion(worldsize_);
    prevCollisions.clear();
}
//add colliable object to colliable gameobject on s
void CollisionHandler::AddObject(GameObject* go_)
{
    if (scenePartition != nullptr) {
        scenePartition->AddObject(go_);
    }
}

void CollisionHandler::MouseUpdate(glm::vec2 mousePos_, int buttonType_)
{
    Ray mouseRay = CollisionDetection::MousePosToWorldRay(mousePos_, MEngine::GetInstance()->GetScreenWidth(),
        MEngine::GetInstance()->GetScreenHeight(), MEngine::GetInstance()->GetCamera());
        
    GameObject* hitResult = nullptr;
    float shortestDistance = FLT_MAX;

    //loop all colliable objects
    if (scenePartition != nullptr) {
        GameObject* hitResult = scenePartition->GetCollision(mouseRay);

        if (hitResult) {
            hitResult->SetHit(true, buttonType_);
        }

        //prev hit that not hit anymore
        for (auto c : prevCollisions) {
            if (hitResult != c && c != nullptr) {
                c->SetHit(false, buttonType_);
            }
            c = nullptr;
        }

        prevCollisions.clear();

        //prev nto hit again
        if (hitResult) {
            prevCollisions.push_back(hitResult);
        }
    }
}

void CollisionHandler::OnDestroy()
{
   
    delete scenePartition;
    scenePartition = nullptr;

    for (auto entry : prevCollisions) {
        entry = nullptr;
    }
    prevCollisions.clear();
}

CollisionHandler::CollisionHandler(){
   
    prevCollisions.reserve(10);
}

CollisionHandler::~CollisionHandler()
{
    OnDestroy();
}
