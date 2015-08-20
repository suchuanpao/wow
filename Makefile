#sample makefile script
CFLAGS = -Wall -o2 -ggdb
LFLAGS = -lm -lpthread
CC = gcc
SRCS = main.c show_map.c int_map.c game.c protocol.c run.c data_structure.c
EXEC = test
all:
	$(CC) $(CFLAGS) $(SRCS) -o $(EXEC) $(LFLAGS)
clean:
	rm -rf $(EXEC)
