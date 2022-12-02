#pragma once
extern int musica;


#include <string>
#include <iostream>
#include "cocos2d.h"



class Nivel1 : public cocos2d::Layer
{
private:
	cocos2d::Sprite* jugador;
	cocos2d::Sprite* estrella;
	cocos2d::Sprite* corazon1;
	cocos2d::Sprite* corazon2;
	cocos2d::Sprite* corazon3;
	cocos2d::Sprite* estrella1;
	cocos2d::Sprite* estrella2;
	cocos2d::Label* labelScore;


	cocos2d::Vec2 pos;
	bool R = false;
	bool L = false;

	std::string nombres[6];

	cocos2d::Vec2 carril1 = cocos2d::Vec2(240, 950);
	cocos2d::Vec2 carril2 = cocos2d::Vec2(410, 950);
	cocos2d::Vec2 carril3 = cocos2d::Vec2(580, 950);

	cocos2d::Vec2 carril1b = cocos2d::Vec2(240, 80);
	cocos2d::Vec2 carril2b = cocos2d::Vec2(410, 80);
	cocos2d::Vec2 carril3b = cocos2d::Vec2(575, 80);

	int posCarril;
	int num;
	int lado;
	int numpiedra;

	bool choqueC = false;
	bool recogerEstrella = false;
	int contadorEstrella;

	int vidas = 3;
	int aux = 0;


public:

	static cocos2d::Scene* createScene();

	void update(float delta);

	virtual bool init();

	//void keyPressed(EventKeyboard::KeyCode* keycode, Event* event);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);


	void funcionCarritos(float delta);

	void funcionFondo(float delta);

	void funcionRandom(float delta);

	void funcionEstrella(float delta);

	bool onContactBegin(cocos2d::PhysicsContact& contact);

	void funcionRecogerEstrella(float delta);

	void funcionChoque(float delta);

	void Score(float delta);

	void Seconds(float delta);


	


	CREATE_FUNC(Nivel1);

};



