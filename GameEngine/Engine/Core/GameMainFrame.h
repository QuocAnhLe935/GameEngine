#ifndef GAMEMAINFRAME_H
#define GAMEMAINFRAME_H


class GameMainFrame
{
public:
	GameMainFrame(){}
	virtual ~GameMainFrame(){}
	//=0 means is not making define 
	virtual bool OnCreate() = 0;
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render() = 0;
};

#endif // ! GAMEMAINFRAME_H