#include "bullet.h"
#include "resource1.h"
USING_NS_CC;
using namespace cocos2d;

cocos2d::CCArray *bullet_play;//存放子弹
cocos2d::CCArray *bullet_enmy;
cocos2d::CCArray *enemy_items;
Bullet::Bullet()
{
	m_HP = 1;
	isactive = true;
	m_velocityx = 0;
	m_velocityy = 200;
	zorder = 3000;
}
Bullet::~Bullet()
{

}
Bullet::Bullet(int speed,const char *bulletstate)
{
	m_HP = 1;
	isactive = true;
	m_velocityx = 0;
	m_velocityy = -speed;
	zorder = 3000;

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_bullet_plist);
	this->initWithSpriteFrameName(bulletstate);
	ccBlendFunc cb = {GL_SRC_ALPHA, GL_ONE};
	this->setBlendFunc(cb);
}
bool Bullet::init()
{
	if (!CCSprite::init())
	{
		return false;
	}

	scheduleUpdate();
	return true;
}

void Bullet::hurt()
{
	m_HP--;
	if (m_HP<0)
	{
		isactive = false;
	}
}

bool Bullet::isAccetive()
{
	return isactive;
}

void Bullet::update(float dt)
{
	CCPoint pos = this->getPosition();
	pos.x -= m_velocityx *dt;
	pos.y -= m_velocityy *dt;
	this->setPosition(pos);
	if (m_HP < 0)
	{
		isactive = false;
	}
}

CCRect Bullet::colideRect()
{
	CCPoint pos = this->getPosition();
	//Size size = this->getContentSize();
	return (CCRectMake(pos.x,pos.y,6,6));
}

void Bullet::removeexplode(CCNode *pSender)
{
	pSender->removeFromParentAndCleanup(true);
}

void Bullet::destory()
{
	//子弹爆炸的效果
	CCSprite *explode = CCSprite::create(s_hit);
	ccBlendFunc cb = {GL_SRC_ALPHA, GL_ONE};
	explode->setBlendFunc(cb);
	explode->setPosition(this->getPosition());
	this->getParent()->addChild(explode,9999);
	explode->setRotation(CCRANDOM_0_1()*360);
	explode->setScale(0.7f);

	bullet_play->removeObject(this);
	bullet_enmy->removeObject(this);
	this->removeFromParentAndCleanup(true);

	CCCallFuncN *removeexplode = CCCallFuncN::create(explode,callfuncN_selector(Bullet::removeexplode)); 
	explode->runAction(CCScaleBy::create(0.2f,2,2));
	explode->runAction(CCSequence::create(CCFadeOut::create(0.2f),removeexplode,NULL));
}
