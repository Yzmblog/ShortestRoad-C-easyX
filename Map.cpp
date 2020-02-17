#include "Map.h"
#include "graphics.h"
#include<stdlib.h>
#include<time.h>
#include "Obstacle.h"
#include "Tob.h"
#include "Fob.h"
#include  <math.h>
#include <iostream>

#define random(x) (rand()%x) 
#define randomrange(i,j) (rand()%(j-i+1)+i)////自定义范围随机数函数

using namespace std;


Map::Map()
{
	h = 10;
	w = 10;
	Tob T1;
	Fob F1;
	Point Tobstacle[5];
	Point* T = Tobstacle;
	T = T1.generateT();

	Point Fangobstacle[5];
	Point* F = Fangobstacle;
	F = F1.generateF();

	
	
	obnum = randomrange(35, 45);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			map1[i][j] = 0;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		ob[i] = T[i];
	}

	for (int i = 5; i < 9; i++)
	{
		ob[i] = F[i-5];
	}


	for (int i = 9; i < obnum; i++)
	{
		ob[i].x = random(9);
		ob[i].y = random(9);
	}



}
Map::~Map()
{
	delete[] ob;
}

double distance(Point a, Point b) //自定义距离函数 
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y- b.y) * (a.y-b.y));

}

void Map::show() //绘制地图
{
	

	

	initgraph(900, 700);
	setcaption("Shortest Road");
	
	setrendermode(RENDER_AUTO);

	setbkcolor(WHITE);
	cleardevice();
	setlinewidth(3);
	setcolor(BLACK);
	setfillcolor(BLACK);
	for (int i = 50; i <= w * 50 + 50; i = i + 50)
	{
		line(50, i, (w+1) * 50, i);
	}
	for (int i = 50; i <= h * 50 + 50; i = i + 50)
	{
		line(i, 50, i, (h+1) * 50);
	}




	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			if (map1[i][j]==1)
			{
				setcolor(BLACK);
				setfillcolor(BLACK);
				bar((i+1)*50,(j+1)*50, (i + 2) * 50, (j + 2) * 50);
			}
			if (map1[i][j] == 2)
			{
				setcolor(RED);
				setfillcolor(RED);
				pieslice((i+1)* 50+25, (j+1) * 50+25,0,360,9);

			}
			if (map1[i][j] == 3)
			{
				setcolor(BLUE);
				setfillcolor(BLUE);
				pieslice((i+1) * 50 + 25, (j+1) * 50 + 25, 0, 360, 9);

			}

		}
	}


	setfont(20, 0, "宋体");
	setcolor(BLACK);
	setfillcolor(BLACK);

	outtextxy(50, 600, "提示信息：");
	outtextxy(50,630,"红色点是起点，蓝色点是终点，点击右方重新生成可重新生成地图，点击展示路径可显示路径");

	setfont(30, 0, "宋体");
	outtextxy(650, 100, "重新生成");
	outtextxy(650, 200, "展示路径");
	
	
}


void Map::start_and_end()  //获取随机障碍物信息
{ 
	
	int i = 1;
	while (i)
	{
		start.x = random(9);
		start.y = random(9);
		end.x = random(9);
		end.y = random(9);



		if (map1[start.x][start.y] || map1[end.x][end.y] || distance(start,end)<=5)
		{

			continue;
		}
		else
		{
			map1[start.x][start.y] = 2;
			map1[end.x][end.y] = 3;
			i = 0;
		}

	}
	

	
}

