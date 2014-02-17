#include "Gamesence.h"
#include "resource1.h"
#include "SimpleAudioEngine.h"
#include "bullet.h"
//#include "Enemy.h"
#include "Effect.h"
//#include "config.h"
#include "unSprite.h"
#include "Pauselawer.h"
USING_NS_CC;
using namespace cocos2d;
bool isPaused = false;
using namespace CocosDenshion;
CCMenuItemImage *m_pauseOrplay;
CCScene* GameScene::scene()
{
	CCScene*scene = CCScene::create();
	scene->addChild(GameScene::create());
	return scene;
}

GameScene::GameScene()
{
	m_time = 0;
}

GameScene::~GameScene()
{
	bullet_enmy->release();
	bullet_play->release();
	enemy_items->release();
}

bool GameScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	this->setTouchEnabled(true);
	bullet_enmy = CCArray::create();
	bullet_enmy->retain();
	bullet_play = CCArray::create();
	bullet_play->retain();
	enemy_items = CCArray::create();
	enemy_items->retain();

	Effect::shareanmation();//Ԥ���ض�������

	winsize = CCDirector::sharedDirector()->getWinSize();
	initBackground();

	/*Enemy::sharedEnemy();
	Effect::explode();*/

	//�����ɴ�
	m_ship = Ship::create();
	this->addChild(m_ship,3000,0x81);
	shipsize = m_ship->getContentSize();
	Enemy::Jiazai();
	m_screenRec = CCRectMake(0, 0,  winsize.width, winsize.height + 10);
	//�����д�
	
	createEnemy();

	//����
	m_score = CCLabelBMFont::create("Score:0",s_arial);
	m_score->setAnchorPoint(ccp(1,0));
	this->addChild(m_score,101);
	m_score->setAlignment(kCCTextAlignmentRight);
	m_score->setScale(1.5f);
	m_score->setPosition(ccp(winsize.width-30,winsize.height-30));
	//schedule(schedule_selector(GameScene::update),3);
	//�����ɴ���������ͼ��
	CCSprite * m_shipcount = CCSprite::create(s_ship,CCRectMake(0, 0, 60, 38));
	m_shipcount->setScale(1);
	m_shipcount->setPosition(ccp(winsize.width/8,winsize.height-30));
	this->addChild(m_shipcount,1,10);

	//lift count
	char liftcount[3];
	sprintf(liftcount,"%d",Config::shareconfig()->GetConfig());
	m_lifeCount = CCLabelTTF::create(liftcount,"Arial",28);
	m_lifeCount->setAnchorPoint(ccp(1,0));
	m_lifeCount->setPosition(ccp(winsize.width/8+50,winsize.height-50));
	m_lifeCount->setColor(ccc3(255,205,205));
	this->addChild(m_lifeCount);

	//��ͣ�����а�ť
	
	m_pauseOrplay = CCMenuItemImage::create(s_pause,s_pause,this,menu_selector(GameScene::doPause));
	m_pauseOrplay->setAnchorPoint(ccp(1,0));
	m_pauseOrplay->setVisible(true);
	m_pauseOrplay->setPosition(ccp(winsize.width-10,winsize.height/10-40));
	//this->addChild(m_pauseOrplay);
	CCMenu *menupause = CCMenu::create(m_pauseOrplay,NULL);
	menupause->setAnchorPoint(ccp(0,0));
	menupause->setPosition(CCPointZero);
	this->addChild(menupause,1,200);
	
	schedule(schedule_selector(GameScene::ScoreCount),1);
	scheduleUpdate();
	return true;
}

void GameScene::update(float dt)
{
	checkIsCollide();
	removeUpdate(dt);
	checkIsborn();
	
}

