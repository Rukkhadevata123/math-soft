#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include "game_of_life.h"
#include "game_of_life.c"

int kbhit(void)
{
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

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int main()
{
    int width, height, iterations, delay_time;
    float live_cell_ratio;

    printf("请输入画布的宽度：");
    scanf("%d", &width);
    printf("请输入画布的高度：");
    scanf("%d", &height);
    printf("请输入细胞存活率（0-1）：");
    scanf("%f", &live_cell_ratio);
    printf("请输入迭代次数：");
    scanf("%d", &iterations);
    printf("请输入每次更新的延迟时间（毫秒）：");
    scanf("%d", &delay_time);

    initialize(width, height, live_cell_ratio);
    for (int i = 0; i < iterations; i++)
    {
        print_world();
        update();
        delay(delay_time);

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
