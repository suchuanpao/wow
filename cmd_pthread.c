#include "protocol.h"
#include "cmd_pthread.h"

#define map msg->map
#define col msg->col
#define row msg->row

void pthread_hero_cmd(struct Msg * msg)
{
	char opt;
	while(*(msg->ok))
	{
		opt = get_opt();
		if(msg->player1 == (*(*(map+*(msg->x))+*(msg->y))>>WEIYI))
		{
			switch(opt)
			{
				case F_UP:
					if(*(msg->x) <= 0)
					{
						*(msg->x) = 0;
					}
					else if(*(*(map+*(msg->x)-1)+*(msg->y)) == NONE)
					{
						*(*(map+*(msg->x))+*(msg->y)) = NONE;
						*(msg->x)--;
					}
					break;
				case F_LEFT:
					if(*(msg->y) <= 0)
					{
						*(msg->y) = 0;
					}
					else if(*(*(map+*(msg->x))+*(msg->y)-1) == NONE)
					{
						*(*(map+*(msg->x))+*(msg->y)) = NONE;
						*(msg->y)--;
					}
					break;
				case F_RIGHT:
					if(*(msg->y) >= col/2-1)
					{
						*(msg->y) = col/2-1;
					}
					else if(*(*(map+*(msg->x))+*(msg->y)+1) == NONE)
					{
						*(*(map+*(msg->x))+*(msg->y)) = NONE;
						*(msg->y)++;
					}
					break;
				case F_DOWN:
					if(*(msg->x) >= (row-1))
					{
						*(msg->x) = row-1;
					}
					else if(*(*(map+*(msg->x)+1)+*(msg->y)) == NONE)
					{
						*(*(map+*(msg->x))+*(msg->y)) = NONE;
						*(msg->x)++;
					}
					break;
			}
			*(*(map+*(msg->x))+*(msg->y)) = ((msg->player1<<WEIYI)|HERO);
		}
		else if(msg->player2 == (*(*(map+*(msg->i))+*(msg->j)) >> WEIYI))
		{
			switch(opt)
			{
				case S_UP:
					if(*(msg->i) <= 0)
					{
						*(msg->i) = 0;
					}
					else if(*(*(map+*(msg->i)-1)+*(msg->j)) == NONE)
					{
						*(*(map+*(msg->i))+*(msg->j)) = NONE;
						*(msg->i)--;
					}

					break;
				case S_LEFT:
					if(*(msg->j) <= 0)
					{
						*(msg->j) = 0;
					}
					else if(*(*(map+*(msg->i))+*(msg->j)-1) == NONE)
					{
						*(*(map+*(msg->i))+*(msg->j)) = NONE;
						*(msg->j)--;
					}
					break;
				case S_RIGHT:
					if(*(msg->j) >= col/2-1)
					{
						*(msg->j) = col/2-1;
					}
					else if(*(*(map+*(msg->i))+*(msg->j)+1) == NONE)
					{
						*(*(map+*(msg->i))+*(msg->j)) = NONE;
						*(msg->j)++;
					}
					break;
				case S_DOWN:
					if(*(msg->i) >= (row-1))
					{
						*(msg->i) = row-1;
					}
					else if(*(*(map+*(msg->i)+1)+*(msg->j)) == NONE)
					{
						*(*(map+*(msg->i))+*(msg->j)) = NONE;
						*(msg->i)++;
					}
					break;
			}
			*(*(map+*(msg->i))+*(msg->j)) = ((msg->player2<<WEIYI)|HERO);
		}
	}
}