void GameScene::initBackground()
{
	m_skyback = CCSprite::create(s_background);
	m_skyback->setAnchorPoint(ccp(0,0));
	m_skybackHeight = m_skyback->getContentSize().height;
	this->addChild(m_skyback,-10);

	//tile map
	m_tileMap = CCTMXTiledMap::create(s_leve01);
	this->addChild(m_tileMap,-9);
	m_tileMapHeight = m_tileMap->getMapSize().height * m_tileMap->getTileSize().height;

	m_skybackHeight -= 48;
	m_tileMapHeight -=200;
	isloadSky = false;
	isloadtileMap = false;

	m_skyback->runAction(CCMoveBy::create(4,ccp(0,-48)));
	m_tileMap->runAction(CCMoveBy::create(4,ccp(0,-200)));

	schedule(schedule_selector(GameScene::moveBackground),4);

}

////Ship* GameScene::getship()
//{
//	return m_ship;
//}
void GameScene::moveBackground(float dt)
{
	m_skyback->runAction(CCMoveBy::create(4,ccp(0,-48)));
	m_tileMap->runAction(CCMoveBy::create(4,ccp(0,-200)));

	m_skybackHeight -=48;
	m_tileMapHeight -=200;

	if (m_skybackHeight <= winsize.height )
	{
		if (!isloadSky)
		{
			m_skybackRe = CCSprite::create(s_background);
			m_skybackRe->setAnchorPoint(ccp(0,0));
			this->addChild(m_skybackRe,-10);
			m_skybackRe->setPosition(ccp(0,winsize.height/*-(winsize.height-m_skybackHeight)*/));
			isloadSky = true;
		}
		m_skybackRe->runAction(CCMoveBy::create(4,ccp(0,-48)));
	}

	if (m_skybackHeight <= 0)
	{
		m_skybackHeight = m_skyback->getContentSize().height;
		this->removeChild(m_skyback,true);
		m_skyback = m_skybackRe;
		m_skybackRe = NULL;
		isloadSky = false;
	}


	if (m_tileMapHeight <= winsize.height)
	{
		if (!isloadtileMap)
		{
			m_tileMapRe = CCTMXTiledMap::create(s_leve01);
			this->addChild(m_tileMapRe,-9);
			m_tileMapRe->setPosition(ccp(0,winsize.height));
			isloadtileMap = true;
		}
		m_tileMapRe->runAction(CCMoveBy::create(4,ccp(0,-200)));
	}

	if (m_tileMapHeight <= 0)
	{
		m_tileMapHeight = m_tileMap->getMapSize().height * m_tileMap->getTileSize().height;
		this->removeChild(m_tileMap,true);
		m_tileMap = m_tileMapRe;
		m_tileMapRe = NULL;
		isloadtileMap = false;
	}
	
}

void GameScene::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
	CCLayer::onEnter();
}

void GameScene::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

bool GameScene::ccTouchBegan(CCTouch *cTouch, CCEvent *cEvent)
{
	return true;
}

void GameScene::ccTouchMoved(CCTouch *cTouch, CCEvent *cEvent)
{
	CCPoint mousePos = cTouch->getLocationInView();
	mousePos = CCDirector::sharedDirector()->convertToGL(mousePos);
	mousePos = convertToNodeSpace(mousePos);
	mousePos = ccpClamp(mousePos,CCPointZero,ccp(winsize.width,winsize.height));
	m_ship->setPosition(mousePos);
}

void GameScene::ccTouchEnded(CCTouch *cTouch, CCEvent *cEvent)
{
	/*CCPoint mousePos = cTouch->getLocationInView();
	Effect *effect = Effect::create();
	effect->explode(this,mousePos);*/
}

void GameScene::createEnemy()
{
	enemtype = Config::shareconfig()->getenemytype();
	//��ʼ���д�
	for (int i = 0;i < 2;i++)
	{
		int num =(int)( CCRANDOM_0_1()*6 );//���ַɴ����������һ��
		EnemyType enempty = enemtype[num];
		m_eneny = Enemy::create(enempty);
		enemy_items->addObject(m_eneny);
		this->addChild(m_eneny,3000,101);
		m_eneny->setPosition(ccp(winsize.width-m_eneny->getContentSize().width,winsize.height-m_eneny->getContentSize().height));
		moveenemy(enempty.movetype);
	}
		
}

