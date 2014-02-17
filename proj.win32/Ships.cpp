#include "Ships.h"
#include "cocos2d.h"
#include "resource1.h"
#include "Effect.h"
#include "bullet.h"

USING_NS_CC;
using namespace cocos2d;

Ship::Ship()
{
	m_HP = 5;
	islife = true;
	m_bulletspeed = 250;

}
Ship::~Ship()
{
	
}

//Ship* Ship::getship()
//{
//	Ship *ship = new Ship();
//	if (!ship)
//	{
//		delete ship;
//		return NULL;
//	}
//	return ship;
//}

bool Ship::init()
{
	if (!CCSprite::init())
	{
		return false;
	}
	winsize = CCDirector::sharedDirector()->getWinSize();
	shipPos.x = winsize.width/3;
	shipPos.y = winsize.height/10;

	CCTexture2D *textture = CCTextureCache::sharedTextureCache()->addImage(s_ship);
	CCRect rec = CCRectMake(0, 0, 60, 38);
	this->initWithTexture(textture,rec);
	this->setPosition(shipPos);

	CCSpriteFrame *fame1 = CCSpriteFrame::createWithTexture(textture,CCRectMake(0,0,60,38));
	CCSpriteFrame *fame2 = CCSpriteFrame::createWithTexture(textture,CCRectMake(60,0,60,38));

	CCArray *anfame = CCArray::create();
	anfame->addObject(fame1);
	anfame->addObject(fame2);
    
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(anfame,0.1f);
	CCAnimate *animate = CCAnimate::create(animation);
	this->runAction(CCRepeatForever::create(animate));


	//绘制子弹
	this->schedule(schedule_selector(Ship::shoot),0.16f);

	this->canAttack = false;
	CCSprite *gostsprite = CCSprite::createWithTexture(textture,CCRectMake(0,45,60,38));
	ccBlendFunc cb = {GL_SRC_ALPHA,GL_NONE};
	gostsprite->setBlendFunc(cb);
	
	gostsprite->setScale(6);
	gostsprite->setPosition(ccp(this->getContentSize().width/2,12));
	//gostsprite->setPosition(shipPos);
	this->addChild(gostsprite,3000,9999);
	gostsprite->runAction(CCScaleTo::create(0.5,1,1));

	

	CCBlink *blink = CCBlink::create(3,9);

	CCCallFuncN *make = CCCallFuncN::create(this,callfuncN_selector(Ship::makeattack));
	this->runAction(CCSequence::create(CCDelayTime::create(0.5),make,NULL));
	this->runAction(blink);
	return true;
	
}
CCRect Ship::colideRect()
{
	CCPoint pos = this->getPosition();
	CCSize size = this->getContentSize();
	return (CCRectMake(pos.x-size.width/2,pos.y-size.height/2,size.width/2,winsize.height/2));
}

void Ship::hurt()
{
	if (canAttack)
	{
		m_HP--;
		this->setColor(ccc3(255,0,0));
	}
	
}

void Ship::destory()
{
	Effect *effect = Effect::create();
	effect->explode(this->getParent(),this->getPosition());
	this->removeFromParentAndCleanup(true);
}

bool Ship::isAccetive()
{
	return islife;
}
void Ship::update(float dt)
{
	if (m_HP < 0)
	{
		islife = false;
	}
}

void Ship::makeattack(CCNode *psender)
{
	canAttack = true;
	this->setVisible(true);
	psender->removeChildByTag(9999,true);
}

void Ship::shoot(float dt)
{
	//绘制左右的子弹
	int offset = 15;
	CCPoint pos = this->getPosition();
	CCSize size = this->getContentSize();
	Bullet *bullet_left = new Bullet(m_bulletspeed,"W1.png");
	if (bullet_left)
	{
		bullet_left->autorelease();
		bullet_play->addObject(bullet_left);
		this->getParent()->addChild(bullet_left,3000,99);
		bullet_left->setPosition(ccp(pos.x-offset,pos.y+size.height/2));
	}
	else
	{
		delete bullet_left;
		bullet_left = NULL;
	}

	Bullet *bullet_right = new Bullet(m_bulletspeed,"W1.png");
	if (bullet_right)
	{
		bullet_right->autorelease();
		bullet_play->addObject(bullet_right);
		this->getParent()->addChild(bullet_right,3000,99);
		bullet_right->setPosition(ccp(pos.x + offset,pos.y +size.height/2));
	}
	else
	{
		delete bullet_right;
		bullet_right = NULL;
	}

}