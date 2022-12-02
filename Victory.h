#pragma once

#include "cocos2d.h"





class Victory : public cocos2d::Layer
{
private:
	int musica;

public:
	static cocos2d::Scene* createScene();

	void update(float deltaTime);

	virtual bool init();

	void playAgainButtonPressed(cocos2d::Ref* pSender);

	void menuButtonPressed(cocos2d::Ref* pSender);




	CREATE_FUNC(Victory);

};

