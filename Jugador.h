#pragma once
#include "cocos2d.h"

class Jugador : public cocos2d::Sprite
{
private:


public :

	static cocos2d::Sprite* createJugador();

	virtual bool init();

	Jugador();

	~Jugador();

	CREATE_FUNC(Jugador);
};

