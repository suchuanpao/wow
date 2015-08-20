#include<stdlib.h>
#include"protocol.h"
#include"data_structure.h"
#include"int_map.h"
#include"run.h"

//功能：将玩家信息与地图传入,集体走一步
int runs(struct PL_Msg * player, int ** map, int row, int col)
{
	struct Soldier * tmp = player->head;
	int ** tmp_map = get_map(row,col);
	struct Queue * tail;
	int dir = 0, ok = 0, pos;
	while(tmp != NULL)
	{
		//如果处于战斗状态则回复为行走状态,否则开始行走
		if(tmp->state == FIGHTING)
		{
			tmp->state = RUNNING;
		}
		else if(tmp->state == RUNNING)
		{
			copy_map(tmp_map,map,row,col);
			tail = in_queue();
			//将坐标与方向同时收起来赋值给pos
			tail->pos = ((tmp->x)*col+(tmp->y))*col+dir;
			dir = get_dir(tmp_map,row,col,player->aim,&ok);
			//原来的士兵的位置位置为0
			pos = *(*(map+tmp->x)+tmp->y);
			*(*(map+tmp->x)+tmp->y) = NONE;
			run(dir,&(tmp->x),&(tmp->y));
			*(*(map+tmp->x)+tmp->y) = pos;
		}
		tmp = tmp->next;
		dir = 0;
		ok = 0;
	}
	free_map(tmp_map,row);
	return 1;
}

//功能：根据方向,对x,y坐标进行一次变化
int run(int dir, int * x, int * y)
{
	switch(dir)
	{
		case UP:
			(*x)--;
			break;
		case DOWN:
			(*x)++;
			break;
		case LEFT:
			(*y)--;
			break;
		case RIGHT:
			(*y)++;
			break;
	}
	return dir;

}

//功能：获得最近的一个士兵的方向
int get_dir(int** map, int row, int col,int aim,int * ok)
{
	struct Queue * tail;
	int i, j, x, y, pos, dir;
	pos = de_queue();
	dir = pos%col;
	pos = pos/col;
	x = pos/col;
	y = pos%col;
	//获得周边数值
	for(i = -1; i <= 1; i++)
	{
		if((x+i) < 0 || (x+i) >= row)
		{
			continue;
		}
		for(j = -1; j <= 1; j++)
		{
			if( ((y+j) < 0) || ((y+j) >= col) || (i == j) || (i == -j))
			{
				continue;
			}
			if( *(*(map+x+i)+y+j) == NONE)
			{
				//如果为空则存放起来
				if(*ok == 0)
				{
					dir = choose_dir(i,j);
				}
				tail = in_queue();
				//将坐标与方向同时收起来赋值给pos
				tail->pos = ((x+i)*col+(y+j))*col+dir;
				*(*(map+x+i)+y+j) = FLAG_NONE;
			}
			else if((*(*(map+x+i)+y+j)>>WEIYI) == aim)
			{
				//返回前清空队列
				free_queue();
				return dir;
			}
		}
	}
	*ok = 1;
	if(is_queue_empty())
	{
		return dir;
	}
	return get_dir(map,row,col,aim,ok);
}


int choose_dir(int i, int j)
{
	if((i == -1) && (j == 0))
	{
		return UP;
	}
	else if((i == 0) && (j == -1))
	{
		return LEFT;
	}
	else if((i == 0) && (j == 1))
	{
		return RIGHT;
	}
	else if((i == 1) && (j == 0))
	{
		return DOWN;
	}
	return NO_DIR;
}



