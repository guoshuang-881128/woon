#include "Enemy.h"
#include "resource1.h"
#include "bullet.h"
//#include "Ships.h"
//#include "Gamesence.h"
#include "Effect.h"
#include "config.h"

USING_NS_CC;
using namespace cocos2d;

//在这里初始化了栈里面的所有东西
Enemy::Enemy()
{
	islife = true;
	bulletspeed = -200;
	enemyspeed = 200;
	delytime = 1+1.2*CCRANDOM_0_1();
		 
}
Enemy::~Enemy()
{

}

Enemy *Enemy::create(EnemyType type)
{
	Enemy *enmpty = new Enemy();
	if (enmpty && enmpty->init(type))
	{
		enmpty->autorelease();
		return enmpty;
	}
	else
	{
		delete enmpty;
		enmpty = NULL;
		return NULL;
	}
}

bool Enemy::init(EnemyType type )
{
	if (!CCSprite::init())
	{
		return false;
	}
	m_hp = type.m_hp;
	//ship = new Ship();
	//Ship = (Ship*)Ship::create();
	//绘制子弹的出现
	

	this->schedule(schedule_selector(Enemy::shoot),delytime);
	this->initWithSpriteFrameName(type.enemtypename.c_str());
	return true;
}

void Enemy::update(float dt)
{
	if (m_hp <= 0)
	{
		islife = false;
	}
}

bool Enemy::isAccetive()
{
	return islife;
}

void Enemy::hurt()
{
	m_hp--;
}

void Enemy::destory()
{
	Effect *effect = Effect::create();
	effect->explode(this->getParent(),this->getPosition());
	enemy_items->removeObject(this);
	this->removeFromParentAndCleanup(true);
}

CCRect Enemy::colideRect()
{
	CCPoint pos = this->getPosition();
	CCSize size = this->getContentSize();
	return (CCRectMake(pos.x - size.width/2,pos.y - size.height/4,size.width,size.height/2));
}

//void Enemy::moveType(int type)
//{
//	int a = type;
//	CCAction *tempAction;
//	CCSize size = CCDirector::sharedDirector()->getWinSize();
//	switch(a)
//	{
//	case Randmove:
//		tempAction = CCMoveTo::create(3,ccp(0,CCRANDOM_0_1()*size.height));
//		break;
//	case Timemove:
//		ship->getPosition();
//		
//		break;
//	case AtackMove:
//		break;
//	}
//	this->runAction(tempAction);
//}
void Enemy::shoot(float dt)
{
	CCPoint pos = this->getPosition();
	Bullet *bulletey = new Bullet(bulletspeed,"W2.png");
	bullet_enmy->addObject(bulletey);
	this->getParent()->addChild(bulletey,3000,98);
	bulletey->setPosition(ccp(pos.x,pos.y - this->getContentSize().height*0.2));
	bulletey->autorelease();
}


void Enemy::sharedEnemy()
{
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_enemy, s_enemyp);
}

//EnemyType Enemy::RandEnemy()
//{
//	int num = CCRANDOM_0_1()*5;
//	EnemyType enmytemp;
//	enmytemp = enemys.at(num);
//	return enmytemp;
//	
//}

void Enemy::Jiazai()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_enemy, s_enemyp);
}