void Map::road(Point s, Point e) //算法1 // 使用递归算法趋合斜率
{

	if ((abs(s.x-e.x)==1 && abs(s.y-e.y)==1) || (abs(s.x - e.x) == 0 && abs(s.y - e.y) == 1) || (abs(s.x - e.x) == 1 && abs(s.y - e.y) == 0))//最后一步
	{

		line((s.x+1)*50+25, (s.y + 1) * 50 + 25, (e.x + 1) * 50 + 25, (e.y + 1) * 50 + 25);
	}//递归终点

	else if (s.x == e.x)//垂直同线
	{
		if (s.y > e.y)
		{
			if (map1[s.x][s.y - 1] == 0 )//上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 1) * 50 + 25, s.y * 50 + 25);
				s.y -= 1;
				road(s,e); //调用递归
			}
			else if (map1[s.x-1][s.y - 1] == 0 && (map1[s.x][s.y - 1] == 0 || map1[s.x - 1][s.y] == 0) )//左上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, s.x * 50 + 25, s.y * 50 + 25);
				s.x -= 1;
				s.y -= 1;
				road(s, e);
			}
			else if (map1[s.x + 1][s.y - 1] == 0 && (map1[s.x][s.y - 1] == 0 || map1[s.x + 1][s.y] == 0) )//右上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x+2) * 50 + 25, s.y * 50 + 25);
				s.x += 1;
				s.y -= 1;
				road(s, e);
			}
			else if (map1[s.x - 1][s.y ] == 0 )//左
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x) * 50 + 25, (s.y+1) * 50 + 25);
				s.x -= 1;
				road(s, e);
			}
			else if (map1[s.x + 1][s.y] == 0 )//右
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x+2) * 50 + 25, (s.y + 1) * 50 + 25);
				s.x += 1;
				road(s, e);
			}
			else if (map1[s.x - 1][s.y+1] == 0 && (map1[s.x - 1][s.y] == 0 || map1[s.x][s.y + 1] == 0))//左下
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x ) * 50 + 25, (s.y + 2) * 50 + 25);
				s.x -= 1;
				s.y += 1;
				road(s, e);
			}
			else if (map1[s.x + 1][s.y+1] == 0 && (map1[s.x + 1][s.y] == 0 || map1[s.x][s.y + 1] == 0))//右下
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x+2) * 50 + 25, (s.y + 2) * 50 + 25);
				s.x += 1;
				s.y += 1;
				road(s, e);
			}
			else if (map1[s.x][s.y + 1] == 0 )//下
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 1) * 50 + 25, (s.y + 2) * 50 + 25);
				s.y += 1;
				road(s, e);
			}


		}
		else if (s.y < e.y)
		{
			if (map1[s.x][s.y + 1] == 0)//下
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 1) * 50 + 25, (s.y+2) * 50 + 25);
				s.y += 1;
				road(s, e);
			}
			else if (map1[s.x - 1][s.y + 1] == 0 && (map1[s.x - 1][s.y] == 0 || map1[s.x][s.y + 1] == 0))//左下
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, s.x * 50 + 25, (s.y+2) * 50 + 25);
				s.x -= 1;
				s.y += 1;
				road(s, e);
			}
			else if (map1[s.x + 1][s.y + 1] == 0 && (map1[s.x + 1][s.y] == 0 || map1[s.x][s.y + 1] == 0))//右下
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, (s.y+2) * 50 + 25);
				s.x += 1;
				s.y += 1;
				road(s, e);
			}
			else if (map1[s.x - 1][s.y] == 0)//左
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x) * 50 + 25, (s.y + 1) * 50 + 25);
				s.x -= 1;
				road(s, e);
			}
			else if (map1[s.x + 1][s.y] == 0)//右
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, (s.y + 1) * 50 + 25);
				s.x += 1;
				road(s, e);
			}
			else if (map1[s.x - 1][s.y - 1] == 0 && (map1[s.x][s.y - 1] == 0 || map1[s.x - 1][s.y] == 0))//左上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x) * 50 + 25, (s.y) * 50 + 25);
				s.x -= 1;
				s.y -= 1;
				road(s, e);
			}
			else if (map1[s.x + 1][s.y - 1] == 0 && (map1[s.x][s.y - 1] == 0 || map1[s.x + 1][s.y] == 0))//右上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, (s.y) * 50 + 25);
				s.x += 1;
				s.y -= 1;
				road(s, e);
			}
			else if (map1[s.x][s.y - 1] == 0)//上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 1) * 50 + 25, (s.y) * 50 + 25);
				s.y -= 1;
				road(s, e);
			}
		}

	}
	else 
	{
		double k = (e.y - s.y) / (e.x - s.x);//计算斜率//水平同线
		if (k == 0 && e.x > s.x)
		{
			if(map1[s.x + 1][s.y] == 0)//右
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, (s.y + 1) * 50 + 25);
				s.x += 1;
				road(s, e);
			}
			else if (map1[s.x + 1][s.y - 1] == 0 && (map1[s.x][s.y - 1] == 0 || map1[s.x + 1][s.y] == 0))//右上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, s.y * 50 + 25);
				s.x += 1;
				s.y -= 1;
				road(s, e);
			}
			else if (map1[s.x + 1][s.y + 1] == 0 && (map1[s.x + 1][s.y] == 0 || map1[s.x][s.y + 1] == 0))//右下
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, (s.y + 2) * 50 + 25);
				s.x += 1;
				s.y += 1;
				road(s, e);
			}
			else if (map1[s.x][s.y - 1] == 0 )//上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 1) * 50 + 25, s.y * 50 + 25);
				s.y -= 1;
				road(s, e);
			}
			else if (map1[s.x][s.y + 1] == 0)//下
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 1) * 50 + 25, (s.y + 2) * 50 + 25);
				s.y += 1;
				road(s, e);
			}
			else if (map1[s.x - 1][s.y - 1] == 0 && (map1[s.x][s.y - 1] == 0 || map1[s.x - 1][s.y] == 0))//左上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, s.x * 50 + 25, s.y * 50 + 25);
				s.x -= 1;
				s.y -= 1;
				road(s, e);
			}
			else if (map1[s.x - 1][s.y + 1] == 0 && (map1[s.x - 1][s.y] == 0 || map1[s.x][s.y + 1] == 0))//左下
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x) * 50 + 25, (s.y + 2) * 50 + 25);
				s.x -= 1;
				s.y += 1;
				road(s, e);
			}
			else if (map1[s.x - 1][s.y] == 0)//左
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x) * 50 + 25, (s.y + 1) * 50 + 25);
				s.x -= 1;
				road(s, e);
			}
		}
		else if (k == 0 && e.x < s.x)
		{
			if (map1[s.x - 1][s.y] == 0)//左
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x) * 50 + 25, (s.y + 1) * 50 + 25);
				s.x -= 1;
				road(s, e);
			}
			else if (map1[s.x - 1][s.y - 1] == 0 && (map1[s.x][s.y - 1] == 0 || map1[s.x - 1][s.y] == 0))//左上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, s.x * 50 + 25, s.y * 50 + 25);
				s.x -= 1;
				s.y -= 1;
				road(s, e);
			}
			else if (map1[s.x - 1][s.y + 1] == 0 && (map1[s.x - 1][s.y] == 0 || map1[s.x][s.y + 1] == 0))//左下
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x) * 50 + 25, (s.y + 2) * 50 + 25);
				s.x -= 1;
				s.y += 1;
				road(s, e);
			}
			else if (map1[s.x][s.y - 1] == 0 )//上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 1) * 50 + 25, s.y * 50 + 25);
				s.y -= 1;
				road(s, e);
			}
			else if (map1[s.x][s.y + 1] == 0)//下
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 1) * 50 + 25, (s.y + 2) * 50 + 25);
				s.y += 1;
				road(s, e);
			}
			else if (map1[s.x + 1][s.y - 1] == 0 && (map1[s.x][s.y - 1] == 0 || map1[s.x + 1][s.y] == 0))//右上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, s.y * 50 + 25);
				s.x += 1;
				s.y -= 1;
				road(s, e);
			}
			else if (map1[s.x + 1][s.y + 1] == 0 && (map1[s.x + 1][s.y] == 0 || map1[s.x][s.y + 1] == 0))//右下
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, (s.y + 2) * 50 + 25);
				s.x += 1;
				s.y += 1;
				road(s, e);
			}
			else if (map1[s.x + 1][s.y] == 0)//右
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, (s.y + 1) * 50 + 25);
				s.x += 1;
				road(s, e);
			}
		}
		else if(k < 0 && e.x > s.x)
		{
			if (map1[s.x + 1][s.y - 1] == 0 && (map1[s.x][s.y - 1] == 0 || map1[s.x + 1][s.y] == 0))//右上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, s.y * 50 + 25);
				s.x += 1;
				s.y -= 1;
				road(s, e);
			}
			else if (map1[s.x][s.y - 1] == 0 )//上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 1) * 50 + 25, s.y * 50 + 25);
				s.y -= 1;
				road(s, e);
			}
			else if (map1[s.x + 1][s.y] == 0)//右
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, (s.y + 1) * 50 + 25);
				s.x += 1;
				road(s, e);
			}
			else if (map1[s.x - 1][s.y - 1] == 0 && (map1[s.x][s.y - 1] == 0 || map1[s.x - 1][s.y] == 0))//左上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, s.x * 50 + 25, s.y * 50 + 25);
				s.x -= 1;
				s.y -= 1;
				road(s, e);
			}
			else if (map1[s.x + 1][s.y + 1] == 0 && (map1[s.x + 1][s.y] == 0 || map1[s.x][s.y + 1] == 0))//右下
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, (s.y + 2) * 50 + 25);
				s.x += 1;
				s.y += 1;
				road(s, e);
			}
			else if (map1[s.x - 1][s.y] == 0)//左
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x) * 50 + 25, (s.y + 1) * 50 + 25);
				s.x -= 1;
				road(s, e);
			}
			else if (map1[s.x][s.y + 1] == 0)//下
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 1) * 50 + 25, (s.y + 2) * 50 + 25);
				s.y += 1;
				road(s, e);
			}
			else if (map1[s.x - 1][s.y + 1] == 0 && (map1[s.x - 1][s.y] == 0 || map1[s.x][s.y + 1] == 0))//左下
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x) * 50 + 25, (s.y + 2) * 50 + 25);
				s.x -= 1;
				s.y += 1;
				road(s, e);
			}
		}
		else if (k < 0 && e.x < s.x)
		{
			if (map1[s.x - 1][s.y + 1] == 0 && (map1[s.x - 1][s.y] == 0 || map1[s.x][s.y + 1] == 0))//左下
				{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x) * 50 + 25, (s.y + 2) * 50 + 25);
				s.x -= 1;
				s.y += 1;
				road(s, e);
				}
			else if (map1[s.x][s.y + 1] == 0)//下
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 1) * 50 + 25, (s.y + 2) * 50 + 25);
				s.y += 1;
				road(s, e);
			}
			else if (map1[s.x - 1][s.y] == 0)//左
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x) * 50 + 25, (s.y + 1) * 50 + 25);
				s.x -= 1;
				road(s, e);
			}
			else if (map1[s.x + 1][s.y + 1] == 0 && (map1[s.x + 1][s.y] == 0 || map1[s.x][s.y + 1] == 0))//右下
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, (s.y + 2) * 50 + 25);
				s.x += 1;
				s.y += 1;
				road(s, e);
			}
			else if (map1[s.x - 1][s.y - 1] == 0 && (map1[s.x][s.y - 1] == 0 || map1[s.x - 1][s.y] == 0))//左上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, s.x * 50 + 25, s.y * 50 + 25);
				s.x -= 1;
				s.y -= 1;
				road(s, e);
			}
			else if (map1[s.x + 1][s.y] == 0)//右
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, (s.y + 1) * 50 + 25);
				s.x += 1;
				road(s, e);
			}
			else if (map1[s.x][s.y - 1] == 0 )//上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 1) * 50 + 25, s.y * 50 + 25);
				s.y -= 1;
				road(s, e);
			}
			else if (map1[s.x + 1][s.y - 1] == 0 && (map1[s.x][s.y - 1] == 0 || map1[s.x + 1][s.y] == 0))//右上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, s.y * 50 + 25);
				s.x += 1;
				s.y -= 1;
				road(s, e);
			}

		}
		else if (k > 0 && e.x < s.x)
		{
			if (map1[s.x - 1][s.y - 1] == 0 && (map1[s.x][s.y - 1] == 0 || map1[s.x - 1][s.y] == 0))//左上
				{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, s.x * 50 + 25, s.y * 50 + 25);
				s.x -= 1;
				s.y -= 1;
				road(s, e);
				}
			else if (map1[s.x - 1][s.y] == 0)//左
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x) * 50 + 25, (s.y + 1) * 50 + 25);
				s.x -= 1;
				road(s, e);
			}
			else if (map1[s.x][s.y - 1] == 0 )//上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 1) * 50 + 25, s.y * 50 + 25);
				s.y -= 1;
				road(s, e);
			}
			else if (map1[s.x - 1][s.y + 1] == 0 && (map1[s.x - 1][s.y] == 0 || map1[s.x][s.y + 1] == 0))//左下
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x) * 50 + 25, (s.y + 2) * 50 + 25);
				s.x -= 1;
				s.y += 1;
				road(s, e);
			}
			else if (map1[s.x + 1][s.y - 1] == 0 && (map1[s.x][s.y - 1] == 0 || map1[s.x + 1][s.y] == 0))//右上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, s.y * 50 + 25);
				s.x += 1;
				s.y -= 1;
				road(s, e);
			}
			else if (map1[s.x][s.y + 1] == 0)//下
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 1) * 50 + 25, (s.y + 2) * 50 + 25);
				s.y += 1;
				road(s, e);
			}
			else if (map1[s.x + 1][s.y] == 0)//右
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, (s.y + 1) * 50 + 25);
				s.x += 1;
				road(s, e);
			}
			else if (map1[s.x + 1][s.y + 1] == 0 && (map1[s.x + 1][s.y] == 0 || map1[s.x][s.y + 1] == 0))//右下
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, (s.y + 2) * 50 + 25);
				s.x += 1;
				s.y += 1;
				road(s, e);
			}

		}
		else if (k > 0 && e.x > s.x)
		{
			if (map1[s.x + 1][s.y + 1] == 0 && (map1[s.x + 1][s.y] == 0 || map1[s.x][s.y + 1] == 0))//右下
				{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, (s.y + 2) * 50 + 25);
				s.x += 1;
				s.y += 1;
				road(s, e);
				}
			else if (map1[s.x + 1][s.y] == 0)//右
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, (s.y + 1) * 50 + 25);
				s.x += 1;
				road(s, e);
			}
			else if (map1[s.x][s.y + 1] == 0)//下
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 1) * 50 + 25, (s.y + 2) * 50 + 25);
				s.y += 1;
				road(s, e);
			}
			else if (map1[s.x + 1][s.y - 1] == 0 && (map1[s.x][s.y - 1] == 0 || map1[s.x + 1][s.y] == 0))//右上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, s.y * 50 + 25);
				s.x += 1;
				s.y -= 1;
				road(s, e);
			}
			else if (map1[s.x - 1][s.y + 1] == 0 && (map1[s.x - 1][s.y] == 0 || map1[s.x][s.y + 1] == 0))//左下
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x) * 50 + 25, (s.y + 2) * 50 + 25);
				s.x -= 1;
				s.y += 1;
				road(s, e);
			}
			else if (map1[s.x][s.y - 1] == 0 )//上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 1) * 50 + 25, s.y * 50 + 25);
				s.y -= 1;
				road(s, e);
			}
			else if (map1[s.x - 1][s.y] == 0)//左
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x) * 50 + 25, (s.y + 1) * 50 + 25);
				s.x -= 1;
				road(s, e);
			}
			else if (map1[s.x - 1][s.y - 1] == 0 && (map1[s.x][s.y - 1] == 0 || map1[s.x - 1][s.y] == 0))//左上
			{
				line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, s.x * 50 + 25, s.y * 50 + 25);
				s.x -= 1;
				s.y -= 1;
				road(s, e);
			}

		}

		

	}
	
	
		
	

	
}

