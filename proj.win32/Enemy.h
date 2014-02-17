#ifndef ENEMY_H
#define ENEMY_H
#include "cocos2d.h"
#include "unSprite.h"

#include "bullet.h"
#include "config.h"

#include <vector>

USING_NS_CC;

enum MoveType
{
	Randmove = 1,//随机移动
	Timemove,  //时间间隔移动
	AtackMove//有攻击性移动
};

class Enemy:public unSprite
{
public:
	Enemy();
	~Enemy();
	virtual void hurt();
	virtual void destory();
	virtual cocos2d::CCRect colideRect();
	virtual bool isAccetive();
	virtual void update(float dt);
	void shoot(float dt);//子弹的生成
	//void moveType(int type);//移动的类型
	static Enemy *create(EnemyType type);
	virtual bool init(EnemyType type );
	void sharedEnemy();
	//void GetMoveType();
	//EnemyType RandEnemy();
	static void Jiazai();
private:
	int m_hp;
	bool islife;//判断飞船的状态
	int lifecount;//计算屏幕上剩余的敌船的数量
	int enemyspeed;//敌船移动速度
	int bulletspeed;//子弹移动速度
	float delytime;//子弹随机出现的时间
	//EnemyType enemytype;
	//Ship *ship;
	//cocos2d::CCLayer *m_gamelayer;
};
#endif



