#include "Pauselawer.h"
#include "resource1.h"

USING_NS_CC;
using namespace cocos2d;
CCMenu *menu;
extern bool isPaused;
bool Pause1::init()
{
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 100)))
	{
		return false;
	}
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();

	CCMenuItemImage *play = CCMenuItemImage::create(s_play,s_play);
	play->setAnchorPoint(ccp(1,0));
	play->setTag(30);
	play->setPosition(ccp(winsize.width-10,winsize.height/10-40));

	menu= CCMenu::create(play,NULL);
	menu->setAnchorPoint(ccp(0,0));
	menu->setPosition(CCPointZero);
	this->addChild(menu,1,200);
	this->setTouchEnabled(true);
	return true;
}

void Pause1::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-99999,true);
	CCLayer::registerWithTouchDispatcher();
}
//根据原来的这个触摸可以被屏蔽，所以恢复函数写在这里，就不在写函数
bool Pause1::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCRect rect = menu->getChildByTag(30)->boundingBox();
	if (rect.containsPoint(pTouch->getLocation()))
	{
		CCDirector::sharedDirector()->resume();
		removeFromParentAndCleanup(true);
		isPaused = true;
	}
	return true;
}

void Pause1::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void Pause1::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}