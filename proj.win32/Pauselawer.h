#ifndef PAUSELAWER_H
#define PAUSELAWER_H
#include "cocos2d.h"
using namespace cocos2d;

class Pause1:public cocos2d::CCLayerColor
{
public:
	virtual bool init();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	virtual void  registerWithTouchDispatcher();
	CREATE_FUNC(Pause1);
};
#endif