void Map::setob()  //在地图设置路障
{
	for (int i = 0; i < obnum; i++)
	{
		map1[ob[i].x][ob[i].y] = 1;
	}

}

Point Map::get_start() //获取起点
{
	return start;
}

Point Map::get_end() //获取终点
{
	return end;
}

void Map::regenerate() //重新生成地图
{
	h = 10;
	w = 10;
	Tob T1;
	Fob F1;
	Point Tobstacle[5];
	Point* T = Tobstacle;
	T = T1.generateT();

	Point Fangobstacle[5];
	Point* F = Fangobstacle;
	F = F1.generateF();



	obnum = randomrange(35, 45);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			map1[i][j] = 0;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		ob[i] = T[i];
	}

	for (int i = 5; i < 9; i++)
	{
		ob[i] = F[i - 5];
	}


	for (int i = 9; i < obnum; i++)
	{
		ob[i].x = random(9);
		ob[i].y = random(9);
	}

}


int Map::scan(Point s,int dir ) //扫描周围的点
{
	if (dir == 0 && s.x < 10 && s.x >= 0 && s.y < 10 && s.y >= 0)
		return map1[s.x + 1][s.y]; //右
	else if(dir==1 && s.x < 10 && s.x >= 0 && s.y < 10 && s.y >= 0)
		return map1[s.x + 1][s.y-1]; //you shang
	else if (dir == 2 && s.x < 10 && s.x >= 0 && s.y < 10 && s.y >= 0)
		return map1[s.x ][s.y - 1]; //shang
	else if (dir == 3 && s.x < 10 && s.x >= 0 && s.y < 10 && s.y >= 0)
		return map1[s.x - 1][s.y - 1]; //zuo shang
	else if (dir == 4 && s.x < 10 && s.x >= 0 && s.y < 10 && s.y >= 0)
		return map1[s.x - 1][s.y ]; //zuo
	else if (dir == 5 && s.x < 10 && s.x >= 0 && s.y < 10 && s.y >= 0)
		return map1[s.x-1][s.y + 1]; //zuoxia
	else if (dir == 6 && s.x < 10 && s.x >= 0 && s.y < 10 && s.y >= 0)
		return map1[s.x][s.y + 1]; //xia
	else if (dir == 7&& s.x < 10 && s.x >= 0 && s.y < 10 && s.y >= 0)
		return map1[s.x +1][s.y + 1]; //youxia


	return 0;
}

