#include <stdlib.h>
#include<time.h>
#include <stdio.h>
#include"protocol.h"
#include "int_map.h"



void control_map(int ** map, int row, int col, struct PL_Msg* msg1, struct PL_Msg * msg2, char opt)
{		
	switch(opt)
	{
		case F_UP:
			if(msg1->x <= 0)
				msg1->x = 0;
			else
				msg1->x--;
			break;
		case F_LEFT:
			if(msg1->y <= 0)
				msg1->y = 0;
			else
				msg1->y--;
			break;
		case F_RIGHT:
			if(msg1->y >= col/2-1)
				msg1->y = col/2-1;
			else
				msg1->y++;
			break;
		case F_DOWN:
			if(msg1->x >= (row-1))
				msg1->x = row-1;
			else
				msg1->x++;
			break;
		case F_ARCHAR:
			if((*(*(map+msg1->x)+msg1->y) & (DATA_SEG)) == ARCHAR)
			{
				msg1->money += ARCHAR_PRICE;
				*(*(map+msg1->x)+msg1->y) = 0;
			}
			else if(*(*(map+msg1->x)+msg1->y)==0 && (msg1->money >= ARCHAR_PRICE))
			{
				msg1->money -= ARCHAR_PRICE;
				*(*(map+msg1->x)+msg1->y) = (msg1->my_self <<WEIYI)|ARCHAR;
			}
			break;
		case F_KNIGHT:
			if((*(*(map+msg1->x)+msg1->y) & (DATA_SEG)) == KNIGHT)
			{
				msg1->money += KNIGHT_PRICE;
				*(*(map+msg1->x)+msg1->y) = 0;
			}
			else if(*(*(map+msg1->x)+msg1->y)==0 && (msg1->money >= KNIGHT_PRICE))
			{
				msg1->money -= KNIGHT_PRICE;
				*(*(map+msg1->x)+msg1->y) = (msg1->my_self<<WEIYI)|KNIGHT;
			}
			break;
		case F_INFANT:
			if((*(*(map+msg1->x)+msg1->y) & (DATA_SEG)) == INFANT)
			{
				msg1->money += INFANT_PRICE;
				*(*(map+msg1->x)+msg1->y) = 0;
			}
			else if(*(*(map+msg1->x)+msg1->y)==0 && (msg1->money >= INFANT_PRICE))
			{
				msg1->money -= INFANT_PRICE;
				*(*(map+msg1->x)+msg1->y) = (msg1->my_self<<WEIYI)|INFANT;
			}
			break;
		case F_OK:
			msg1->ok = 1;
			break;

	/***********************************************分界线********************************************************/		

		case S_UP:
			if(msg2->x <= 0)
				msg2->x = 0;
			else
				msg2->x--;
			break;
		case S_DOWN:
			if(msg2->x >= (row-1))
				msg2->x = row-1;
			else
				msg2->x++;
			break;
		case S_LEFT:
			if(msg2->y <= col/2+1)
				msg2->y = col/2+1;
			else
				msg2->y--;
			break;
		case S_RIGHT:
			if(msg2->y >= (col-1))
				msg2->y = (col-1);
			else
				msg2->y++;
			break;
		case S_ARCHAR:
			if((*(*(map+msg2->x)+msg2->y) & (DATA_SEG)) == ARCHAR)
			{
				msg2->money += ARCHAR_PRICE;
				*(*(map+msg2->x)+msg2->y) = 0;
			}
			else if(*(*(map+msg2->x)+msg2->y)==0 && (msg2->money >= ARCHAR_PRICE))
			{
				msg2->money -= ARCHAR_PRICE;
				*(*(map+msg2->x)+msg2->y) = (msg2->my_self<<WEIYI)|ARCHAR;
			}
			break;
		case S_KNIGHT:
			if((*(*(map+msg2->x)+msg2->y) & (DATA_SEG)) == KNIGHT)
			{
				msg2->money += KNIGHT_PRICE;
				*(*(map+msg2->x)+msg2->y) = 0;
			}
			else if(*(*(map+msg2->x)+msg2->y)==0 && (msg2->money >= KNIGHT_PRICE))
			{
				msg2->money -= KNIGHT_PRICE;
				*(*(map+msg2->x)+msg2->y) = (msg2->my_self<<WEIYI)|KNIGHT;
			}
			break;

		case S_INFANT:
			if((*(*(map+msg2->x)+msg2->y) & (DATA_SEG)) == INFANT)
			{
				msg2->money += INFANT_PRICE;
				*(*(map+msg2->x)+msg2->y) = 0;
			}
			else if(*(*(map+msg2->x)+msg2->y)==0 && (msg2->money >= INFANT_PRICE))
			{
				msg2->money -= INFANT_PRICE;
				*(*(map+msg2->x)+msg2->y) = (msg2->my_self<<WEIYI)|INFANT;
			}
			break;
		case S_OK:
			msg2->ok = 1;
	}
}


int ** get_map(const int row, const int col)
{
	int i;
	int** map;
	map = (int**)malloc(row*sizeof(int*));
	if(map == NULL)
	{
		printf("malloc map failed!\n");
		exit(0);
	}
	for(i = 0; i < row; i++)
	{
		*(map+i) = (int*)malloc(col*sizeof(int));
		if(*(map+i) == NULL)
		{
			printf("malloc *(map+i) failed!\n");
			exit(0);
		}
	}
	return map;
}
int * get_array(const int length)
{
	int *array = (int *)malloc(sizeof(int)*length);
	if(array == NULL)
	{
		printf("malloc array failed!\n");
		exit(0);
	}
	return array;
}

//功能：复制地图
int** copy_map(int** new_map, int ** map, const int row, const int col)
{	
	int i, j;
	for(i = 0; i < row; i++)
	{
		for(j = 0; j < col; j++)
		{
			*(*(new_map+i)+j) = *(*(map+i)+j);
		}
	}
	return new_map;
}


void free_map(int **map, const int row)
{
	int i;
	for(i = 0; i < row; i++)
	{
		free(*(map+i));
	}
	free(map);
}

void zero_map(int** map, int row, int col)
{
	int i, j;
	for(i = 0; i < row; i++)
	{
		for(j = 0; j < col; j++)
		{
			*(*(map+i)+j) = 0;
		}
	}
}



int num_counts(int ** map, const int row, int col, int num)
{
	int i, j, counts = 0;
	for(i = 0; i < row; i++)
	{
		for(j = 0; j < col; j++)
		{
			if(num == (*(*(map+i)+j)>>WEIYI))
				counts++;
		}
	}
	return counts;
}

int* get_num_all_pos(int** map, const int row, const int col, int num, int* array)
{
	int i, j, counts = 0;
	for(i = 0; i < row; i++)
	{
		for(j = 0; j < col; j++)
		{
			if(num == (*(*(map+i)+j)>>WEIYI))
			{
				*(array+counts) = i*col+j;
				counts++;
			}
		}
	}
	return array;
}


