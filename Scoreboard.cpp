#include "Scoreboard.h"
#include "GameMenu.h"
#include "AppDelegate.h"
#include <fstream>


USING_NS_CC;


cocos2d::Scene* Scoreboard::createScene()
{

	Scene* scene = Scene::create();
	auto* layer = Scoreboard::create();
	scene->addChild(layer);
	return scene;
}

void Scoreboard::update(float deltaTime)
{

}

bool Scoreboard::archivo_existe(std::string nombre)
{
	std::ifstream archivo(nombre.c_str());
	return archivo.good();
}

bool Scoreboard::init()
{
	
	//Variables de tamaño
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	const auto winSize =
		cocos2d::Director::getInstance()->getWinSize();

	//Fondo
	auto fondoMenu = Sprite::create("MenuB.jpg");
	fondoMenu->setAnchorPoint(Vec2::ZERO);
	this->addChild(fondoMenu, 0);


	//Agregar titulo
	auto label = Label::createWithTTF("Scoreboard", "fonts/Marker Felt.ttf", 80);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 350));
	label->enableOutline(Color4B::RED, 5);
	label->enableShadow();
	label->setColor(Color3B::YELLOW);
	auto animation = Sequence::create(ScaleBy::create(.4, 1.1), ScaleBy::create(.4, .909), NULL);
	label->runAction(RepeatForever::create(animation));
	this->addChild(label, 0);


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

	std::string cad1 = "The best score:          ";
	std::string cad2 = "Your score:          ";

	std::string bestscore = std::to_string(finalScore);
	std::string lastScore = std::to_string(score);


	

	
	
	//Labels de score
	auto theBest = Label::createWithTTF(cad1, "fonts/Marker Felt.ttf", 50);
	theBest->setColor(Color3B::BLACK);
	theBest->setAnchorPoint(Vec2(0, 0));
	theBest->setPosition(Vec2(50, 600));
	this->addChild(theBest, 0);

	auto yourscore = Label::createWithTTF(cad2, "fonts/Marker Felt.ttf", 50);
	yourscore->setColor(Color3B::BLACK);
	yourscore->setAnchorPoint(Vec2(0, 0));
	yourscore->setPosition(Vec2(50, 400));
	this->addChild(yourscore, 0);

	auto labelbestscore = Label::createWithTTF(bestscore, "fonts/Marker Felt.ttf", 50);
	labelbestscore->setColor(Color3B::BLACK);
	labelbestscore->setAnchorPoint(Vec2(.5, 0));
	labelbestscore->setPosition(Vec2(600, 600));
	this->addChild(labelbestscore, 0);

	auto labellastscore = Label::createWithTTF(lastScore, "fonts/Marker Felt.ttf", 50);
	labellastscore->setColor(Color3B::BLACK);
	labellastscore->setAnchorPoint(Vec2(.5, 0));
	labellastscore->setPosition(Vec2(600, 400));
	this->addChild(labellastscore, 0);


	//Carrito fondo
	auto carro1 = Sprite::create("Police.png");
	auto carro2 = Sprite::create("Audi.png");

	carro1->setPosition(Vec2(100, 200));
	carro2->setPosition(Vec2(700, 200));

	carro1->setScale(2);
	carro2->setScale(2);

	this->addChild(carro1);
	this->addChild(carro2);







	//Botones para ir al menu
	auto menuNormal = Sprite::create("Menu.png");
	auto menuSelected = Sprite::create("MenuSelected.png");
	auto menuDisable = Sprite::create("Menu.png");

	//Menu item para boton play
	auto menuButton = MenuItemSprite::create(
		menuNormal, menuSelected, menuDisable,
		CC_CALLBACK_1(Scoreboard::menuButtonPressed, this)
	);


	auto menu = Menu::create(menuButton, nullptr);

	menu->setContentSize(Size(0, 0));
	menu->setPosition(Vec2(visibleSize.width / 2, 150));
	menu->setScale(.7);
	this->addChild(menu, 1);

	return true;
}

void Scoreboard::menuButtonPressed(cocos2d::Ref* pSender)
{
	auto menu = Scene::createWithPhysics();
	//nivel1->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	menu->addChild(GameMenu::createScene());
	Director::getInstance()->replaceScene(TransitionFade::create(1.5, menu));
}