int Map::road2(Point s)  //第二种路径算法 //类似于蚁群算法，用分数代表蚂蚁走后留下的信息素//能到终点的点分数高，死路分数低
{

		for (int i = 0; i < 8; i++)
		{
			if (scan(s, i) == 3)
				map1[s.x][s.y]=200;
		}

		for (int i = 0; i < 8; i++)
		{
			if (scan( s, i) == 200)
				map1[s.x][s.y] = 100;
		}

		for (int i = 0; i < 8; i++)
		{
			if (scan( s, i) == 100)
				map1[s.x][s.y] = 50;
		}

		for (int i = 0; i < 8; i++)
		{
			if (scan( s, i) == 1)
				map1[s.x][s.y]--;
		}
		for (int i = 0; i < 8; i++)
		{
			if (scan( s, i) > 30)
				map1[s.x][s.y]++;
		}
		for (int i = 0; i < 8; i++)
		{
			if (scan( s, i) < 30)
				map1[s.x][s.y]--;
		}
		for (int i = 0; i < 8; i++)
		{
			if (scan(s, i) <= 15)
				map1[s.x][s.y]-=5;
		}
		if (map1[s.x + 2][s.y] == 1 && map1[s.x + 1][s.y - 1] == 1 && map1[s.x + 1][s.y + 1] == 1) //you
			map1[s.x+1][s.y] = 15;
		else if (map1[s.x - 2][s.y] == 1 && map1[s.x - 1][s.y - 1] == 1 && map1[s.x - 1][s.y + 1] == 1) //zuo
			map1[s.x - 1][s.y] = 15;
		else if (map1[s.x ][s.y-2] == 1 && map1[s.x + 1][s.y - 1] == 1 && map1[s.x - 1][s.y - 1] == 1) //shang
			map1[s.x ][s.y-1] = 15;
		else if (map1[s.x][s.y+2] == 1 && map1[s.x + 1][s.y + 1] == 1 && map1[s.x - 1][s.y + 1] == 1) //xia
			map1[s.x ][s.y+1] = 15;


		return 0;
	
}


