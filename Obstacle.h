#pragma once
#include "Point.h"
class Obstacle
{
public:
	Obstacle();
	~Obstacle();
	Point generate();
private:
	Point ob;

};

