#ifndef EFFECT_H
#define EFFECT_H
#include "cocos2d.h"
class Effect:public cocos2d::CCNode
{
private:
	cocos2d::CCSprite * sprie;
public:
	Effect();
	~Effect();

	static Effect* create();
	static void shareanmation();//���붯������

	void shareeffect(CCNode *parent,cocos2d::CCCallFunc* callbanck);
	void explode(CCNode *parent,cocos2d:: CCPoint pos);//����Ч����ʾ
	void spark(cocos2d::CCPoint pos, CCNode *parent, float scale, float duration);
	void killSprite(CCNode *pSender);
};
#endif