void move(Point& s, int dir)  //点的位移函数
{
	if (dir == 0 && s.x < 10 && s.x >= 0 && s.y < 10 && s.y >= 0)
		s.x += 1; //右
	else if (dir == 1 && s.x < 10 && s.x >= 0 && s.y < 10 && s.y >= 0)
	{
		s.x += 1; s.y -= 1;
	} //you shang
	else if (dir == 2 && s.x < 10 && s.x >= 0 && s.y < 10 && s.y >= 0)
		s.y -= 1; //shang
	else if (dir == 3 && s.x < 10 && s.x >= 0 && s.y < 10 && s.y >= 0)
	{
		s.x -= 1; s.y -= 1;
	} //zuo shang
	else if (dir == 4 && s.x < 10 && s.x >= 0 && s.y < 10 && s.y >= 0)
		s.x -= 1; //zuo
	else if (dir == 5 && s.x < 10 && s.x >= 0 && s.y < 10 && s.y >= 0)
	{
		s.x -= 1; s.y += 1;
	} //zuoxia
	else if (dir == 6 && s.x < 10 && s.x >= 0 && s.y < 10 && s.y >= 0)
		s.y += 1; //xia
	else if (dir == 7 && s.x < 10 && s.x >= 0 && s.y < 10 && s.y >= 0)
	{
		s.y += 1; s.x += 1;
	} //youxia
}

