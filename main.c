#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include "protocol.h"
#include "show_map.h"
#include "int_map.h"
#include "game.h"
#include "run.h"
//#define BAT_TRAIT		{row/2,col/4,BAT_ATK,BAT_DEF,BAT_HP,BAT_RANGE,BAT_NAME}
//#define HERO_TRAIT		{0,0,HERO_ATK,HERO_DEF,HERO_HP,HERO_RANGE,HERO_NAME}

int main(int argv, char * argc[])
{
	int ** map;
	int row,col;
	//1.确定战场的大小
	fprintf(stdout,"请输入战场的高和宽,(用逗号隔开):____\b\b\b\b");
	scanf("%d,%d",&row,&col);
	//2.玩家1,玩家2,的初值设定好,id,对手id,初始坐标x,y,金钱数10000,所拥有士兵的链表头,炮台属性
	struct PL_Msg msg1 = {2,3,0,0,10000,0,NULL};
	struct PL_Msg msg2 = {3,2,0,col/2+1,10000,0,NULL};
	//3.获得战斗地图并打扫战场
	map = get_map(row,col);
	zero_map(map,row,col);
	c_show_map(map,row,col,&msg1,&msg2);
	//添加：放置炮台
	*(*(map+row/2)+col/4) = ((msg1.my_self<<DATA_SEG)|BAT);
	*(*(map+row/2)+col/4+col/2) = ((msg2.my_self<<DATA_SEG)|BAT);
	//4.玩家通过操作地图,放置士兵
	char opt;
	while((msg1.ok == 0 || msg2.ok == 0) && (opt = get_opt()) && opt != QUIT)
	{
		control_map(map,row,col,&msg1,&msg2,opt);
		c_show_map(map,row,col,&msg1,&msg2);
	}
	//5.获得己方所有士兵的位置并存入数组
	//----1.玩家
	int counts = num_counts(map,row,col,msg1.my_self);//获得士兵数量
	int * array = get_array(counts);//申请同大小数组
	get_num_all_pos(map,col,row,msg1.my_self,array);//将所有士兵的位置存入数组
	add_soldiers(&(msg1.head),map,col,counts,array);//通过对应位置的添加相应类型的士兵
	free(array);
	//----2.玩家
	counts = num_counts(map,row,col,msg2.my_self);
	array = get_array(counts);
	get_num_all_pos(map,row,col,msg2.my_self,array);
	add_soldiers(&(msg2.head),map,col,counts,array);
	free(array);
	//6.战斗环节:直至一方士兵全灭战斗结束
	while(msg1.head && msg2.head)
	{
		//-1.A玩家打B玩家,B玩家打A玩家
		fights(msg1.head,msg2.head);
		fights(msg2.head,msg1.head);

		//-2.A玩家和B玩家各走一步,攻击过的不能走
		//走之前进行排序前排的先走
		rank_soldier(&(msg1.head),0,0);//0,0代表距离(0,0)坐标最远的士兵排前面
		rank_soldier(&(msg2.head),row-1,col-1);//表示距离(row-1,col-1)最远的士兵排前面

		print_soldiers(msg1.head,msg2.head);//输出士兵

		runs(&msg1,map,row,col);
		runs(&msg2,map,row,col);
		//-4.删除死亡的士兵
		del_dead_soldier(&(msg1.head),map);
		del_dead_soldier(&(msg2.head),map);
		sleep(1);
		c_show_map(map,row,col,&msg1,&msg2);
	}
	//7.战斗结束,判断输赢
	if(msg1.head == NULL && msg2.head)
	{
		printf("玩家2赢了.\n");
		del_all_soldier(&(msg1.head));
	}
	else if(msg2.head == NULL && msg1.head)
	{
		printf("玩家1赢了.\n");
		del_all_soldier(&(msg1.head));

	}
	else
	{
		printf("平手.\n");
	}
	//释放地图
	free_map(map,col);
	
	return 0;
}



