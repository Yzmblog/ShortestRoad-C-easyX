#pragma once
#include "Obstacle.h"
class Tob :
	public Obstacle
{
public:
	Tob();
	~Tob();
	Point* generateT();
private:
	Point obT[5];

};

