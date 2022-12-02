#include "audio/include/AudioEngine.h"
#include "Nivel3.h"
#include "Victory.h"
#include "GameOver.h"
#include "GameMenu.h"
#include "Nivel1.h"
#include "AppDelegate.h"
#include <fstream>
#include <iostream>
#include <string.h>


USING_NS_CC;

std::ofstream auxiliar;

bool Nivel3::archivo_existe(std::string nombre)
{
	std::ifstream archivo(nombre.c_str());
	return archivo.good();
}



cocos2d::Scene* Nivel3::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	auto layer = Nivel3::create();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->addChild(layer);
	return scene;
}


bool Nivel3::init()
{

	contadorEstrella = 0;
	srand(time(NULL));

	nombres[0] = "Ambulance.png";
	nombres[1] = "Audi.png";
	nombres[2] = "Car.png";
	nombres[3] = "Mini_truck.png";
	nombres[4] = "Police.png";
	nombres[5] = "taxi.png";





	//Variables de tamaño
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	const auto winSize =
		cocos2d::Director::getInstance()->getWinSize();




	//Agregar sprite jugador
	jugador = Sprite::create("Jugador.png");
	jugador->setAnchorPoint(Vec2(.5, .5));
	jugador->setPosition(Vec2(origin.x + visibleSize.width / 2 + 15,
		origin.y + 80));
	auto cuerpo = PhysicsBody::createBox(Size(jugador->getContentSize().width - 90, jugador->getContentSize().height - 30));
	cuerpo->setDynamic(false);
	cuerpo->setCollisionBitmask(1);
	cuerpo->setContactTestBitmask(true);
	jugador->setPhysicsBody(cuerpo);
	this->addChild(jugador, 100);


	//Event Listener
	auto listener = EventListenerKeyboard().create();
	listener->onKeyPressed = CC_CALLBACK_2(Nivel3::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Nivel3::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	//Estrella
	estrella = Sprite::create("star1.png");
	auto animation = Sequence::create(ScaleBy::create(.4, 1.1), ScaleBy::create(.4, .909), NULL);
	estrella->runAction(RepeatForever::create(animation));
	estrella->setScale(.07);
	auto cuerpoEstrella = PhysicsBody::createCircle(estrella->getContentSize().width / 2);
	cuerpoEstrella->setDynamic(false);
	cuerpoEstrella->setCollisionBitmask(3);
	cuerpoEstrella->setContactTestBitmask(true);
	estrella->setPhysicsBody(cuerpoEstrella);
	estrella->setVisible(false);
	this->addChild(estrella);


	//Corazones-Vidas
	corazon1 = Sprite::create("Corazon.png");
	corazon1->setScale(.1);
	corazon1->setPosition(Vec2(680, 850));
	corazon1->runAction(RepeatForever::create(animation->clone()));

	corazon2 = Sprite::create("Corazon.png");
	corazon2->setScale(.1);
	corazon2->setPosition(Vec2(730, 850));
	corazon2->runAction(RepeatForever::create(animation->clone()));


	corazon3 = Sprite::create("Corazon.png");
	corazon3->setScale(.1);
	corazon3->setPosition(Vec2(780, 850));
	corazon3->runAction(RepeatForever::create(animation->clone()));


	this->addChild(corazon1, 100);
	this->addChild(corazon2, 100);
	this->addChild(corazon3, 100);



	//Estrellas para ganar
	estrella1 = Sprite::create("star1.png");
	estrella1->setScale(.04);
	estrella1->setPosition(Vec2(40, 850));
	estrella1->runAction(RepeatForever::create(animation->clone()));
	estrella1->setVisible(false);

	estrella2 = Sprite::create("star1.png");
	estrella2->setScale(.04);
	estrella2->setPosition(Vec2(70, 850));
	estrella2->runAction(RepeatForever::create(animation->clone()));
	estrella2->setVisible(false);

	this->addChild(estrella1, 100);
	this->addChild(estrella2, 100);









	//Agregar fondo de nivel 1
	auto fondoMenu = Sprite::create("FondoNivel1 - copia.png");
	fondoMenu->setScale(1.73);
	fondoMenu->setAnchorPoint(Vec2::ZERO);
	fondoMenu->setPosition(0, -5);
	this->addChild(fondoMenu, -10);


	//Agregar titulo
	auto label = Label::createWithTTF("Level 3", "fonts/Marker Felt.ttf", 50);
	label->setPosition(Vec2(origin.x, visibleSize.height - label->getContentSize().height - 50));
	label->enableOutline(Color4B::RED, 5);
	label->enableShadow();
	label->setColor(Color3B::YELLOW);
	this->addChild(label, 0);
	auto moveBy = MoveBy::create(2.65, Vec2(1000, 0));
	label->runAction(moveBy);

	//Agregar Score
	labelScore = Label::createWithTTF("Score: ", "fonts/Marker Felt.ttf", 30);
	labelScore->setPosition(Vec2(730, 800));
	this->addChild(labelScore, 100);






	this->scheduleUpdate();
	this->schedule(CC_SCHEDULE_SELECTOR(Nivel3::funcionRandom), .1);
	this->schedule(CC_SCHEDULE_SELECTOR(Nivel3::funcionCarritos), .3);
	this->schedule(CC_SCHEDULE_SELECTOR(Nivel3::funcionEstrella), 5);
	this->schedule(CC_SCHEDULE_SELECTOR(Nivel3::funcionRecogerEstrella), .1);
	this->schedule(CC_SCHEDULE_SELECTOR(Nivel3::funcionChoque), .1);
	this->schedule(CC_SCHEDULE_SELECTOR(Nivel3::funcionFondo), .8);
	this->schedule(CC_SCHEDULE_SELECTOR(Nivel3::Score), .5);
	this->schedule(CC_SCHEDULE_SELECTOR(Nivel3::jugadorMov), .1);
	this->schedule(CC_SCHEDULE_SELECTOR(Nivel3::Seconds), 1);




	//Listener de colision
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Nivel3::onContactBegin, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);


	return true;
}


