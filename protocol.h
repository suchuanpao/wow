#ifndef __PROTOCOL_H_
#define __PROTOCOL_H_

/********************************宏定义****************************/

#define ARCHAR		0x02
#define KNIGHT		0x04
#define INFANT		0x08
#define HERO		0X10
#define BAT			0x20

#define DATA_SEG	0x0000003F
#define WEIYI		6

#define ARCHAR_PRICE 200
#define KNIGHT_PRICE 500
#define INFANT_PRICE 300
/*******************************run.c用到的所有宏定义************/

#define NONE		0
#define FLAG_NONE	1

#define NO_DIR		5 
#define UP			1
#define DOWN		2
#define LEFT		3
#define RIGHT		4

/**************************************int_map.c与protocol.h所有宏定义*******************/
//玩家1的上下左右,放置士兵以及确认
#define F_UP		'w'
#define F_LEFT		'a'
#define F_RIGHT		'd'
#define F_DOWN		's'
#define F_ARCHAR	'u'
#define F_KNIGHT	'i'
#define F_INFANT	'o'
#define F_OK		'y'

//玩家2的上下左右
#define S_UP		';'
#define S_DOWN		'.'
#define S_LEFT		','
#define S_RIGHT		'/'
#define S_ARCHAR	'b'
#define S_KNIGHT	'n'
#define S_INFANT	'm'
#define S_OK		'v'

#define QUIT		'q'
/********************************game.c用到的战斗初始值定义****************************/

//战斗状态
#define FIGHTING		1
#define RUNNING			0
//战斗天赋触发几率
#define DODGE_LUCK		10
#define CRI_LUCK		5
#define COUNTER_LUCK	5
//属性相克,伤害加成
#define DAMAGE			0.3
//攻击力
#define KNIGHT_ATK		150
#define	INFANT_ATK		100
#define	ARCHAR_ATK		100
//血量
#define KNIGHT_HP		1000
#define	INFANT_HP		800
#define	ARCHAR_HP		500
//防御力
#define	KNIGHT_DEF		50
#define	INFANT_DEF		50
#define	ARCHAR_DEF		50
//攻击范围
#define KNIGHT_RANGE	2
#define	INFANT_RANGE	3
#define	ARCHAR_RANGE	6
//天赋
#define CRI				5
#define COUNTER			6
#define DODGE			10
//士兵名称
#define Archar			"弓箭手"
#define Knight			"骑士"
#define Infant			"步兵"

//炮台的各项属性
#define BAT_ATK			200
#define BAT_DEF			50
#define BAT_HP			2000
#define BAT_RANGE		6
#define BAT_NAME		"炮台"
//英雄的各项属性
#define HERO_ATK		200
#define HERO_DEF		50
#define HERO_HP			2000
#define HERO_RANGE		6
#define HERO_NAME		"英雄"


/**********************************类型定义****************************/
struct Soldier
{
	//1.士兵类别
	int soldier_type;
	//2.攻击
	int ATK;
	//3.防御
	int DEF;
	//4.气血
	int HP;
	//5.克制士兵类别
	int control_object;
	//6.天赋
	int talent;
	//7.幸运值
	int luck;
	//8.射程
	float range;
	//9.位置x
	int x;
	//10.位置y
	int y;
	//11.战斗状态
	int state;
	//12.结构体指针
	struct Soldier * next;
	struct Soldier * last;
	char name[20];
};

struct PL_Msg
{
	int my_self;
	int aim;
	int x;
	int y;
	int money;
	int ok;
	struct Soldier * head;
};

struct Msg
{
	int *x;
	int *y;
	int *i;
	int *j;
	int player1;
	int player2;
	int ** map;
	int col;
	int row;
	int *ok;
};

/********************************接口定义****************************/
char get_opt();
char screen_str(char* str);

#endif

