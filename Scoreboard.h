#pragma once

#include "cocos2d.h"


class Scoreboard : public cocos2d::Layer
{
private:

public:

	static cocos2d::Scene* createScene();

	void update(float deltaTime);

	virtual bool init();

	void menuButtonPressed(cocos2d::Ref* pSender);

	bool archivo_existe(std::string nombre);


	CREATE_FUNC(Scoreboard);

};