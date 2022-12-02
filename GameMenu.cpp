#include "GameMenu.h"
#include "Scoreboard.h"
#include <string>
#include "audio/include/AudioEngine.h"
#include <fstream>
USING_NS_CC;

int finalScore;


cocos2d::Scene* GameMenu::createScene()
{	
	Scene* scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vect(0, 0));
	auto* layer = GameMenu::create();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->addChild(layer);
	return scene;
}

void GameMenu::update(float deltaTime)
{

}

bool GameMenu::archivo_existe(std::string nombre)
{
	std::ifstream archivo(nombre.c_str());
	return archivo.good();
}

bool GameMenu::init()
{

	if (archivo_existe("Puntuacion.txt"))
	{
		std::ifstream arch;
		arch.open("Puntuacion.txt", std::ios::in);
		int x;
		arch >> x;
		finalScore = x;
		arch.close();
	}
	else {
		finalScore = 0;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	const auto winSize =
		cocos2d::Director::getInstance()->getWinSize();

	//Fondo
	auto fondoMenu = Sprite::create("MenuB.jpg");
	fondoMenu->setAnchorPoint(Vec2::ZERO);
	this->addChild(fondoMenu,0);

	//Titulo
	auto label = Label::createWithTTF("Crazy cars", "fonts/Marker Felt.ttf", 75);
	label->enableOutline(Color4B::RED,5);
	label->enableShadow();
	label->setColor(Color3B::YELLOW);
	auto animation = Sequence::create(ScaleBy::create(.4, 1.1), ScaleBy::create(.4, .909), NULL);
	auto action = RepeatForever::create(animation);
	label->runAction(action);



	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		visibleSize.height - label->getContentSize().height - 50));
	this->addChild(label);

	//Sprites de carros
	auto carro1 = Sprite::create("Police.png");
	auto carro2 = Sprite::create("Audi.png");
	

	//Posicion de carros
	carro1->setPosition(Vec2(origin.x + 10 + carro1->getContentSize().width,origin.y + 30 + carro1->getContentSize().height));
	carro2->setPosition(Vec2(origin.x - 10 + visibleSize.width - carro2->getContentSize().width, origin.y + 30 + carro2->getContentSize().height));

	//Tamaño de carros
	carro1->setScale(2);
	carro2->setScale(2);

	//Agregar sprites de carros
	this->addChild(carro1);
	this->addChild(carro2);

	//Botones para play
	auto playNormal = Sprite::create("BotonPlay.png");
	auto playSelected = Sprite::create("PlaySelected.png");		
	auto playDisable = Sprite::create("BotonPlay.png");	

	//Botones para ScoreBoard
	auto scoreboardNormal = Sprite::create("Scoreboard.png");
	auto scoreboardSelected = Sprite::create("ScoreboardSelected.png");
	auto scoreboardDisable = Sprite::create("Scoreboard.png");



	//Menu item para boton play
	auto play = MenuItemSprite::create(
		playNormal,playSelected,playDisable,
		CC_CALLBACK_1(GameMenu::playButtonPressed,this));

	auto scoreboard = MenuItemSprite::create(
		scoreboardNormal, scoreboardSelected, scoreboardDisable,
		CC_CALLBACK_1(GameMenu::scoreboardButtonPressed,this));

	


	//auto menu = Menu::create(play,scoreboard,nullptr);
	auto menu = Menu::create(play, scoreboard, NULL);
	menu->alignItemsVerticallyWithPadding(20);


	menu->setContentSize(Size(0, 0));
	float x = origin.x + visibleSize.width/2;
	float y = origin.y + visibleSize.height/2 + 50;
	menu->setPosition(Vec2(x, y));


	menu->setScale(.9);




	this->addChild(menu,1);



	return true;
}
 
void GameMenu::playButtonPressed(cocos2d::Ref* sender)
{
	AudioEngine::stopAll();
	auto nivel1 = Scene::createWithPhysics();
	//nivel1->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); 
	nivel1->addChild(Nivel1::createScene());
	Director::getInstance()->replaceScene(TransitionFade::create(1.5,nivel1));
}

void GameMenu::scoreboardButtonPressed(cocos2d::Ref* sender)
{
	auto nivel1 = Scene::createWithPhysics();
	nivel1->addChild(Scoreboard::createScene());
	Director::getInstance()->replaceScene(TransitionFade::create(1.5, nivel1));

}



