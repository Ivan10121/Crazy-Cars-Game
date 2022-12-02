#include "GameOver.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;

cocos2d::Scene* GameOver::createScene()
{

	Scene* scene = Scene::create();
	auto* layer = GameOver::create();
	scene->addChild(layer);
	return scene;
}

void GameOver::update(float deltaTime)
{

}

bool GameOver::init()
{
	//int musica = AudioEngine::play2d("MusicaNiveles.mp3", true);

	//Variables de tamaño
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	const auto winSize =
		cocos2d::Director::getInstance()->getWinSize();



	//Agregar titulo
	auto label = Label::createWithTTF("GameOver", "fonts/Marker Felt.ttf", 50);

	label->setPosition(Vec2(origin.x, visibleSize.height - label->getContentSize().height - 50));
	label->enableOutline(Color4B::RED, 5);
	label->enableShadow();
	label->setColor(Color3B::YELLOW);
	this->addChild(label, 0);

	auto moveBy = MoveBy::create(2.5, Vec2(1000, 0));
	label->runAction(moveBy);

	return true;
}







