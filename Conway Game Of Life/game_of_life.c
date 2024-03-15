#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include "game_of_life.h"

// 定义全局变量
int **world;
int WIDTH;
int HEIGHT;

#pragma pack(push, 1)
typedef struct {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BITMAPINFOHEADER;
#pragma pack(pop)

void save_to_bmp(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("无法打开文件 %s\n", filename);
        return;
    }

    BITMAPFILEHEADER fileHeader = {0x4D42, 0, 0, 0, 54};
    BITMAPINFOHEADER infoHeader = {40, WIDTH, HEIGHT, 1, 24, 0, 0, 0, 0, 0, 0};

    fileHeader.bfSize = 54 + WIDTH * HEIGHT * 3;
    infoHeader.biSizeImage = WIDTH * HEIGHT * 3;

    fwrite(&fileHeader, sizeof(fileHeader), 1, file);
    fwrite(&infoHeader, sizeof(infoHeader), 1, file);

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            uint8_t color = world[i][j] ? 0 : 255;
            fwrite(&color, 1, 1, file); // Blue
            fwrite(&color, 1, 1, file); // Green
            fwrite(&color, 1, 1, file); // Red
        }
    }

    fclose(file);
}

// 初始化格子世界的状态
void initialize(int width, int height, float live_cell_ratio)
{
    WIDTH = width;
    HEIGHT = height;

    // 使用calloc分配内存并自动初始化为0
    world = (int **)calloc(HEIGHT, sizeof(int *));
    for (int i = 0; i < HEIGHT; i++)
    {
        world[i] = (int *)calloc(WIDTH, sizeof(int));
    }

    // 随机选择一些细胞设置为活细胞
    srand(time(NULL));                                     // 初始化随机数生成器
    int num_live_cells = HEIGHT * WIDTH * live_cell_ratio; // 使用用户指定的存活率
    for (int i = 0; i < num_live_cells; i++)
    {
        int x = rand() % HEIGHT;
        int y = rand() % WIDTH;
        world[x][y] = 1;
    }
}

// 输出格子世界的状态
void print_world()
{
    // 清除屏幕
    system("clear"); // 对于Linux和Mac系统
    // system("cls"); // 对于Windows系统

    // 输出上边框
    for (int i = 0; i < 2 * WIDTH + 2; i++)
    {
        printf("-");
    }
    printf("\n");

    // 遍历每一个细胞，将其状态输出到控制台
    for (int i = 0; i < HEIGHT; i++)
    {
        printf("|"); // 输出左边框
        for (int j = 0; j < WIDTH; j++)
        {
            printf("%c%c", world[i][j] ? '*' : ' ', world[i][j] ? '*' : ' ');
        }
        printf("|\n"); // 输出右边框
    }

    // 输出下边框
    for (int i = 0; i < 2 * WIDTH + 2; i++)
    {
        printf("-");
    }
    printf("\n");

    printf("提示：按下 s 键可以保存当前画布为 game_of_life.bmp\n");
    printf("提示：按下 Ctrl+C 可以退出程序\n");
}

// 根据游戏规则更新格子世界的状态
void update()
{
    int new_world[HEIGHT][WIDTH];

    // 遍历每一个细胞
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            // 计算细胞的邻居数量
            int neighbors = 0;
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    if (di == 0 && dj == 0)
                        continue;
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < HEIGHT && nj >= 0 && nj < WIDTH && world[ni][nj])
                    {
                        neighbors++;
                    }
                }
            }

            // 根据生命游戏的规则更新细胞的状态
            if (world[i][j] && (neighbors == 2 || neighbors == 3))
            {
                new_world[i][j] = 1;
            }
            else if (!world[i][j] && neighbors == 3)
            {
                new_world[i][j] = 1;
            }
            else
            {
                new_world[i][j] = 0;
            }
        }
    }

    // 将新的状态复制到原来的数组中
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            world[i][j] = new_world[i][j];
        }
    }
}
void delay(int milliseconds)
{
    usleep(milliseconds * 1000);
}