#ifndef BULLET_H
#define BULLET_H
#include "unSprite.h"
#include "cocos2d.h"

extern cocos2d::CCArray *bullet_play;//����ӵ�
extern cocos2d::CCArray *bullet_enmy;
extern cocos2d::CCArray *enemy_items;
enum bulletstate
{
	bulebullet = 1,
	greenbullet,
};
class Bullet:public unSprite
{
public:
	virtual void hurt();
	virtual void destory();
	virtual cocos2d::CCRect colideRect();
	virtual bool isAccetive();
	virtual bool init();
	virtual void update(float dt);
	void removeexplode(CCNode *pSender);

public:
	Bullet();
	 Bullet(int speed,const char *bulletstate);
	 ~Bullet();
	 bool isactive;//�ж��ӵ��Ƿ񻹴���
private:
	int m_HP;//�ӵ���Ѫ��
	int bulletType;//�ӵ�������
	float m_velocityx;//��Ч���������
	float m_velocityy;
	int zorder;//��ʾ�ڸ��ڵ����ȣ�����0�ڸ��ڵ����棬С��0������
};
#endif