void Nivel3::funcionRandom(float detla)
{
	posCarril = 1 + rand() % 4;
	num = rand() % 6;

	lado = 1 + rand() % 3;
	numpiedra = 1 + rand() % 3;

	posy = 150 + rand() % 501;
}

void Nivel3::funcionCarritos(float delta)
{

	auto cuerpo2 = PhysicsBody::createBox(Size(jugador->getContentSize().width - 90, jugador->getContentSize().height - 30));
	cuerpo2->setDynamic(false);
	cuerpo2->setCollisionBitmask(2);
	cuerpo2->setContactTestBitmask(true);
	auto delayAction = DelayTime::create(2);
	auto avanzarCarrito = MoveBy::create(1.7, Vec2(0, -1200));
	auto sequence1 = Sequence::create(avanzarCarrito, delayAction, RemoveSelf::create(), NULL);
	auto carrito = Sprite::create(nombres[num]);
	carrito->setPhysicsBody(cuerpo2);

	auto linea = Sprite::create("Linea.png");
	linea->setRotation(90);
	linea->setPosition(Vec2(491, 1000));
	this->addChild(linea);


	auto linea2 = Sprite::create("Linea.png");
	linea2->setRotation(90);
	linea2->setPosition(Vec2(321, 1000));
	this->addChild(linea2);

	linea->runAction(sequence1->clone());
	linea2->runAction(sequence1->clone());





	if (posCarril == 1)
	{
		carrito->setPosition(carril1);
		carrito->setRotation(180);
		this->addChild(carrito);
		carrito->runAction(sequence1);
	}

	if (posCarril == 2)
	{
		carrito->setPosition(carril2);
		carrito->setRotation(180);
		this->addChild(carrito);
		carrito->runAction(sequence1);
	}

	if (posCarril == 3)
	{
		carrito->setPosition(carril3);
		carrito->setRotation(180);
		this->addChild(carrito);
		carrito->runAction(sequence1);
	}



}

