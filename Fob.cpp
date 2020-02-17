#include "Fob.h"
#include "Point.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define random(x) (rand()%x)
#define randomrange(i,j) (rand()%(j-i+1)+i)

Fob::Fob()
{

}


Fob::~Fob()
{

}

Point* Fob::generateF()
{

	srand((int)time(0));
	obF[0].x = randomrange(0,8);
	obF[0].y = randomrange(0, 8);
	obF[1].x = obF[0].x + 1;
	obF[1].y = obF[0].y;
	obF[2].x = obF[0].x;
	obF[2].y = obF[0].y+1;
	obF[3].x = obF[0].x + 1;
	obF[3].y = obF[0].y+1;

	return obF;
}
