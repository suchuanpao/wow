#ifndef __GAME_H_
#define __GAME_H_

#define A_S_X					A_soldier->x
#define A_S_Y					A_soldier->y
#define B_S_X					B_soldier->x
#define B_S_Y					B_soldier->y

//功能：对所有士兵进行全排列,距离x,y远的排前面
void rank_soldier(struct Soldier ** head, int x, int y);
int soldier_cmp(struct Soldier *soldier1, struct Soldier *soldier2, int x, int y);

//功能：将对手的表头与己方表头的指针传入，让双方进行战斗一回合
void fights(struct Soldier * head1, struct Soldier * head2);
//功能：传入A,B两个,让A士兵攻击B士兵,如果攻击成功返回1,否则返回0
int fight(struct Soldier * A_soldier, struct Soldier * B_soldier );



//功能：将要添加的士兵类型和数量以及链表头地址传入,自动添加一定数量的士兵,返回表头
struct Soldier * add_soldiers(struct Soldier ** phead,int**map,int col, int counts, int * pos_array);
//功能：将表头地址传入,删除死亡士兵,并返回表头
struct Soldier * del_dead_soldier(struct Soldier ** phead, int** map);



//功能：将交换两个节点,分别传入这两个节点的指针
struct Soldier * exc_soldier(struct Soldier ** soldier1,struct Soldier ** soldier2);


//功能：将表头地址传入,添加新结构体到表头,返回头指针
struct Soldier * add_soldier(struct Soldier ** phead);
//功能：将被删除表的结构体指针地址传入,返回被删除节点的下一节点地址
struct Soldier * del_soldier(struct Soldier ** psoldier);
//功能：输出所有结构体内容
void print_soldiers(struct Soldier * head1,struct Soldier * head2);
//功能：删除所有的士兵
void del_all_soldier(struct Soldier ** head);

//附上弓兵属性
struct Soldier * become_ARCHAR(struct Soldier * soldier);
//附上骑士属性
struct Soldier * become_KNIGHT(struct Soldier * soldier);
//附上步兵属性
struct Soldier * become_INFANT(struct Soldier * soldier);
//附上塔属性
struct Soldier * become_BAT(struct Soldier * soldier);
//附上英雄属性
struct Soldier * become_HERO(struct Soldier * soldier);


#endif
