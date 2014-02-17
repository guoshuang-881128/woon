#include "MainMenu.h"
#include "SimpleAudioEngine.h"
#include "resource1.h"
#include "Effect.h"
#include "option.h"
#include "About.h"
#include "Gamesence.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d;

CCScene * MainMenu::scene()
{
	CCScene *scene = CCScene::create();

	MainMenu *layer = (MainMenu*)MainMenu::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenu::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	winsize = CCDirector::sharedDirector()->getWinSize();

	//background
	CCSprite *loadingbackground = CCSprite::create(s_loadingbg);
	loadingbackground->setAnchorPoint(ccp(0,0));
	this->addChild(loadingbackground,0,1);

	CCSprite *logo = CCSprite::create(s_logo);
	logo->setAnchorPoint(ccp(0.5,1));
	logo->setPosition(ccp(winsize.width/2-10,winsize.height/2+180));
	this->addChild(logo,10,1);

	CCSprite *menuNomal = CCSprite::create(s_menu,CCRectMake(0,0,126,33));
	CCSprite *menuSelected = CCSprite::create(s_menu,CCRectMake(0,33,126,33));
	CCSprite *menuDisable = CCSprite::create(s_menu,CCRectMake(0,66,126,33));

	CCSprite *optionNomal = CCSprite::create(s_menu,CCRectMake(126,0,126,33));
	CCSprite *optionSelect = CCSprite::create(s_menu,CCRectMake(126,33,126,33));
	CCSprite *optionDisable = CCSprite::create(s_menu,CCRectMake(126,66,126,33));

	CCSprite *aboutNomal = CCSprite::create(s_menu,CCRectMake(252,0,126,33));
	CCSprite *aboutSelect = CCSprite::create(s_menu,CCRectMake(252,33,126,33));
	CCSprite *aboutDisable = CCSprite::create(s_menu,CCRectMake(252,66,126,33));

	CCMenuItemSprite *newgame = CCMenuItemSprite::create(menuNomal,menuSelected,menuDisable,this,menu_selector(MainMenu::fareEffect));
	CCMenuItemSprite *option = CCMenuItemSprite::create(optionNomal,optionSelect,optionDisable,this,menu_selector(MainMenu::setOption));
	option->setTag(20);
	CCMenuItemSprite *about = CCMenuItemSprite::create(aboutNomal,aboutSelect,aboutDisable,this,menu_selector(MainMenu::setAbout));
	about->setTag(21);

	CCMenu *menu = CCMenu::create(newgame,option,about,NULL);
	menu->alignItemsVerticallyWithPadding(20);
	menu->setPosition(ccp(winsize.width/2,winsize.height/2-100));
	this->addChild(menu,1,2);
	//one
	m_ships = CCSprite::create(s_ship,CCRectMake(0, 45, 60, 38));
	CCPoint postion = ccp(CCRANDOM_0_1()*winsize.width,0);
	m_ships->setPosition(postion);
	this->addChild(m_ships,0,4);
	m_ships->runAction(CCMoveBy::create(3,ccp(CCRANDOM_0_1()*winsize.width,postion.y+winsize.height+100)));
	//two
	/*CCTexture2D *textCache = CCTextureCache::sharedTextureCache()->addImage(s_ship);
	CCSprite *m_ship = CCSprite::createWithTexture(textCache,CCRectMake(0, 45, 60, 38));
	CCPoint postion1 = ccp(CCRANDOM_0_1()*winsize.width,0);
	m_ship->setPosition(postion1);
	this->addChild(m_ship,0,4);
	m_ship->runAction(CCMoveBy::create(3,ccp(CCRANDOM_0_1()*winsize.width,postion1.y+winsize.height+100)));*/

	this->schedule(schedule_selector(MainMenu::update),0.1f);
	return true;
}

void MainMenu::update(float dt)
{
	if (m_ships->getPositionY() > winsize.height)
	{
		CCPoint pos = ccp(CCRANDOM_0_1()*winsize.width,0);
		m_ships->setPosition(pos);
		m_ships->runAction(CCMoveBy::create(floor(CCRANDOM_0_1()*5),ccp(CCRANDOM_0_1()*winsize.width,pos.y+winsize.height+100)));
	}
}

void MainMenu::fareEffect(CCObject* pSender)
{
	Effect *effect = Effect::create();
	CCCallFunc *callback = CCCallFunc::create(this,callfunc_selector(MainMenu::newGame));
	effect->shareeffect(this,callback);

}

void MainMenu::newGame()
{
	CCScene *scene = CCScene::create();
	scene->addChild(GameScene::create());
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2f, scene));
}

void MainMenu::setOption(CCObject* pSender)
{
	CCScene *scene = CCScene::create();
	scene->addChild(Option::create());
	CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1.2f,scene,true));
}

void MainMenu::setAbout(CCObject *pSender)
{
	CCScene *scene = CCScene::create();
	scene->addChild(About::create());
	CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInL::create(1.5f,scene));
}