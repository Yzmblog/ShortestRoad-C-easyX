#include "Map.h"
#include <iostream>
#include "graphics.h"

using namespace std;


int main()
{
	

	Map map1; 


	map1.setob(); //随机生成地图障碍物
	map1.start_and_end(); //随机生成起点和终点

	map1.show(); //输出地图信息

	
	while (1)
	{
		mouse_msg mousem = getmouse();//获取鼠标信息

		if (mousem.msg == mouse_msg_down)
		{

			if (mousem.x >= 650 && mousem.x <= 770 && mousem.y >= 100 && mousem.y <= 130) //按下重新生成
			{
				
				map1.regenerate(); //重新生成地图
				map1.setob();
				map1.start_and_end();
				map1.show();

			}
			else   if (mousem.x >= 650 && mousem.x <= 770 && mousem.y >= 200 && mousem.y <= 230) //按下展示路径
			{
				setlinewidth(3);
				setcolor(BLACK);
				setfillcolor(BLACK);
				
				map1.road(map1.get_start(), map1.get_end()); //展示最短路径算法结果

			}
	}
	

	}



	getch();

	
	return 0;
}
