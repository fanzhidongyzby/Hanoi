#pragma once
#include "Plate.h"
#include <vector>
using namespace std;
class Stakes
{
private:
	vector<Plate*>list[3];
public:
	Stakes(void);
	void genOnePlate(int id,int n);//盘子个数
	int dropDown();//把准备的盘子落下
	void paint(CDC&dc);
	Plate* beginMove(int a,int b,CPoint*pos);//开始移动
	void endMove(Plate*cur);//结束移动
	void clear();
	~Stakes(void);
};

