#include "StdAfx.h"
#include "Stakes.h"


Stakes::Stakes(void)
{
}

void Stakes::clear()
{
	for(int j=0;j<3;j++)
	{
		for(UINT i=0;i<list[j].size();i++)
		{
			delete list[j][i];
		}
		list[j].clear();
	}
}
Stakes::~Stakes(void)
{
	clear();
}

void Stakes::genOnePlate(int id,int n)
{
	//static int n=id;//从第n个盘子开始
	int x0=100,y0=300-5-4-8;
	list[0].push_back(new Plate(x0,y0-300-20*(n-id),20+(n-1)*15-(n-id)*15,16,id));
}
int Stakes::dropDown()
{
	int sum=0;
	for(UINT i=0;i<list[0].size();i++)
	{
		sum+=list[0][i]->drop();
	}
	return(sum!=0);
}
void Stakes::paint(CDC&dc)
{
	for(int j=0;j<3;j++)
		for(UINT i=0;i<list[j].size();i++)
		{
			list[j][i]->paint(dc);
		}
}
Plate* Stakes::beginMove(int a,int b,CPoint* pos)
{
	Plate*curPlate=list[a][list[a].size()-1];
	pos[0].x=curPlate->x;
	pos[0].y=curPlate->y;
	pos[1].x=100+175*b;
	pos[1].y=300-5-4-8-list[b].size()*20;
	list[a].pop_back();
	return curPlate;
}
void Stakes::endMove(Plate*cur)
{
	int index=(cur->x-100)/175;
	list[index].push_back(cur);
}