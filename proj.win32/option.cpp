#include "option.h"
#include "resource1.h"
#include "SimpleAudioEngine.h"
#include "MainMenu.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene * Option::scene()
{
	CCScene *scene = CCScene::create();
	Option *layer = (Option*)Option::create();
	scene->addChild(layer);
	return scene;
}

bool Option::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	CCSprite *background = CCSprite::create(s_loadingbg);
	background->setAnchorPoint(ccp(0,0));
	this->addChild(background,0,1);

	CCTexture2D *Title = CCTextureCache::sharedTextureCache()->addImage(s_title);
	CCSprite *Optiontitle = CCSprite::createWithTexture(Title,CCRectMake(0,0,134,34));
	this->addChild(Optiontitle);
	Optiontitle->setPosition(ccp(winsize.width/2-20,winsize.height-90));

	CCMenuItemFont *menuTitle = CCMenuItemFont::create("Sound");
	menuTitle->setFontName("Arial");
	menuTitle->setFontSize(19);
	menuTitle->setEnabled(false);

	CCMenuItemFont::setFontName("Arial");
	CCMenuItemFont::setFontSize(26);
	CCMenuItemToggle *toggle = CCMenuItemToggle::createWithTarget(this,menu_selector(Option::SetOption),CCMenuItemFont::create("ON"),CCMenuItemFont::create("OFF"),NULL);
	
	
	CCLabelBMFont *backlb = CCLabelBMFont::create("GO Back",s_font);
	CCMenuItemLabel *goback = CCMenuItemLabel::create(backlb,this,menu_selector(Option::Goback));
	goback->setScale(0.6f);
	CCActionInterval *fadein = CCFadeTo::create(1,100);
	CCActionInterval *fadeout = CCFadeTo::create(1,255);
	CCEaseSineInOut *sinein = CCEaseSineInOut::create(fadein);
	CCEaseSineInOut *sineout = CCEaseSineInOut::create(fadeout);
	CCFiniteTimeAction *sqe = CCSequence::create(sinein,sineout,NULL);
	goback->runAction(CCRepeatForever::create((CCActionInterval*)sqe));

	CCMenu *menu = CCMenu::create(menuTitle,toggle,goback,NULL);
	menu->alignItemsInColumns(2,1);
	this->addChild(menu);

	CCPoint pos =  goback->getPosition();
	pos.y -= 50;
	goback->setPosition(pos);
	return true;                    
}

void Option::SetOption(CCObject *psender)
{

}

void Option::Goback(CCObject *psender)
{
	CCScene *scene = CCScene::create();
	MainMenu *layer = (MainMenu*)MainMenu::create();
	scene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1.2f, scene,false));
}