void Nivel3::funcionFondo(float delta)
{

	auto moverObjetos = MoveBy::create(3, Vec2(0, -1200));
	auto delayAction = DelayTime::create(2);
	auto sequence1 = Sequence::create(moverObjetos, delayAction, RemoveSelf::create(), NULL);


	auto arbol = Sprite::create("Arbol.png");
	arbol->setScale(1.2);

	auto piedra1 = Sprite::create("Piedra1.png");
	piedra1->setScale(5);

	auto piedra2 = Sprite::create("Piedra2.png");


	auto piedra3 = Sprite::create("Piedra3.png");



	if (lado == 1)
	{
		arbol->setPosition(Vec2(70, 850));
		arbol->runAction(sequence1->clone());
		this->addChild(arbol);

	}
	if (lado == 2)
	{
		arbol->setPosition(Vec2(750, 850));
		arbol->runAction(sequence1->clone());
		this->addChild(arbol);
	}

	if (numpiedra == 1)
	{
		if (lado == 1)
		{
			piedra1->setPosition(80, 1000);
			piedra1->runAction(sequence1->clone());
			this->addChild(piedra1);
		}

		if (lado == 2)
		{
			piedra1->setPosition(750, 1000);
			piedra1->runAction(sequence1->clone());
			this->addChild(piedra1);
		}
	}

	if (numpiedra == 2)
	{
		if (lado == 1)
		{
			piedra2->setPosition(100, 1000);
			piedra2->runAction(sequence1->clone());
			this->addChild(piedra2);
		}

		if (lado == 2)
		{
			piedra2->setPosition(750, 1000);
			piedra2->runAction(sequence1->clone());
			this->addChild(piedra2);
		}
	}

	if (numpiedra == 3)
	{
		if (lado == 1)
		{
			piedra3->setPosition(30, 1000);
			piedra3->setRotation(180);
			piedra3->runAction(sequence1->clone());
			this->addChild(piedra3);
		}

		if (lado == 2)
		{
			piedra3->setPosition(780, 1000);
			piedra3->runAction(sequence1->clone());
			this->addChild(piedra3);
		}
	}

}

void Nivel3::funcionEstrella(float delta)
{
	carril1b.y = posy;
	carril2b.y = posy;
	carril3b.y = posy;

	if (posCarril == 1 && pos.x > 300)
	{
		estrella->setPosition(carril1b);
		estrella->setVisible(true);
	}

	if (posCarril == 2 && pos.x > 470 && pos.x < 300)
	{
		estrella->setPosition(carril2b);
		estrella->setVisible(true);
	}

	if (posCarril == 3 && pos.x < 500)
	{
		estrella->setPosition(carril3b);
		estrella->setVisible(true);
	}
}


