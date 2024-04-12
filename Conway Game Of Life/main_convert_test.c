#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "game_of_life.h"
#include "game_of_life.c"
// Not finished yet
int main()
{
    // 测试 convert_rle_to_txt 函数
    // convert_rle_to_txt("gosperglidergun.rle", "gosperglidergun.txt");
    // 测试 convert_txt_to_rle 函数
    convert_txt_to_rle("gosperglidergun.txt", "gosperglidergun.rle");
    return 0;
}