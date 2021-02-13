#ifndef SCENE_H
#define SCENE_H

class Scene {
public:
	Scene(){}
	virtual ~Scene(){}

	virtual bool OnCreate() = 0;
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render() = 0;
};


#endif // !SCENE_H
