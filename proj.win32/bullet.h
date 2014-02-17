#ifndef BULLET_H
#define BULLET_H
#include "unSprite.h"
#include "cocos2d.h"

extern cocos2d::CCArray *bullet_play;//存放子弹
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
	 bool isactive;//判断子弹是否还存在
private:
	int m_HP;//子弹的血量
	int bulletType;//子弹的类型
	float m_velocityx;//有效区域的坐标
	float m_velocityy;
	int zorder;//表示在父节点的深度，大于0在父节点上面，小于0在下面
};
#endif