#include "Effect.h"
#include <string>
#include "resource1.h"

USING_NS_CC;
using namespace cocos2d;

Effect::Effect()
{

}
Effect::~Effect()
{

}
Effect* Effect::create()
{
	Effect *effect = new Effect();
	if (effect)
	{
		effect->autorelease();
		return effect;
	}
	else
	{
		delete effect;
		effect = NULL;
		return NULL;
	}
}

void Effect::shareanmation()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_expolition);
	CCArray *anmation = CCArray::create();
	char str[64] = {0};

	for (int i = 1;i < 35;++i)
	{
		sprintf(str,"explosion_%02d.png",i);
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		anmation->addObject(frame);
	}
	//动画效果的延迟时间
	CCAnimation *anmation1 = CCAnimation::createWithSpriteFrames(anmation,0.04f);
	CCAnimationCache::sharedAnimationCache()->addAnimation(anmation1, "Explosion");
}

void Effect::shareeffect(CCNode *parent,cocos2d::CCCallFunc* callbanck)
{
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	CCSprite *fare = CCSprite::create(s_fare);

	ccBlendFunc abd = {GL_SRC_ALPHA, GL_ONE};
	fare->setBlendFunc(abd);

	parent->addChild(fare);

	fare->setOpacity(0);
	fare->setRotation(-90);
	fare->setPosition(ccp(-30,winsize.height-100));
	fare->setScale(0.2f);

	CCActionInterval *opacityAim = CCFadeTo::create(0.5f,255);
	CCActionInterval *opcityDim = CCFadeTo::create(1,0);

	CCActionInterval *bigerim = CCScaleBy::create(0.5f,1.2f,1.2f);

	CCEaseSineOut *bigEase = CCEaseSineOut::create(bigerim);
	CCActionInterval *moveim = CCMoveBy::create(0.7f,ccp(312,0));
	CCEaseSineOut *moveEase = CCEaseSineOut::create(moveim);

	CCActionInterval *roteim = CCScaleBy::create(2.5,8);

	CCEaseExponentialOut *roteease = CCEaseExponentialOut::create(roteim);
	CCScaleTo *biger = CCScaleTo::create(0.5,1);
	CCCallFuncN *removefouction = CCCallFuncN::create(fare,callfuncN_selector(Effect::killSprite));

	fare->runAction(CCSequence::create(opacityAim,bigEase,opcityDim,removefouction,callbanck,NULL));
	fare->runAction(moveEase);
	fare->runAction(roteease);
	fare->runAction(biger);
}

void Effect::explode(CCNode *parent,cocos2d:: CCPoint pos)
{
	CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("explosion_01.png");
	CCSprite *exption = CCSprite::createWithSpriteFrame(frame);
	parent->addChild(exption);
	exption->setPosition(pos);

	CCCallFuncN *removefunction = CCCallFuncN::create(exption,callfuncN_selector(Effect::killSprite));
	CCAnimation *animation = CCAnimationCache::sharedAnimationCache()->animationByName("Explosion");
	exption->runAction(CCSequence::create(CCAnimate::create(animation),removefunction,NULL));
}

void Effect::killSprite(CCNode *pSender)
{
	pSender->removeFromParentAndCleanup(true);
}