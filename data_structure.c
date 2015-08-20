#include<stdlib.h>
#include"data_structure.h"

/***********************私有成员变量********************/


//队列链表的头和尾
static struct Queue * head = NULL;
static struct Queue * tail = NULL;
//节点数量
static int node_counts = 0;
//节点最大长度
static int QUEUEMAX = 1000;



/*****************************************单向链表,队列存放*******************************************/

void free_queue()
{
	struct Queue * tmp;
	if(!is_queue_empty())
	{
		while(head == NULL)
		{
			tmp = head;
			head = head->Node;
			free(tmp);
		}
	}
	//节点数清零
	node_counts = 0;
	//尾节点清零 
	tail = NULL;
}

struct Queue * in_queue()
{
	struct Queue * tmp;
	tmp = (struct Queue *)malloc(sizeof(struct Queue));
	if(tmp == NULL)
	{
		return NULL;
	}
	tmp->Node = NULL;
	//头节点为空或者尾节点为空时,说明链表无节点
	if(NULL == tail || head == NULL)
	{
		tail = tmp;
		head = tmp;
	}
	else
	{
		tail->Node = tmp;
		tail = tail->Node;
	}
	//节点数+1
	node_counts++;
	//返回尾节点的指针供外部赋值
	return tail;
}

int de_queue()
{
	if(is_queue_empty())
	{
		return QUE_IS_EMPTY;
	}
	int content = head->pos;
	//删除表头,head指向下一个节点
	struct Queue * tmp = head;
	head = head->Node;
	free(tmp);
	tmp = NULL;

	//节点数-1
	node_counts--;
	//每次删完判断头节点是否为NULL,是则令尾节点=NULL;
	if(head == NULL)
	{
		tail = NULL;
	}
	return content;
}

struct Queue * get_queue_head()
{
	return head;
}
struct Queue * get_queue_tail()
{
	return tail;
}
int is_queue_empty()
{
	return (node_counts == 0?1:0);
}

int is_queue_full()
{
	return (node_counts < QUEUEMAX?0:1);
}



/*****************************************单向链表,栈存放*******************************************/