void Nivel3::update(float deltaTime)
{

	pos = jugador->getPosition();
	if (pos.x <= 580 && R == true)
	{
		auto action2 = MoveBy::create(.1, Vec2(8, 0));
		jugador->runAction(action2);
	}

	if (pos.x >= 250 && L == true)
	{
		auto action2 = MoveBy::create(.1, Vec2(-8, 0));
		jugador->runAction(action2);
	}

	if (pos.y < 600 && U)
	{
		auto action = MoveBy::create(.1, Vec2(0, 8));
		jugador->runAction(action);

	}

	if (contadorEstrella == 3)
	{	
		if (finalScore < score)
		{
			auxiliar.open("Auxiliar.txt",std::ios::app);
			auxiliar << score;
			auxiliar.close();
			if (archivo_existe("Puntuacion.txt"))
			{
				remove("Puntuacion.txt");

			}
			if (rename("Auxiliar.txt", "Puntuacion.txt") == 0) {
				CCLOG("Renombrado");
			}
			else {
				CCLOG("Hubo un error");
			}
		}
		AudioEngine::stopAll();
		auto victory = Scene::createWithPhysics();
		victory->addChild(Victory::createScene());
		Director::getInstance()->replaceScene(victory);
	}

	if (vidas == 0)
	{
		score = 0;
		auto GameOver = Scene::create();
		GameOver->addChild(GameOver::createScene());
		int musica = AudioEngine::play2d("GameOver.mp3", false, 10);
		Director::getInstance()->replaceScene(GameOver);
	}

	if (aux == 5)
	{
		auto label = Label::createWithTTF("Keep Moving!!!!", "fonts/Marker Felt.ttf", 50);
		label->setPosition(Vec2(420, 500));
		label->enableOutline(Color4B::RED, 5);
		label->enableShadow();
		label->setColor(Color3B::YELLOW);
		auto animation = Sequence::create(ScaleBy::create(.1, 1.1), ScaleBy::create(.1, .909), NULL);
		auto secuencia = Sequence::create(Repeat::create(animation, 8), RemoveSelf::create(), NULL);
		label->runAction(secuencia);
		this->addChild(label, 100);

		vidas--;

		if (vidas == 2)
		{
			corazon3->removeFromParentAndCleanup(true);
		}
		if (vidas == 1)
		{
			corazon2->removeFromParentAndCleanup(true);
		}
		aux = 0;
	}


}

void Nivel3::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	if (key == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		R = true;
		aux = 0;

	}

	if (key == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		L = true;
		aux = 0;
	}

	if (key == EventKeyboard::KeyCode::KEY_SPACE)
	{
		U = true;
	}
}

void Nivel3::onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
{
	if (key == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		R = false;
	}

	if (key == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		L = false;
	}

	if (key == EventKeyboard::KeyCode::KEY_SPACE)
	{
		U = false;
	}
}


bool Nivel3::onContactBegin(PhysicsContact& contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
	{
		AudioEngine::play2d("Choque.mp3", false);
		choqueC = true;
	}

	if ((1 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask()) || (3 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
	{
		AudioEngine::play2d("StarSound.mp3", false);
		recogerEstrella = true;
	}

	return true;
}

void Nivel3::funcionRecogerEstrella(float delta)
{
	if (recogerEstrella)
	{
		contadorEstrella++;
		estrella->setVisible(false);
		estrella->setPosition(Vec2(0, 0));
		recogerEstrella = false;
	}
	if (contadorEstrella == 1)
	{
		estrella1->setVisible(true);
	}
	if (contadorEstrella == 2)
	{
		estrella2->setVisible(true);
	}


}

void Nivel3::funcionChoque(float delta)
{
	if (choqueC)
	{

		if (score - 500 < 0)
		{
			score = 0;
			std::string cad = "Score: 0";
			labelScore->setString(cad);
		}
		else {
			score -= 500;
		}
		auto choque = Spawn::create(Sequence::create(RotateBy::create(.1, 90), RotateTo::create(.1, 0), NULL),
			Sequence::create(FadeTo::create(.2, 50), FadeTo::create(.2, 255), FadeTo::create(.2, 50), FadeTo::create(.2, 255), NULL), NULL);

		jugador->runAction(choque);
		choqueC = false;
		vidas--;
		if (vidas == 2)
		{
			corazon3->removeFromParentAndCleanup(true);
		}
		if (vidas == 1)
		{
			corazon2->removeFromParentAndCleanup(true);
		}
	}
}

void Nivel3::Score(float delta)
{
	if (score != 0)
	{
		if (score - 10 < 0)
		{
			score = 0;
			std::string cad = "Score: 0";
			labelScore->setString(cad);
			return;
		}
		score -= 10;
		std::string secs = std::to_string(score);
		std::string cad = "Score: " + secs;
		labelScore->setString(cad);
	}
}

void Nivel3::jugadorMov(float delata)
{
	auto bajar = MoveBy::create(.1, Vec2(0, -15));
	if (pos.y > 80)
	{
		jugador->runAction(bajar);
	}
}

void Nivel3::Seconds(float delta)
{
	aux++;
}













