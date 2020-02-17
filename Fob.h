#pragma once
#include "Obstacle.h"
class Fob :
	public Obstacle
{
public:
	Fob();
	~Fob();
	Point* generateF();
private:
	Point obF[4];
};