void GameScene::moveenemy(int type)
{
	CCPoint shippos; 
	CCAction *EnemyAction;
	switch(type)
	{
	case 0://���ŷɴ��ƶ������
		if (m_ship)
		{
			shippos = m_ship->getPosition();
		}
		else
		{
			shippos = ccp(winsize.width /2,0);
		}
		EnemyAction = CCMoveTo::create(3,shippos);
		break;
	case 1://���������ƶ�
		shippos = ccp(0,winsize.height - m_eneny->getContentSize().height);
		EnemyAction = CCMoveTo::create(3,shippos);
		
		break;
	case 2://����ƶ�
		shippos = ccp(CCRANDOM_0_1()*(winsize.width-m_eneny->getContentSize().width),CCRANDOM_0_1()*(winsize.height-m_eneny->getContentSize().height));
		EnemyAction = CCMoveTo::create(3,shippos);
		break;
	}
	m_eneny->runAction(EnemyAction);
}

//���º��������������Ҫ������ÿ���ڵ��״̬
void GameScene::removeUpdate(float dt)
{
	CCArray *children = this->getChildren();
	for (int i = 0; i < children->count();i++)
	{
		CCSprite *chil = dynamic_cast<CCSprite*>(children->objectAtIndex(i));
		if (chil)
		{
			chil->update(dt);
			int tag = chil->getTag();
			if (tag == 99 || tag == 98 ||tag == 101 || tag == 0x81)
			{
				if (!((unSprite*)chil)->isAccetive())
				{
					((unSprite*)chil)->destory();
					if( tag == 0x81 )
					{
						m_ship = Ship::create();
						this->addChild(m_ship,3000,0x81);
					}
				}
			}
		}
	}

}
//��������ĺô���ͨ�������ָ��ָ����Ӧ�����࣬����д���븴���Ը���
bool GameScene::collide(unSprite *a, unSprite *b)
{
	if( !a || !b)
	{
		return false;
	}

	CCRect aRect = a->colideRect();
	CCRect bRect = b->colideRect();
	if (aRect.intersectsRect(bRect))//�ж������ص��Ļ�����TRUE
	{
		return true;
	}
	return false;
}

void GameScene::checkIsCollide()
{
	CCObject *units;
	CCObject *bullets;
	CCObject *enemybs;
	CCARRAY_FOREACH(enemy_items, units)
	{
		unSprite *enemy = dynamic_cast<unSprite*>(units);
		CCARRAY_FOREACH(bullet_play, bullets)
		{
			unSprite *bullet = dynamic_cast<unSprite*>(bullets);
			if (this->collide(enemy, bullet)) {
				enemy->hurt();
				bullet->hurt();
			}
			/*if (!(m_screenRec.intersectsRect(bullet->boundingBox()))) {
				bullet->destory();
			}*/
		}
		if (collide(enemy, m_ship)) {
			if (m_ship->isAccetive()) {
				enemy->hurt();
				m_ship->hurt();
			}

		}
		/*if (!(m_screenRec.intersectsRect(enemy->boundingBox()))) 
			enemy->destory();*/
		
	}

	CCARRAY_FOREACH(bullet_enmy, enemybs)
	{
		unSprite *enemyb = dynamic_cast<unSprite*>(enemybs);
		if (enemyb) {
			if (collide(enemyb, m_ship)) {
				if (m_ship->isAccetive()) {
					enemyb->hurt();
					m_ship->hurt();
				}
			}
			/*if (!m_screenRec.intersectsRect(enemyb->boundingBox())) {
				enemyb->destory();*/
			//}
		}

	}
}
//�����µķɴ�
void GameScene::checkIsborn()
{
	if (!m_ship)
	{
		m_ship = Ship::create();
		this->addChild(m_ship,3000,101);
	}
		
	
	
}

void GameScene::doPause(CCObject *psender)
{
	CCDirector::sharedDirector()->pause();
	//removeFromParentAndCleanup(true);
	
	//m_pauseOrplay->setVisible(isPaused);
	
	Pause1 *layer = Pause1::create();
	this->addChild(layer);
}	

void GameScene::ScoreCount(float dt)
{
	m_time++;
	enemyCount(m_time);
}

void GameScene::enemyCount(float dt)
{
	createEnemy();
}

