#ifndef __SHOW_COLOR_TABLE_H__
#define __SHOW_COLOR_TABLE_H__

#define p1 " "
#define p2 "  "
#define p3 "   "
#define p4 "    "
#define p5 "     "
#define p6 "      "
#define p8 "        "
#define UNDO_WIDTH 2
#define VERTICAL()          printf("\033[31;1m|\033[0m")
#define ADD()				printf("\033[31;1m+\033[0m")
#define SUB()				printf("\033[31;1m-\033[0m")

#define ZERO_SPACE()		printf("%s",p2)
#define WORD_RED(val)		printf("\033[31;1m%2d\033[0m", val)
#define WORD_GREEN(val)		printf("\033[32;1m%2d\033[0m", val)
#define WORD_YELLOW(val)	printf("\033[33;1m%2d\033[0m", val)
#define WORD_BLUE(val)		printf("\033[34;1m%2d\033[0m", val)
#define WORD_PURPLE(val)	printf("\033[35;1m%2d\033[0m", val)
#define WORD_DEEPGREEN(val)	printf("\033[36;1m%2d\033[0m", val)

#define FLICKER_SPACE()			printf("\033[40;1m%s\033[0m",p2)
#define FLICKER_RED(val)		printf("\033[41;30;1m%2d\033[0m",val)
#define FLICKER_GREEN(val)		printf("\033[42;30;1m%2d\033[0m",val)
#define FLICKER_YELLOW(val)		printf("\033[43;30;1m%2d\033[0m",val)
#define FLICKER_BLUE(val)		printf("\033[44;30;1m%2d\033[0m",val)
#define FLICKER_PURPLE(val)		printf("\033[45;30;1m%2d\033[0m",val)
#define FLICKER_DEEPGREEN(val)	printf("\033[46;30;1m%2d\033[0m",val)
#define FLICKER_ARCHAR()		printf("\033[36;41;1m%2s\033[0m","弓")
#define FLICKER_KNIGHT()		printf("\033[32;44;1m%2s\033[0m","骑")
#define FLICKER_INFANT()		printf("\033[34;43;1m%2s\033[0m","步")
#define FLICKER_BAT()			printf("\033[32;41;1m%2s\033[0m","炮")

#define RED_SPACE()			printf("\033[31;42;1m%s\033[0m",p2)
#define GREEN_SPACE()		printf("\033[35;46;1m%s\033[0m",p2)
#define YELLOW_SPACE()		printf("\033[34;43;1m%s\033[0m",p2)
#define BLUE_SPACE()		printf("\033[33;44;1m%s\033[0m",p2)
#define PURPLE_SPACE()		printf("\033[35;45;1m%s\033[0m",p2)
#define DEEPGREEN_SPACE()	printf("\033[36;41;1m%s\033[0m",p2)

#define P_ARCHAR1()		printf("\033[31;46;1m%2s\033[0m","弓")
#define P_KNIGHT1()		printf("\033[32;45;1m%2s\033[0m","骑")
#define P_INFANT1()		printf("\033[33;44;1m%2s\033[0m","步")
#define P_ARCHAR2()		printf("\033[34;43;1m%2s\033[0m","弓")
#define P_KNIGHT2()		printf("\033[35;42;1m%2s\033[0m","骑")
#define P_INFANT2()		printf("\033[36;41;1m%2s\033[0m","步")

#define P_BAT1()		printf("\033[32;43;1m%2s\033[0m","炮")
#define P_BAT2()		printf("\033[33;44;1m%2s\033[0m","炮")


//输出彩色数字
void print_number(int val, int self1, int self2);
//输出反彩的颜色
int print_flick(int val);
//控制台显示地图
void c_show_map(int **map,int row, int col, struct PL_Msg * msg1, struct PL_Msg * msg2);

#endif
