#include "CollisionHandler.h"
#include "../Core/MEngine.h"

std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*> CollisionHandler::colliders = std::vector<GameObject*>();
std::vector<GameObject*> CollisionHandler::prevCollisions = std::vector<GameObject*>();


CollisionHandler* CollisionHandler::GetInstance()
{
    if (collisionInstance.get() == nullptr) {
        collisionInstance.reset(new CollisionHandler);

    }

    return collisionInstance.get();
}

void CollisionHandler::OnCreate()
{
    colliders.clear();
    prevCollisions.clear();
}
//add colliable object to colliable gameobject on s
void CollisionHandler::AddObject(GameObject* go_)
{
    colliders.push_back(go_);
}

void CollisionHandler::MouseUpdate(glm::vec2 mousePos_, int buttonType_)
{
    Ray mouseRay = CollisionDetection::MousePosToWorldRay(mousePos_, MEngine::GetInstance()->GetScreenWidth(),
        MEngine::GetInstance()->GetScreenHeight(), MEngine::GetInstance()->GetCamera());
        
    GameObject* hitResult = nullptr;
    float shortestDistance = 1000000.0f;

    //loop all colliable objects
    for (auto g : colliders) {
        //if ray collide with boudning box
        if (mouseRay.IsColliding(&g->GetBoundingBox())) {
            //
            if (mouseRay.intersectionDist < shortestDistance) {
                hitResult = g;
                shortestDistance = mouseRay.intersectionDist;
            }
        }
    }
    if (hitResult) {
        hitResult->SetHit(true, buttonType_);
    }
    //prev hit that not hit anymore
    for (auto c : prevCollisions) {
        if (hitResult != c && c != nullptr) {
            c->SetHit(false, buttonType_);
        }
    }

    prevCollisions.clear();
    //prev nto hit again
    if (hitResult) {
        prevCollisions.push_back(hitResult);
    }
}

void CollisionHandler::OnDestroy()
{
    for (auto entry : colliders) {
        entry = nullptr;
    }
    colliders.clear();

    for (auto entry : prevCollisions) {
        entry = nullptr;
    }
    prevCollisions.clear();
}

CollisionHandler::CollisionHandler(){
    colliders.reserve(10);
    prevCollisions.reserve(10);
}

CollisionHandler::~CollisionHandler()
{
    OnDestroy();
}
