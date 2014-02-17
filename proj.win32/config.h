#ifndef CONFIG_H
#define  CONFIG_H
#include "cocos2d.h"
#include <vector>

using namespace std;


typedef struct  
{
	string enemtypename;//敌船的类型
	int movetype;//敌船的移动方式
	int m_hp;//敌船的血量
	int score;//敌船的分数
	string bulletname;//子弹的名字
	int type;
}EnemyType;

class Config
{
public:
	Config();
	~Config();
	vector<EnemyType> enemys;
	
	static Config* shareconfig();
	vector<EnemyType>  getenemytype();
	int lifecount;
	 int GetConfig();
};

#endif