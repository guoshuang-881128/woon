#ifndef CONFIG_H
#define  CONFIG_H
#include "cocos2d.h"
#include <vector>

using namespace std;


typedef struct  
{
	string enemtypename;//�д�������
	int movetype;//�д����ƶ���ʽ
	int m_hp;//�д���Ѫ��
	int score;//�д��ķ���
	string bulletname;//�ӵ�������
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