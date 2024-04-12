#include <fstream>  // 包含文件流操作的头文件
#include <iostream> // 包含输入输出流操作的头文件
#include <vector>   // 包含向量操作的头文件

#pragma pack(push, 1) // 设置结构体按照1字节对齐
struct BITMAPFILEHEADER
{                               // 定义位图文件头结构体
    unsigned short bfType;      // 位图文件类型
    unsigned int bfSize;        // 位图文件大小
    unsigned short bfReserved1; // 保留字段1
    unsigned short bfReserved2; // 保留字段2
    unsigned int bfOffBits;     // 位图数据偏移量
};

struct BITMAPINFOHEADER
{                                // 定义位图信息头结构体
    unsigned int biSize;         // 位图信息头大小
    int biWidth;                 // 位图宽度
    int biHeight;                // 位图高度
    unsigned short biPlanes;     // 位图平面数
    unsigned short biBitCount;   // 每个像素的位数
    unsigned int biCompression;  // 压缩类型
    unsigned int biSizeImage;    // 位图数据大小
    int biXPelsPerMeter;         // 水平分辨率
    int biYPelsPerMeter;         // 垂直分辨率
    unsigned int biClrUsed;      // 使用的颜色数
    unsigned int biClrImportant; // 重要的颜色数
};

struct RGBTRIPLE
{                           // 定义RGB像素结构体
    unsigned char rgbBlue;  // 蓝色分量
    unsigned char rgbGreen; // 绿色分量
    unsigned char rgbRed;   // 红色分量
};
#pragma pack(pop) // 恢复默认的结构体对齐方式

// 定义一个简单的像素字体
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

void draw_digit(std::ofstream &file, int digit, int start_x, int start_y, const RGBTRIPLE &color, int scale)
{
    for (int y = 0; y < DIGITS[digit].size(); y++)
    { // 遍历数字的每一行
        for (int x = 0; x < DIGITS[digit][y].size(); x++)
        { // 遍历数字的每一列
            if (DIGITS[digit][y][x] == '1')
            { // 如果当前位置是1
                for (int sy = 0; sy < scale; sy++)
                { // 在y方向上进行缩放
                    for (int sx = 0; sx < scale; sx++)
                    {                                                                                                                    // 在x方向上进行缩放
                        file.seekp((start_y + (DIGITS[digit].size() - 1 - y) * scale + sy) * 1024 * 3 + (start_x + x * scale + sx) * 3); // 定位到文件中的像素位置
                        file.write(reinterpret_cast<const char *>(&color), sizeof(color));                                               // 写入颜色数据
                    }
                }
            }
        }
    }
}

int main()
{
    BITMAPFILEHEADER bfh; // 定义位图文件头变量
    BITMAPINFOHEADER bih; // 定义位图信息头变量
    RGBTRIPLE color;      // 定义颜色变量

    std::ofstream file("output.bmp", std::ios::binary); // 打开输出文件流
    if (!file)
    {                                                     // 如果文件打开失败
        std::cout << "Could not open file for writing\n"; // 输出错误信息
        return 1;                                         // 返回错误码
    }

    bfh.bfType = 0x4D42;                                                                               // 设置位图文件类型
    bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 1024 * 768 * sizeof(RGBTRIPLE); // 设置位图文件大小
    bfh.bfReserved1 = 0;                                                                               // 设置保留字段1
    bfh.bfReserved2 = 0;                                                                               // 设置保留字段2
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);                               // 设置位图数据偏移量

    bih.biSize = sizeof(BITMAPINFOHEADER); // 设置位图信息头大小
    bih.biWidth = 1024;                    // 设置位图宽度
    bih.biHeight = 768;                    // 设置位图高度
    bih.biPlanes = 1;                      // 设置位图平面数
    bih.biBitCount = 24;                   // 设置每个像素的位数
    bih.biCompression = 0;                 // 设置压缩类型
    bih.biSizeImage = 0;                   // 设置位图数据大小
    bih.biXPelsPerMeter = 0;               // 设置水平分辨率
    bih.biYPelsPerMeter = 0;               // 设置垂直分辨率
    bih.biClrUsed = 0;                     // 设置使用的颜色数
    bih.biClrImportant = 0;                // 设置重要的颜色数

    color.rgbBlue = 255;  // 设置蓝色分量
    color.rgbGreen = 255; // 设置绿色分量
    color.rgbRed = 255;   // 设置红色分量

    file.write(reinterpret_cast<char *>(&bfh), sizeof(bfh)); // 写入位图文件头数据
    file.write(reinterpret_cast<char *>(&bih), sizeof(bih)); // 写入位图信息头数据

    for (int y = 0; y < bih.biHeight; y++)
    { // 遍历位图的每一行
        for (int x = 0; x < bih.biWidth; x++)
        {                                                                // 遍历位图的每一列
            file.write(reinterpret_cast<char *>(&color), sizeof(color)); // 写入颜色数据
        }
    }

    color.rgbBlue = 0;  // 设置蓝色分量为0
    color.rgbGreen = 0; // 设置绿色分量为0
    color.rgbRed = 255; // 设置红色分量为255

    int scale = 20;                              // 设置数字的大小
    int digit_width = 3 * scale;                 // 每个数字的宽度
    int gap = scale;                             // 每个数字之间的间隔
    int total_width = 4 * digit_width + 3 * gap; // 所有数字和间隔的总宽度

    // 计算新的起始x坐标以将数字移到中间
    int start_x = (bih.biWidth - total_width) / 2;

    draw_digit(file, 2, start_x, 100, color, scale);                           // 绘制数字2
    draw_digit(file, 1, start_x + digit_width + gap, 100, color, scale);       // 绘制数字1
    draw_digit(file, 7, start_x + 2 * (digit_width + gap), 100, color, scale); // 绘制数字7
    draw_digit(file, 9, start_x + 3 * (digit_width + gap), 100, color, scale); // 绘制数字9

    file.close(); // 关闭文件流

    return 0; // 返回成功码
}