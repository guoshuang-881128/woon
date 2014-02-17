#ifndef MAIN_MEUN_H
#define MAIN_MENU_H

#include "cocos2d.h"
//USING_NS_CC;

class MainMenu:public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene *scene();
	CREATE_FUNC(MainMenu);
	virtual void update(float dt);
	void buttonEffect();
	void fareEffect(CCObject* pSender);
	void newGame();
	void setOption(CCObject* pSender);
	void setAbout(CCObject *pSender);
private:
	cocos2d::CCSize winsize;
	cocos2d::CCSprite *m_ships;
	
};

#endif