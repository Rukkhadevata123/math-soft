#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include "game_of_life.h"
#include "game_of_life.c"

int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

// 初始化特定模式
void initialize_pattern(const char *pattern_name)
{
    if (strcmp(pattern_name, "Bee-hive") == 0)
    {
        // 初始化Bee-hive模式
        // Bee-hive模式是一个6个细胞的模式，所以我们需要确保世界的宽度和高度至少为3
        if (WIDTH < 3 || HEIGHT < 3)
        {
            printf("世界太小，无法初始化Bee-hive模式\n");
            return;
        }

        // Bee-hive模式的中心位置
        int center_x = HEIGHT / 2;
        int center_y = WIDTH / 2;

        // 设置Bee-hive模式的细胞
        world[center_x - 1][center_y] = 1;
        world[center_x - 1][center_y + 1] = 1;
        world[center_x][center_y - 1] = 1;
        world[center_x][center_y + 2] = 1;
        world[center_x + 1][center_y] = 1;
        world[center_x + 1][center_y + 1] = 1;
    }
    if (strcmp(pattern_name, "Beacon") == 0)
    {
        // 初始化Beacon模式
        // Beacon模式是一个4x4的模式，所以我们需要确保世界的宽度和高度至少为4
        if (WIDTH < 4 || HEIGHT < 4)
        {
            printf("世界太小，无法初始化Beacon模式\n");
            return;
        }

        // Beacon模式的中心位置
        int center_x = HEIGHT / 2;
        int center_y = WIDTH / 2;

        // 设置Beacon模式的细胞
        world[center_x - 1][center_y - 1] = 1;
        world[center_x - 1][center_y - 2] = 1;
        world[center_x - 2][center_y - 1] = 1;
        world[center_x - 2][center_y - 2] = 1;
        world[center_x + 0][center_y + 0] = 1;
        world[center_x + 0][center_y + 1] = 1;
        world[center_x + 1][center_y + 0] = 1;
        world[center_x + 1][center_y + 1] = 1;
    }
    if (strcmp(pattern_name, "Glider") == 0)
    {
        // 初始化Glider模式
        // Glider模式是一个3x3的模式，所以我们需要确保世界的宽度和高度至少为3
        if (WIDTH < 3 || HEIGHT < 3)
        {
            printf("世界太小，无法初始化Glider模式\n");
            return;
        }

        // Glider模式的中心位置
        int center_x = HEIGHT / 2;
        int center_y = WIDTH / 2;

        // 设置Glider模式的细胞
        world[center_x - 1][center_y] = 1;
        world[center_x][center_y + 1] = 1;
        world[center_x + 1][center_y - 1] = 1;
        world[center_x + 1][center_y] = 1;
        world[center_x + 1][center_y + 1] = 1;
    }
    if (strcmp(pattern_name, "Block") == 0)
    {
        // 初始化Block模式
        // Block模式是一个2x2的模式，所以我们需要确保世界的宽度和高度至少为2
        if (WIDTH < 2 || HEIGHT < 2)
        {
            printf("世界太小，无法初始化Block模式\n");
            return;
        }

        // Block模式的中心位置
        int center_x = HEIGHT / 2;
        int center_y = WIDTH / 2;

        // 设置Block模式的细胞
        world[center_x - 1][center_y - 1] = 1;
        world[center_x - 1][center_y] = 1;
        world[center_x][center_y - 1] = 1;
        world[center_x][center_y] = 1;
    }
    if (strcmp(pattern_name, "Loaf") == 0)
    {
        // 初始化Loaf模式
        // Loaf模式是一个4x4的模式，所以我们需要确保世界的宽度和高度至少为4
        if (WIDTH < 4 || HEIGHT < 4)
        {
            printf("世界太小，无法初始化Loaf模式\n");
            return;
        }

        // Loaf模式的中心位置
        int center_x = HEIGHT / 2;
        int center_y = WIDTH / 2;

        // 设置Loaf模式的细胞
        world[center_x - 1][center_y - 1] = 1;
        world[center_x - 1][center_y] = 1;
        world[center_x][center_y - 2] = 1;
        world[center_x][center_y - 1] = 1;
        world[center_x + 1][center_y - 1] = 1;
        world[center_x + 1][center_y] = 1;
        world[center_x + 2][center_y - 1] = 1;
    }
    if (strcmp(pattern_name, "Boat") == 0)
    {
        // 初始化Boat模式
        // Boat模式是一个3x3的模式，所以我们需要确保世界的宽度和高度至少为3
        if (WIDTH < 3 || HEIGHT < 3)
        {
            printf("世界太小，无法初始化Boat模式\n");
            return;
        }

        // Boat模式的中心位置
        int center_x = HEIGHT / 2;
        int center_y = WIDTH / 2;

        // 设置Boat模式的细胞
        world[center_x - 1][center_y - 1] = 1;
        world[center_x - 1][center_y] = 1;
        world[center_x][center_y - 1] = 1;
        world[center_x][center_y + 1] = 1;
        world[center_x + 1][center_y] = 1;
    }
    if (strcmp(pattern_name, "Tub") == 0)
    {
        // 初始化Tub模式
        // Tub模式是一个3x3的模式，所以我们需要确保世界的宽度和高度至少为3
        if (WIDTH < 3 || HEIGHT < 3)
        {
            printf("世界太小，无法初始化Tub模式\n");
            return;
        }

        // Tub模式的中心位置
        int center_x = HEIGHT / 2;
        int center_y = WIDTH / 2;

        // 设置Tub模式的细胞
        world[center_x - 1][center_y] = 1;
        world[center_x][center_y - 1] = 1;
        world[center_x][center_y + 1] = 1;
        world[center_x + 1][center_y] = 1;
    }
    if (strcmp(pattern_name, "Blinker") == 0)
    {
        // 初始化Blinker模式
        // Blinker模式是一个3x1的模式，所以我们需要确保世界的宽度至少为3
        if (WIDTH < 3)
        {
            printf("世界太小，无法初始化Blinker模式\n");
            return;
        }

        // Blinker模式的中心位置
        int center_x = HEIGHT / 2;
        int center_y = WIDTH / 2;

        // 设置Blinker模式的细胞
        world[center_x][center_y - 1] = 1;
        world[center_x][center_y] = 1;
        world[center_x][center_y + 1] = 1;
    }
    if (strcmp(pattern_name, "Toad") == 0)
    {
        // 初始化Toad模式
        // Toad模式是一个4x2的模式，所以我们需要确保世界的宽度至少为4，高度至少为2
        if (WIDTH < 4 || HEIGHT < 2)
        {
            printf("世界太小，无法初始化Toad模式\n");
            return;
        }

        // Toad模式的中心位置
        int center_x = HEIGHT / 2;
        int center_y = WIDTH / 2;

        // 设置Toad模式的细胞
        world[center_x - 1][center_y - 1] = 1;
        world[center_x - 1][center_y] = 1;
        world[center_x - 1][center_y + 1] = 1;
        world[center_x][center_y - 2] = 1;
        world[center_x][center_y - 1] = 1;
        world[center_x][center_y] = 1;
    }
    if (strcmp(pattern_name, "Pulsar") == 0)
    {
        // 初始化 Pulsar 模式
        // Pulsar 模式是一个13x13的模式，所以我们需要确保世界的宽度和高度至少为13
        if (WIDTH < 13 || HEIGHT < 13)
        {
            printf("世界太小，无法初始化 Pulsar 模式\n");
            return;
        }

        // Pulsar 模式的中心位置
        int center_x = HEIGHT / 2;
        int center_y = WIDTH / 2;

        // 设置 Pulsar 模式的细胞
        for (int i = -6; i <= 6; i++)
        {
            for (int j = -6; j <= 6; j++)
            {
                if ((abs(i) % 6 == 1 || abs(i) % 6 == 4) && (abs(j) % 6 == 1 || abs(j) % 6 == 4))
                {
                    world[center_x + i][center_y + j] = 1;
                }
            }
        }
    }
    if (strcmp(pattern_name, "Pentadecathlon") == 0)
    {
        // 初始化 Pentadecathlon 模式
        // Pentadecathlon 模式是一个8x3的模式，所以我们需要确保世界的宽度至少为8，高度至少为3
        if (WIDTH < 8 || HEIGHT < 3)
        {
            printf("世界太小，无法初始化 Pentadecathlon 模式\n");
            return;
        }

        // Pentadecathlon 模式的中心位置
        int center_x = HEIGHT / 2;
        int center_y = WIDTH / 2;

        // 设置 Pentadecathlon 模式的细胞
        for (int i = -4; i <= 3; i++)
        {
            world[center_x][center_y + i] = 1;
            if (i == -3 || i == 2)
            {
                world[center_x - 1][center_y + i] = 1;
                world[center_x + 1][center_y + i] = 1;
            }
        }
    }
    if (strcmp(pattern_name, "LightweightSpaceship") == 0)
    {
        // 初始化 Lightweight Spaceship 模式
        // Lightweight Spaceship 模式是一个5x4的模式，所以我们需要确保世界的宽度至少为5，高度至少为4
        if (WIDTH < 5 || HEIGHT < 4)
        {
            printf("世界太小，无法初始化 Lightweight Spaceship 模式\n");
            return;
        }

        // Lightweight Spaceship 模式的中心位置
        int center_x = HEIGHT / 2;
        int center_y = WIDTH / 2;

        // 设置 Lightweight Spaceship 模式的细胞
        world[center_x - 1][center_y - 2] = 1;
        world[center_x - 1][center_y + 2] = 1;
        world[center_x][center_y - 2] = 1;
        world[center_x][center_y + 1] = 1;
        world[center_x + 1][center_y - 2] = 1;
        world[center_x + 1][center_y - 1] = 1;
        world[center_x + 1][center_y] = 1;
        world[center_x + 1][center_y + 1] = 1;
    }
    if (strcmp(pattern_name, "MiddleweightSpaceship") == 0)
    {
        // 初始化 Middleweight Spaceship 模式
        // Middleweight Spaceship 模式是一个6x5的模式，所以我们需要确保世界的宽度至少为6，高度至少为5
        if (WIDTH < 6 || HEIGHT < 5)
        {
            printf("世界太小，无法初始化 Middleweight Spaceship 模式\n");
            return;
        }

        // Middleweight Spaceship 模式的中心位置
        int center_x = HEIGHT / 2;
        int center_y = WIDTH / 2;

        // 设置 Middleweight Spaceship 模式的细胞
        world[center_x - 2][center_y - 2] = 1;
        world[center_x - 2][center_y + 2] = 1;
        world[center_x - 1][center_y - 2] = 1;
        world[center_x - 1][center_y + 1] = 1;
        world[center_x][center_y - 2] = 1;
        world[center_x][center_y - 1] = 1;
        world[center_x][center_y] = 1;
        world[center_x][center_y + 1] = 1;
        world[center_x + 1][center_y + 2] = 1;
    }
    if (strcmp(pattern_name, "HeavyweightSpaceship") == 0)
    {
        // 初始化 Heavyweight Spaceship 模式
        // Heavyweight Spaceship 模式是一个7x5的模式，所以我们需要确保世界的宽度至少为7，高度至少为5
        if (WIDTH < 7 || HEIGHT < 5)
        {
            printf("世界太小，无法初始化 Heavyweight Spaceship 模式\n");
            return;
        }

        // Heavyweight Spaceship 模式的中心位置
        int center_x = HEIGHT / 2;
        int center_y = WIDTH / 2;

        // 设置 Heavyweight Spaceship 模式的细胞
        world[center_x - 2][center_y - 3] = 1;
        world[center_x - 2][center_y + 2] = 1;
        world[center_x - 1][center_y - 3] = 1;
        world[center_x - 1][center_y + 1] = 1;
        world[center_x][center_y - 3] = 1;
        world[center_x][center_y - 2] = 1;
        world[center_x][center_y - 1] = 1;
        world[center_x][center_y] = 1;
        world[center_x + 1][center_y + 2] = 1;
        world[center_x + 1][center_y + 3] = 1;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("请提供一个模式名称\n");
        return 1;
    }

    // 初始化世界
    initialize(100, 50, 0.0f);

    // 初始化特定模式
    initialize_pattern(argv[1]);

    // 主循环
    while (1)
    {
        print_world();
        update();
        delay(500);

        if (kbhit())
        {
            char ch = getchar();
            if (ch == 's')
            {
                save_to_bmp("game_of_life.bmp");
            }
        }
    }

    return 0;
}