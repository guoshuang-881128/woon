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
	Randmove = 1,//����ƶ�
	Timemove,  //ʱ�����ƶ�
	AtackMove//�й������ƶ�
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
	void shoot(float dt);//�ӵ�������
	//void moveType(int type);//�ƶ�������
	static Enemy *create(EnemyType type);
	virtual bool init(EnemyType type );
	void sharedEnemy();
	//void GetMoveType();
	//EnemyType RandEnemy();
	static void Jiazai();
private:
	int m_hp;
	bool islife;//�жϷɴ���״̬
	int lifecount;//������Ļ��ʣ��ĵд�������
	int enemyspeed;//�д��ƶ��ٶ�
	int bulletspeed;//�ӵ��ƶ��ٶ�
	float delytime;//�ӵ�������ֵ�ʱ��
	//EnemyType enemytype;
	//Ship *ship;
	//cocos2d::CCLayer *m_gamelayer;
};
#endif



