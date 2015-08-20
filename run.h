#ifndef _RUN_H_
#define _RUN_H_




//功能：将链表头与地图传入,集体走一步
int runs(struct PL_Msg * player, int ** map, int row, int col);
//功能：根据方向,对x,y坐标进行一次变化
int run(int dir, int * x, int * y);
//功能：获得最近的一个士兵的方向
int get_dir(int** map, int row , int col, int aim,int * ok);
//功能：通过i,j的值获得一个方向
int choose_dir(int i, int j);
//功能：输入一个特定的方向使一个士兵的横坐标与纵坐标发生变化


#endif
