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
	void genOnePlate(int id,int n);//���Ӹ���
	int dropDown();//��׼������������
	void paint(CDC&dc);
	Plate* beginMove(int a,int b,CPoint*pos);//��ʼ�ƶ�
	void endMove(Plate*cur);//�����ƶ�
	void clear();
	~Stakes(void);
};

