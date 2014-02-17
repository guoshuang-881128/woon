#include "About.h"
#include "resource1.h"
#include "SimpleAudioEngine.h"
#include "MainMenu.h"

USING_NS_CC;
using namespace cocos2d;
using namespace CocosDenshion;

CCScene* About::scene()
{
	CCScene* scene = CCScene::create();
	scene->addChild(About::create());
	return scene;
}

bool About::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCSprite *background = CCSprite::create(s_loadingbg);
	background->setAnchorPoint(ccp(0,0));
	this->addChild(background);

	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	CCSprite *about = CCSprite::create(s_title,CCRectMake(0,36,134,34));
	this->addChild(about);
	about->setPosition(ccp(winsize.width/2-10,winsize.height-90));

	CCLabelTTF *aboutl = CCLabelTTF::create("   I recode this game according to the logic of MoonWarriors-html5,almost all of the code  keep unanimous with the original. \n     This showcase utilizes many features from Cocos2d-x engine, including: Parallax background, tilemap, actions, ease, frame animation, schedule, Labels, keyboard Dispatcher, Scene Transition", "Arial", 18, CCSizeMake(winsize.width * 0.85, 320), kCCTextAlignmentLeft);
	aboutl->setPosition(ccp(winsize.width/2-5,winsize.height-290));
	this->addChild(aboutl);

	CCLabelBMFont *abl = CCLabelBMFont::create("Go Back",s_font);
	CCMenuItemLabel *goback = CCMenuItemLabel::create(abl,this,menu_selector(About::Goback));
	goback->setScale(0.7f);

	CCActionInterval *fadein = CCFadeTo::create(1.2f,90);
	CCActionInterval *fadeout = CCFadeTo::create(1.2f,255);
	CCEaseSineInOut *fadeease = CCEaseSineInOut::create(fadein);
	CCEaseSineInOut *fadeease1 = CCEaseSineInOut::create(fadeout);
	CCFiniteTimeAction *sqe = CCSequence::create(fadeease,fadeease1,NULL);

	goback->runAction(CCRepeatForever::create((CCActionInterval*)sqe));
	CCMenu *menu = CCMenu::create(goback,NULL);
	menu->setPosition(ccp(winsize.width/2,60));
	this->addChild(menu);
	return true;
}


void About::Goback(CCObject *pSender)
{
   CCScene *scene = CCScene::create();
   scene->addChild(MainMenu::create());
   CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInR::create(1.5f,scene));
}