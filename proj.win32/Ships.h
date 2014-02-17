#ifndef SHIP_H
#define SHIP_H

#include "cocos2d.h"
#include "unSprite.h"


class Ship:public unSprite
{
public:
	Ship();
	~Ship();
	virtual bool init();
   virtual  void destory();
   virtual  void hurt();
   virtual cocos2d:: CCRect colideRect();
   virtual bool isAccetive();
   virtual void update(float dt);
   void shoot(float dt);
   void makeattack(CCNode *psender);
 //  Ship* getship();
   CREATE_FUNC(Ship);
public:
	//CCSprite *m_ship;
	int m_HP;//�ɴ���Ѫ��
	bool islife;//�ɴ���״̬
	cocos2d::CCPoint shipPos;//�ɴ���λ��
	cocos2d::CCSize winsize;
	bool canAttack;//�ɴ��Ƿ񱻹���
	int m_bulletspeed;

};
#endif
