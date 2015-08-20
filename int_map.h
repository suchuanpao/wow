#ifndef __INT_MAP_H_
#define __INT_MAP_H_

//功能：基于魔兽世界的操作地图,参数是map,row,col以及两个光标的地址结合的结构体
void control_map(int ** map, int row, int col, struct PL_Msg* msg1, struct PL_Msg * msg2, char opt);


//功能：初始化一个行数为row,列数为col的map,返回首地址
int ** get_map(const int row, const int col);
int * get_array(const int length);
//功能：复制地图
int** copy_map(int** new_map, int **map, const int row, const int col);

//功能：释放地图所占内存大小
void free_map(int **map, const int row);

//功能：将map中内容初始化为0
void zero_map(int** map, int row, int col);

//功能：获得map中某个数的存在的数量
int num_counts(int ** map, int row, int col, int num);

//功能：将map中大小等于一个特定值的位置全部放入到一维array中
int* get_num_all_pos(int** map, const int row, const int col, int num, int* array);

#endif
