#include "Tob.h"
#include "Point.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define random(x) (rand()%x)
#define randomrange(i,j) (rand()%(j-i+1)+i)

Tob::Tob()
{

}


Tob::~Tob()
{

}

Point* Tob::generateT()
{

	srand((int)time(0));
	obT[0].x = randomrange(0,7);
	obT[0].y = randomrange(1,8);
	obT[1].x = obT[0].x;
	obT[1].y = obT[0].y - 1;
	obT[2].x = obT[0].x;
	obT[2].y = obT[0].y + 1;
	obT[3].x = obT[0].x+1;
	obT[3].y = obT[0].y;
	obT[4].x = obT[0].x + 2;
	obT[4].y = obT[0].y;

	return obT;
}