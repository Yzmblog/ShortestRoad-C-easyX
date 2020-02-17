#include "Obstacle.h"
#include "Point.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define random(x) (rand()%x)


Obstacle::Obstacle()
{

}


Obstacle::~Obstacle()
{

}

Point Obstacle::generate()
{
	
	srand((int)time(0));
	ob.x = random(10);
	ob.y = random(10);
	
	return ob;
}