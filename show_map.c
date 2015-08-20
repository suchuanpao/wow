#include<stdlib.h>
#include<stdio.h>
#include"protocol.h"
#include"show_map.h"


//输出长度相等的不同字符
void print_number(int val, int self1, int self2)
{
	if((val >> WEIYI) == self1)
	{
		switch(val & DATA_SEG)
		{
			case ARCHAR:	
				P_ARCHAR1();
				break;
			case KNIGHT:
				P_KNIGHT1();
				break;
			case INFANT:
				P_INFANT1();
				break;
			case BAT:
				P_BAT1();
				break;
		}
	}
	else
	{
		switch(val & DATA_SEG)
		{
			case 0:
				ZERO_SPACE();
				break;
			case ARCHAR:	
				P_ARCHAR2();
				break;
			case KNIGHT:
				P_KNIGHT2();
				break;
			case INFANT:
				P_INFANT2();
				break;
			case BAT:
				P_BAT2();
				break;
		}
	}
	return;
}

int print_flick(int val)
{
	switch(val & DATA_SEG)
	{
		case 0:
			FLICKER_SPACE();
			break;
		case ARCHAR:
			FLICKER_ARCHAR();
			break;
		case KNIGHT:
			FLICKER_KNIGHT();
			break;
		case INFANT:
			FLICKER_INFANT();
			break;
		case BAT:
			FLICKER_BAT();
			break;
	}
	return 1;
}


void c_show_map(int **map,int row, int col, struct PL_Msg* msg1, struct PL_Msg * msg2)
{
	system("clear");
	printf("玩家1按w,a,s,d移动光标,'u','i','o'放置士兵,按y确认结束,玩家2按上下左右移动光标,'b','n','m'放置士兵,按v键确认结束.只有10000金币,骑士500,步兵300,弓箭手200金币.\n");
	printf("玩家1剩余金币：%d,玩家2剩余金币：%d\n",msg1->money,msg2->money);
	int i, j;
	for(i = 0; i < row; i++)
	{
		//输出数字
		for(j = 0; j < col; j++)
		{
			VERTICAL();
			if((i == msg1->x && j == msg1->y)||(i == msg2->x && j == msg2->y))
			{
				print_flick(*(*(map+i)+j));
			}
			else
			{
				print_number(*(*(map+i)+j),msg1->my_self,msg2->my_self);
			}
		}
		VERTICAL();
		putchar('\n');
	}
}



