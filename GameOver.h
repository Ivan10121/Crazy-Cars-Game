#pragma once

#include "cocos2d.h"

class GameOver : public cocos2d::Layer
{
private:

public:

	static cocos2d::Scene* createScene();

	void update(float deltaTime);

	virtual bool init();


	CREATE_FUNC(GameOver);

};