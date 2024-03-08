#include "DigitDrawing.h" // 包含绘制数字的头文件
#include <iostream>
#include <fstream>

int main() {
    BITMAPFILEHEADER bfh; // 定义位图文件头变量
    BITMAPINFOHEADER bih; // 定义位图信息头变量
    RGBTRIPLE color; // 定义颜色变量

    std::ofstream file("output.bmp", std::ios::binary); // 打开输出文件流
    if (!file) { // 如果文件打开失败
        std::cout << "Could not open file for writing\n"; // 输出错误信息
        return 1; // 返回错误码
    }

    bfh.bfType = 0x4D42; // 设置位图文件类型
    bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 1024 * 768 * sizeof(RGBTRIPLE); // 设置位图文件大小
    bfh.bfReserved1 = 0; // 设置保留字段1
    bfh.bfReserved2 = 0; // 设置保留字段2
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); // 设置位图数据偏移量

    bih.biSize = sizeof(BITMAPINFOHEADER); // 设置位图信息头大小
    bih.biWidth = 1024; // 设置位图宽度
    bih.biHeight = 768; // 设置位图高度
    bih.biPlanes = 1; // 设置位图平面数
    bih.biBitCount = 24; // 设置每个像素的位数
    bih.biCompression = 0; // 设置压缩类型
    bih.biSizeImage = 0; // 设置位图数据大小
    bih.biXPelsPerMeter = 0; // 设置水平分辨率
    bih.biYPelsPerMeter = 0; // 设置垂直分辨率
    bih.biClrUsed = 0; // 设置使用的颜色数
    bih.biClrImportant = 0; // 设置重要的颜色数

    color.rgbBlue = 255; // 设置蓝色分量
    color.rgbGreen = 255; // 设置绿色分量
    color.rgbRed = 255; // 设置红色分量

    file.write(reinterpret_cast<char*>(&bfh), sizeof(bfh)); // 写入位图文件头数据
    file.write(reinterpret_cast<char*>(&bih), sizeof(bih)); // 写入位图信息头数据

    for (int y = 0; y < bih.biHeight; y++) { // 遍历位图的每一行
        for (int x = 0; x < bih.biWidth; x++) { // 遍历位图的每一列
            file.write(reinterpret_cast<char*>(&color), sizeof(color)); // 写入颜色数据
        }
    }

    color.rgbBlue = 0; // 设置蓝色分量为0
    color.rgbGreen = 0; // 设置绿色分量为0
    color.rgbRed = 255; // 设置红色分量为255
    
    int scale = 20; // 设置数字的大小
    int digit_width = 3 * scale; // 每个数字的宽度
    int gap = scale; // 每个数字之间的间隔
    int total_width = 4 * digit_width + 3 * gap; // 所有数字和间隔的总宽度

    // 计算新的起始x坐标以将数字移到中间
    int start_x = (bih.biWidth - total_width) / 2;

    draw_digit(file, 2, start_x, 100, color, scale); // 绘制数字2
    draw_digit(file, 1, start_x + digit_width + gap, 100, color, scale); // 绘制数字1
    draw_digit(file, 7, start_x + 2 * (digit_width + gap), 100, color, scale); // 绘制数字7
    draw_digit(file, 9, start_x + 3 * (digit_width + gap), 100, color, scale); // 绘制数字9

    file.close(); // 关闭文件流

    return 0; // 返回成功码
}