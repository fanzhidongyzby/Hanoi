#include "StdAfx.h"
#include "Plate.h"

Plate::Plate(int x,int y,int w,int h,int id)
{
	this->x=x;
	this->y=y;
	this->w=w;
	this->h=h;
	this->id=id;	
	dropTimes=0;//下降的次数，最大是10
}

void Plate::paint(CDC&dc)
{
	CRect r;
	CString s;
	r.SetRect(x-w/2,y-h/2,x+w/2,y+h/2);
	s.Format("%d",id);
	dc.Ellipse(r);
	dc.DrawText(s,r,DT_CENTER);
}
int Plate::drop()
{
	dropTimes++;
	if(dropTimes>10)
		return 0;
	y+=60-6*(dropTimes-1)-6/2;
	return 1;
}
Plate::~Plate(void)
{
}
