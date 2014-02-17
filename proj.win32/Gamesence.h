#ifndef GAME_SCENE_H
#define GAME_SCENE_H
#include "cocos2d.h"
#include "Ships.h"
#include "Enemy.h"
#include "config.h"
#include "Pauselawer.h"

enum GameState
{
	Playing = 1,
	Pause = 2
};
class GameScene:public cocos2d::CCLayer
{
private:
	cocos2d::CCSprite *m_skyback;
	float m_skybackHeight;
	cocos2d::CCSprite *m_skybackRe;

	cocos2d::CCTMXTiledMap *m_tileMap;
	float m_tileMapHeight;
	cocos2d::CCTMXTiledMap *m_tileMapRe;

	bool isloadSky;
	bool isloadtileMap;

	Ship* m_ship;//创建飞船
	Enemy *m_eneny;
	cocos2d::CCSize winsize;	
	int enemycount;//判断屏幕上面的飞船数目
	CCSize shipsize;//飞船的大小
public:
	GameScene();
	~GameScene();
	static cocos2d::CCScene* scene();
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(cocos2d::CCTouch *cTouch, cocos2d::CCEvent *cEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *cTouch, cocos2d::CCEvent *cEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *cTouch, cocos2d::CCEvent *cEvent);

	void initBackground();
	void moveBackground(float dt);
	virtual void update(float dt);
	//敌船的移动方式
	void moveenemy(int type);
	//创建敌船
	void createEnemy();
	//检验两个节点的区域是否重叠
	bool collide(unSprite *a, unSprite *b);
	//检测是否相撞
	void checkIsCollide();
	void checkIsborn();

	void removeUpdate(float dt);
	//EnemyType Getenmy();
	//Ship* getship();
	vector<EnemyType> enemtype;
	//EnemyType enemtype;
	EnemyType *enty;
	CCRect m_screenRec;
	CCLabelBMFont *m_score;//分数显示
	CCLabelTTF *m_lifeCount;
	//暂停判断
	void doPause(CCObject *psender);
	//分数计算
	void ScoreCount(float dt);
	int m_time;//生成次数
	void enemyCount(float dt);
	CREATE_FUNC(GameScene);
};
#endif