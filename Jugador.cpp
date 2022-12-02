#include "Jugador.h"
USING_NS_CC;

Sprite* Jugador::createJugador()
{
	auto* player = Sprite::create();
	auto* x = Jugador::create();
	player = x;
	return player;
}

bool Jugador::init()
{	
	auto jugador = Sprite::create("Black_viper.png");
	jugador->setPosition(Vec2::ZERO);
	return true;
}


Jugador::Jugador()
{
	init();
}

Jugador::~Jugador()
{
}
