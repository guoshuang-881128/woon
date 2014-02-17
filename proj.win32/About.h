#ifndef ABOUT_H
#define ABOUT_H
#include "cocos2d.h"
class About:public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene* scene();
	virtual bool init();
	void Goback(CCObject *pSender);
	CREATE_FUNC(About);
};
#endif