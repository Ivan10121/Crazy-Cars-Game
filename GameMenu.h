#pragma once

extern int finalScore;

#include "cocos2d.h"
#include "Nivel1.h"
#include "Nivel2.h"
#include "Nivel3.h"


class GameMenu : public cocos2d::Layer
{
private:
	int musicaa;

public:
	static cocos2d::Scene* createScene();

	void update(float deltaTime);

	virtual bool init();

	void playButtonPressed(cocos2d::Ref* pSender);

	void scoreboardButtonPressed(cocos2d::Ref* pSender);

	bool archivo_existe(std::string nombre);





	CREATE_FUNC(GameMenu);

};

