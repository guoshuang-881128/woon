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

	Ship* m_ship;//�����ɴ�
	Enemy *m_eneny;
	cocos2d::CCSize winsize;	
	int enemycount;//�ж���Ļ����ķɴ���Ŀ
	CCSize shipsize;//�ɴ��Ĵ�С
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
	//�д����ƶ���ʽ
	void moveenemy(int type);
	//�����д�
	void createEnemy();
	//���������ڵ�������Ƿ��ص�
	bool collide(unSprite *a, unSprite *b);
	//����Ƿ���ײ
	void checkIsCollide();
	void checkIsborn();

	void removeUpdate(float dt);
	//EnemyType Getenmy();
	//Ship* getship();
	vector<EnemyType> enemtype;
	//EnemyType enemtype;
	EnemyType *enty;
	CCRect m_screenRec;
	CCLabelBMFont *m_score;//������ʾ
	CCLabelTTF *m_lifeCount;
	//��ͣ�ж�
	void doPause(CCObject *psender);
	//��������
	void ScoreCount(float dt);
	int m_time;//���ɴ���
	void enemyCount(float dt);
	CREATE_FUNC(GameScene);
};
#endif