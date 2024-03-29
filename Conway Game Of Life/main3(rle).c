#include "game_of_life.h"
#include "game_of_life.c"
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

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

int main()
{
    load_rle("gosperglidergun.rle");
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