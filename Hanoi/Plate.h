#pragma once
class Plate
{
private:
	
	int w,h;
	int id;
	int dropTimes;
public:	
	int x,y;
	Plate(int x,int y,int w,int h,int id);
	void paint(CDC&dc);
	int drop();
	~Plate(void);
};