void Map::paint(Point s)  //用于第二种算法的绘制路径
{
	int dir = 0;
	int value = 0;

	while (!(s.x == end.x && s.y == end.y))
	{
		for (int i = 0; i < 8; i++)
		{

			if (i == 0 && s.x + 1 < 10 && s.x + 1 >= 0 && s.y < 10 && s.y >= 0)
			{
				if (scan(s, i) >= value)
				{
					dir = i;
					value = scan(s, i);
				}

			}

			else if (i == 1 && s.x + 1 < 10 && s.x + 1 >= 0 && s.y - 1 < 10 && s.y - 1 >= 0)
			{
				if (scan(s, i) >= value)
				{
					dir = i;
					value = scan(s, i);
				}

			}
			else if (i == 2 && s.x < 10 && s.x >= 0 && s.y - 1 < 10 && s.y - 1 >= 0)
			{
				if (scan(s, i) >= value)
				{
					dir = i;
					value = scan(s, i);
				}

			}
			else if (i == 3 && s.x - 1 < 10 && s.x - 1 >= 0 && s.y - 1 < 10 && s.y - 1 >= 0)
			{
				if (scan(s, i) >= value)
				{
					dir = i;
					value = scan(s, i);
				}

			}
			else if (i == 4 && s.x - 1 < 10 && s.x - 1 >= 0 && s.y < 10 && s.y >= 0)
			{
				if (scan(s, i) >= value)
				{
					dir = i;
					value = scan(s, i);
				}

			}
			else if (i == 5 && s.x - 1 < 10 && s.x - 1 >= 0 && s.y + 1 < 10 && s.y + 1 >= 0)
			{
				if (scan(s, i) >= value)
				{
					dir = i;
					value = scan(s, i);
				}

			}
			else if (i == 6 && s.x < 10 && s.x >= 0 && s.y + 1 < 10 && s.y + 1 >= 0)
			{
				if (scan(s, i) >= value)
				{
					dir = i;
					value = scan(s, i);
				}

			}
			else if (i == 7 && s.x + 1 < 10 && s.x + 1 >= 0 && s.y + 1 < 10 && s.y + 1 >= 0)
			{
				if (scan(s, i) >= value)
				{
					dir = i;
					value = scan(s, i);
				}

			}
		}
		value = 0;

		if (dir == 0)
		{
			line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, (s.y + 1) * 50 + 25);//y
			move(s, dir);
		}
		else if (dir == 1)
		{
			line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, s.y * 50 + 25);//ys
			move(s, dir);
		}
		else if (dir == 2)
		{
			line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 1) * 50 + 25, s.y * 50 + 25); //s
			move(s, dir);

		}
		else if (dir == 3)
		{
			line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, s.x * 50 + 25, s.y * 50 + 25);//zs
			move(s, dir);
		}
		else if (dir == 4)
		{
			line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x) * 50 + 25, (s.y + 1) * 50 + 25);//z
			move(s, dir);
		}
		else if (dir == 5)
		{
			line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x) * 50 + 25, (s.y + 2) * 50 + 25);//zx
			move(s, dir);
		}
		else if (dir == 6)
		{
			line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 1) * 50 + 25, (s.y + 2) * 50 + 25);//x
			move(s, dir);
		}
		else if (dir == 7)
		{
			line((s.x + 1) * 50 + 25, (s.y + 1) * 50 + 25, (s.x + 2) * 50 + 25, (s.y + 2) * 50 + 25);//yx
			move(s, dir);
		}



















	}



}

