#include "Victory.h"
#include "Nivel1.h"
#include "GameMenu.h"
#include "AppDelegate.h"
#include "audio/include/AudioEngine.h"
USING_NS_CC;


cocos2d::Scene* Victory::createScene()
{
	Scene* scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vect(0, 0));
	auto* layer = Victory::create();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->addChild(layer);
	return scene;
}

void Victory::update(float deltaTime)
{

}



bool Victory::init()
{
	AudioEngine::stop(musica);

	AudioEngine::play2d("MusicaVictoria.mp3");

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	const auto winSize =
		cocos2d::Director::getInstance()->getWinSize();

	auto fondoMenu = Sprite::create("MenuB.jpg");
	fondoMenu->setAnchorPoint(Vec2::ZERO);
	this->addChild(fondoMenu, 0);

	//Titulo
	auto label = Label::createWithTTF("VICTORY", "fonts/Marker Felt.ttf", 80);
	label->setPosition(Vec2(400,700));
	label->enableOutline(Color4B::RED, 5);
	label->enableShadow();
	label->setColor(Color3B::YELLOW);
	auto animation = Sequence::create(ScaleBy::create(.2, 1.1), ScaleBy::create(.2, .909), NULL);
	auto action = RepeatForever::create(animation);
	label->runAction(action);
	this->addChild(label);

	
	

	





	//Botones para Menu
	auto menuNormal = Sprite::create("Menu.png");
	auto menuSelected = Sprite::create("MenuSelected.png");
	auto menuDisable = Sprite::create("Menu.png");

	//Botones para ScoreBoard
	auto playAgainNormal = Sprite::create("PlayAgain.png");
	auto playAgainSelected = Sprite::create("PlayAgainSelected.png");
	auto playAgainDisable = Sprite::create("PlayAgain.png");



	//Menu item para boton play
	auto menuButton = MenuItemSprite::create(
		menuNormal, menuSelected, menuDisable,
		CC_CALLBACK_1(Victory::menuButtonPressed, this));

	auto playAgain = MenuItemSprite::create(
		playAgainNormal, playAgainSelected, playAgainDisable,
		CC_CALLBACK_1(Victory::playAgainButtonPressed, this));




	//auto menu = Menu::create(play,scoreboard,nullptr);
	auto menu = Menu::create(menuButton, playAgain, NULL);
	menu->alignItemsVerticallyWithPadding(20);


	menu->setContentSize(Size(0, 0));
	float x = origin.x + visibleSize.width / 2;
	float y = origin.y + visibleSize.height / 2 -30;
	menu->setPosition(Vec2(x, y));


	menu->setScale(.9);




	this->addChild(menu, 1);



	return true;
}


void Victory::menuButtonPressed(cocos2d::Ref* sender)
{
	AudioEngine::stopAll();
	AudioEngine::play2d("MusicaMenu.mp3");
	auto scene = GameMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.5, scene));
}


void Victory::playAgainButtonPressed(cocos2d::Ref* sender)
{
	AudioEngine::stop(musica);
	auto nivel1 = Scene::createWithPhysics();
	//nivel1->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); 
	nivel1->addChild(Nivel1::createScene());
	Director::getInstance()->replaceScene(TransitionFade::create(1.5, nivel1));
}






