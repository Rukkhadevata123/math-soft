/**
 * @file DigitDrawing.h
 * @brief 该文件包含了一个简单的像素字体和绘制数字的函数的定义。
 */

#include <fstream>
#include <vector>
#include "BitmapStructures.h"

/**
 * @brief 一个简单的像素字体，用于表示数字。
 */
const std::vector<std::vector<std::string>> DIGITS = {
    {"111", "101", "101", "101", "111"}, // 0
    {"010", "110", "010", "010", "111"}, // 1
    {"111", "001", "111", "100", "111"}, // 2
    {"111", "001", "111", "001", "111"}, // 3
    {"101", "101", "111", "001", "001"}, // 4
    {"111", "100", "111", "001", "111"}, // 5
    {"111", "100", "111", "101", "111"}, // 6
    {"111", "001", "001", "001", "001"}, // 7
    {"111", "101", "111", "101", "111"}, // 8
    {"111", "101", "111", "001", "111"}  // 9
};

/**
 * @brief 在位图文件中绘制一个数字。
 * @param file 输出文件流。
 * @param digit 要绘制的数字。
 * @param start_x 数字左上角的x坐标。
 * @param start_y 数字左上角的y坐标。
 * @param color 数字的颜色。
 * @param scale 数字的缩放因子。
 */
void draw_digit(std::ofstream& file, int digit, int start_x, int start_y, const RGBTRIPLE& color, int scale) {
    for (int y = 0; y < DIGITS[digit].size(); y++) { // 遍历数字的每一行
        for (int x = 0; x < DIGITS[digit][y].size(); x++) { // 遍历数字的每一列
            if (DIGITS[digit][y][x] == '1') { // 如果当前位置是1
                for (int sy = 0; sy < scale; sy++) { // 在y方向上进行缩放
                    for (int sx = 0; sx < scale; sx++) { // 在x方向上进行缩放
                        file.seekp((start_y + (DIGITS[digit].size() - 1 - y) * scale + sy) * 1024 * 3 + (start_x + x * scale + sx) * 3); // 定位到文件中的像素位置
                        file.write(reinterpret_cast<const char*>(&color), sizeof(color)); // 写入颜色数据
                    }
                }
            }
        }
    }
}