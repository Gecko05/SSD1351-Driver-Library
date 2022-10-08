CC = gcc
SRC_DIR = ../src
HAL_DIR = ../example
CFLAGS = -Wextra -g -I$(SRC_DIR) -I.
INCLUDE = -I/../example
DEPS = $(SRC_DIR)/ssd1351.h $(SRC_DIR)/fonts.h $(SRC_DIR)/sprites.h $(SRC_DIR)/color_palette.h $(HAL_DIR)/myHAL.h
OBJS = $(SRC_DIR)/ssd1351.o $(SRC_DIR)/color_palette.o $(SRC_DIR)/fonts.o $(SRC_DIR)/sprites.o $(HAL_DIR)/myHAL.o

all: main

main: main.o $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -o main main.o $(OBJS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(HAL_DIR)/%.o: $(HAL_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm *.o main