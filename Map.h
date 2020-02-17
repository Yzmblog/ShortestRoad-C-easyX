#pragma once
#include "Point.h"
#include <vector>




class Map
{
public:
	Map();
	~Map();
	void show();
	void road(Point s, Point e);
	void start_and_end();
	void setob();
	void regenerate();
	Point get_start();
	Point get_end();
	int scan(Point s, int dir);
	int road2(Point s);
	void paint(Point s);


private:
	int map1[10][10];
	int h;
	int w;
	int obnum;
	Point start;
	Point end;
	Point *ob=new Point[obnum];
};

