#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "protocol.h"
#include"game.h"

//功能：对所有士兵进行全排列,距离x,y远的排前面
void rank_soldier(struct Soldier ** head, int x, int y)
{
	if(*head == NULL)
		return ;
	struct Soldier * r_max = NULL;
	struct Soldier * tmp;
	while((*head)->next != r_max)
	{
		if(soldier_cmp(*head,( (*head)->next ),x,y))
		{
			exc_soldier(head,&((*head)->next));
		}
		tmp = *head;
		while(tmp->next->next != r_max)
		{
			if(soldier_cmp((tmp->next),(tmp->next->next),x,y))
			{
				exc_soldier(&(tmp->next),&(tmp->next->next));
			}
			tmp = tmp->next;
		}
		r_max = tmp->next;
	}
	return ;
}
int soldier_cmp(struct Soldier *soldier1, struct Soldier *soldier2, int x, int y)
{
	if(abs(soldier1->x-x) < abs(soldier2->x-x))
	{
		return 1;
	}
	else if(abs(soldier1->x-x) == abs(soldier2->x-x))
	{
		if(abs(soldier1->y-y) < abs(soldier2->y-y))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}


//A阵营打B阵营
void fights(struct Soldier * self_head, struct Soldier * aim_head)
{
	struct Soldier * tmp = aim_head;
	while(self_head != NULL)
	{
		while(tmp != NULL)
		{
			if(fight(self_head,tmp))
			{
				break;
			}
			tmp = tmp->next;
		}
		tmp = aim_head;
		self_head = self_head->next;
	}
}

int fight(struct Soldier * A_soldier, struct Soldier * B_soldier )
{
	int hurt = 0;
	srand((unsigned)time(NULL));
	if(A_soldier->range < sqrt(pow((double)(A_S_X-B_S_X),2) + pow((double)(A_S_Y-B_S_Y),2)))
	{
		A_soldier->state = RUNNING;
		return 0;
	}
	else if(B_soldier->HP <= 0)
	{
		return 0;
	}
	else
	{
		//进入战斗模式不会行走
		A_soldier->state = FIGHTING;
		//攻击前判定A是否克制B,获得攻击伤害加成
		hurt = (A_soldier->ATK - B_soldier->DEF);
		if(A_soldier->control_object == B_soldier->soldier_type)
		{
			//攻击减防御乘以属性相克伤害加成
			hurt = hurt*(1+DAMAGE);

		}
		//判断A的天赋属性是否生效,暴击则伤害加倍
		if(A_soldier->luck >= (rand() % 100 + 1))
		{
			switch(A_soldier->talent)
			{
				case CRI:
					hurt *= 2;
					break;
				case DODGE:
				case COUNTER:
					break;
				default:
					break;
			}

		}
		/*判断B的天赋属性是否生效,闪避则直接return 1,回合结束.反击则对A造成B攻击力的百分之五十伤害*/
		if(B_soldier->luck >= (rand() % 100 +1))
		{
			switch(B_soldier->talent)
			{
				case CRI:
					break;
				case COUNTER:
					A_soldier->HP -= (B_soldier->ATK - A_soldier->DEF)/2;
					break;
				case DODGE:

					return 1;
				default:
					break;
			}
		}
		B_soldier->HP -= hurt;
	}
	return 1;
}

struct Soldier * add_soldiers(struct Soldier ** phead,int**map, int col, int counts, int * pos_array)
{
	int i;
	for(i = 0; i < counts; i++)
	{
		add_soldier(phead);
		(*phead)->x = *(pos_array+i)/col;
		(*phead)->y = *(pos_array+i)%col;
		switch(*(*(map+(*phead)->x)+(*phead)->y)&(DATA_SEG))
		{
			case ARCHAR:
				become_ARCHAR(*phead);
				break;
			case KNIGHT:
				become_KNIGHT(*phead);
				break;
			case INFANT:
				become_INFANT(*phead);
				break;
			case BAT:
				become_BAT(*phead);
				break;
			case HERO:
				become_HERO(*phead);
				break;
		}
	}
	return *phead;
}
struct Soldier * del_dead_soldier(struct Soldier ** phead, int **map)
{
	struct Soldier * tmp;
	//头节HP小于0就一直删除
	while(*phead && ((*phead)->HP <= 0))
	{
		*(*(map+(*phead)->x)+(*phead)->y) = 0;
		//可返回可不返回
		*phead = del_soldier(phead);
	}
	if((*phead) == NULL)
	{
		return NULL;
	}
	tmp = *phead;
	//删除头节点一下的HP小于0的节点
	while(tmp->next != NULL)
	{
		if(tmp->next->HP <=0)
		{
			*(*(map+tmp->next->x)+tmp->next->y) = 0;
			//可返回可不返回
			tmp->next = del_soldier(&(tmp->next));
		}
		else
		{
			tmp = tmp->next;
		}
 	}
	return *phead;
}

struct Soldier *  exc_soldier(struct Soldier ** soldier1,struct Soldier ** soldier2)
{
	struct Soldier * tmp;
	tmp = *soldier1;
	*soldier1 = *soldier2;
	*soldier2 = tmp;
	tmp = (*soldier1)->next;
	(*soldier1)->next = (*soldier2)->next;
	(*soldier2)->next = tmp;
	return *soldier1;
}

struct Soldier * add_soldier(struct Soldier ** phead)
{
	struct Soldier *temp;
	temp = (struct Soldier *)malloc(sizeof(struct Soldier));
	temp -> next = *phead;
	*phead = temp;
	temp = NULL;
	return *phead;
}

struct Soldier * del_soldier(struct Soldier ** psoldier)
{
	struct Soldier * tmp;
	tmp = *psoldier;
	*psoldier = (*psoldier)->next;
	free(tmp);
	tmp = NULL;
	return *psoldier;
}

void print_soldiers(struct Soldier * head1,struct Soldier * head2)
{
	if(head1 == NULL || head2 == NULL)
		return ;
	printf("Player1:\t\t\t\t\tPlayer2:\n");
	while(head1 != NULL && head2 != NULL)
	{
		printf("类型:%s,ATK =%d,DEF=%d,HP=%d\t\t",head1->name,head1->ATK,head1->DEF,head1->HP);
		printf("类型:%s,ATK =%d,DEF=%d,HP=%d\n",head2->name,head2->ATK,head2->DEF,head2->HP);
		head1 = head1->next;
		head2 = head2->next;
	}
	if(head1 == NULL && head2)
	{
		while(head2 != NULL)
		{
			printf("\t\t\t\t\t\t类型:%s,ATK =%d,DEF=%d,HP=%d\n",head2->name,head2->ATK,head2->DEF,head2->HP);
			head2 = head2->next;
		}
	}
	if(head2 == NULL && head1)
	{
		while(head1 != NULL)
		{
			printf("类型:%s,ATK =%d,DEF=%d,HP=%d\n",head1->name,head1->ATK,head1->DEF,head1->HP);
			head1 = head1->next;
		}
	}

}

void del_all_soldier(struct Soldier ** head)
{
	struct Soldier *tmp;
	while((*head) != NULL)
	{
		tmp = (*head);
		*head = (*head)->next;
		free(tmp);
	}
	tmp = NULL;
}



struct Soldier * become_ARCHAR(struct Soldier * soldier)
{
	soldier -> soldier_type = ARCHAR;
	soldier -> ATK = ARCHAR_ATK;
	soldier -> DEF = ARCHAR_DEF;
	soldier -> HP =ARCHAR_HP;
	soldier -> control_object = KNIGHT;
	soldier -> talent = CRI;
	soldier -> luck = CRI_LUCK;
	soldier -> range = ARCHAR_RANGE;
	strcpy(soldier->name,Archar);
	return soldier;
}
struct Soldier * become_KNIGHT(struct Soldier * soldier)
{
	soldier -> soldier_type = KNIGHT;
	soldier -> ATK = KNIGHT_ATK;
	soldier -> DEF = KNIGHT_DEF;
	soldier -> HP =KNIGHT_HP;
	soldier -> control_object = INFANT;
	soldier -> talent = DODGE;
	soldier -> luck = DODGE_LUCK;
	soldier -> range = KNIGHT_RANGE;
	strcpy(soldier->name,Knight);
	return soldier;
}
struct Soldier * become_INFANT(struct Soldier * soldier)
{
	soldier -> soldier_type = INFANT;
	soldier -> ATK = INFANT_ATK;
	soldier -> DEF = INFANT_DEF;
	soldier -> HP = INFANT_HP;
	soldier -> control_object = ARCHAR;
	soldier -> talent = COUNTER;
	soldier -> luck = COUNTER_LUCK;
	soldier -> range = INFANT_RANGE;
	strcpy(soldier->name,Infant);
	return soldier;
}
struct Soldier * become_BAT(struct Soldier * soldier)
{
	soldier -> soldier_type = BAT;
	soldier -> ATK = BAT_ATK;
	soldier -> DEF = BAT_DEF;
	soldier -> HP = BAT_HP;
	soldier -> control_object = NONE;
	soldier -> talent = NONE;
	soldier -> luck = NONE;
	soldier -> range = BAT_RANGE;
	soldier -> state = FIGHTING;
	strcpy(soldier->name,BAT_NAME);
	return soldier;
}
struct Soldier * become_HERO(struct Soldier * soldier)
{
	soldier -> soldier_type = HERO;
	soldier -> ATK = HERO_ATK;
	soldier -> DEF = HERO_DEF;
	soldier -> HP = HERO_HP;
	soldier -> control_object = NONE;
	soldier -> talent = NONE;
	soldier -> luck = NONE;
	soldier -> range = HERO_RANGE;
	soldier -> state = FIGHTING;
	strcpy(soldier->name,HERO_NAME);
	return soldier;
}



