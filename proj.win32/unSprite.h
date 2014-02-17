#ifndef UNSPRITE_H
#define UNSPRITE_H
#include "cocos2d.h"

class unSprite:public cocos2d::CCSprite
{
public:
	unSprite();
	~unSprite();
	virtual void destory()=0;
	virtual void hurt()=0;
	virtual cocos2d::CCRect colideRect()=0;
	virtual bool isAccetive()=0;
};
#endif