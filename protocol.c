#include<termios.h>
#include"stdio.h"
#include"protocol.h"

char get_opt()
{
	char str[4];
	int i;
	//设置缓冲区大小一个字符,即时读取字符消息
	struct termios new_settings;
	struct termios old_settings;
	//获得终端的设置
	tcgetattr(0,&old_settings);
	//修改设置
	new_settings = old_settings;
	new_settings.c_lflag &= (~ICANON);
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	//再次获得新的设置
	tcgetattr(0,&old_settings);
	//设置自定义的属性
	tcsetattr(0,TCSANOW,&new_settings);
	for(i = 0; i < 3; i++)
	{
		str[i] = getchar();
		switch(str[i])
		{
			case F_UP:
			case F_LEFT:
			case F_RIGHT:
			case F_DOWN:
			case F_ARCHAR:
			case F_KNIGHT:
			case F_INFANT:
			case F_OK:
			case S_UP:
			case S_DOWN:
			case S_LEFT:
			case S_RIGHT:
			case S_ARCHAR:
			case S_KNIGHT:
			case S_INFANT:
			case S_OK:
				tcsetattr(0,TCSANOW,&old_settings);
				return str[i];
		}
		if(str[0] == 27)
		{
			continue;
		}
		else
		{
			i = -1;
		}
	}
	//使用结束，设置回原来的属性
	tcsetattr(0,TCSANOW,&old_settings);
	return screen_str(str);
}
char screen_str(char* str)
{
	if(str[0] == 27)
	{
		if(str[1] == 91)
		{
			switch(str[2])
			{
				case 65:
					return S_UP;
				case 66:
					return S_DOWN;
				case 67:
					return S_RIGHT;
				case 68:
					return S_LEFT;
			}
		}
	}
	return -1;
}


