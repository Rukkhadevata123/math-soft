#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

// 定义全局变量
extern int **world;
extern int WIDTH;
extern int HEIGHT;

// 函数原型
void initialize(int width, int height, float live_cell_ratio);
void update();
void print_world();
void delay(int milliseconds);
void save_to_bmp(const char *filename);

#endif