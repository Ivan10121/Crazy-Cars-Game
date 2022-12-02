#pragma once
#include "cocos2d.h"

class Carritos : public cocos2d::Sprite
{
public:
	static Carritos* createWithFileName();
	void start();
	void stop();
	void SetSpeedAndWidth(const float speed, const float width);
	Carritos() {};

private:
	void ReachDestination();
	float speed;
	float screeenWidth;
	float pixelsPerSec;
	float xOffSet;

};

