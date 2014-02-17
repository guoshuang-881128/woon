#include "config.h"
//#include "cocos2d.h"


USING_NS_CC;
using namespace cocos2d;
static Config *config = NULL;
Config::Config()
{
	lifecount = 3;
	//≥ı ºªØ
	EnemyType enemytype;
	enemytype.type = 0;
	enemytype.bulletname = "W2.png";
	enemytype.enemtypename = "E0.png";
	enemytype.m_hp = 1;
	enemytype.movetype = 0;
	enemytype.score = 20;
	enemys.push_back(enemytype);

	enemytype.type = 1;
	enemytype.enemtypename = "E1.png";
	enemytype.bulletname = "W2.png";
	enemytype.m_hp = 1;
	enemytype.movetype = 1;
	enemytype.score = 30;
	enemys.push_back(enemytype);

	enemytype.type =2;
	enemytype.enemtypename = "E2.png";
	enemytype.bulletname = "W2.png";
	enemytype.m_hp = 1;
	enemytype.movetype = 2;
	enemytype.score = 40;
	enemys.push_back(enemytype);

	enemytype.type = 3;
	enemytype.enemtypename = "E3.png";
	enemytype.bulletname = "W2.png";
	enemytype.m_hp = 1;
	enemytype.movetype = 2;
	enemytype.score = 50;
	enemys.push_back(enemytype);

	enemytype.type = 4;
	enemytype.enemtypename = "E4.png";
	enemytype.bulletname = "W2.png";
	enemytype.m_hp = 1;
	enemytype.movetype = 1;
	enemytype.score = 60;
	enemys.push_back(enemytype);

	enemytype.type = 5;
	enemytype.enemtypename = "E5.png";
	enemytype.bulletname = "W2.png";
	enemytype.m_hp = 1;
	enemytype.movetype = 0;
	enemytype.score = 100;
	enemys.push_back(enemytype);
}
Config::~Config()
{

}
Config* Config::shareconfig()
{
	if (!config)
	{
		config = new Config();
	}
	return config;
}

vector<EnemyType> Config::getenemytype()
{
	return enemys;
}

int Config::GetConfig()
{
	return lifecount;
}