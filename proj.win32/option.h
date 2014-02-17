#ifndef OPTION_H
#define OPTION_H
#include "cocos2d.h"

class Option:public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene *scene();
	virtual bool init();
	void Goback(CCObject *psender);
	void SetOption(CCObject *psender);
	bool issound;
	CREATE_FUNC(Option);
};
#endif