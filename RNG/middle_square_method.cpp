#include <fstream>
#include <iostream>

// 定义BMP图像的宽度和高度
#define WIDTH 512
#define HEIGHT 512

// 定义用于生成BMP图像的RGB颜色结构体
struct RGB {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

// 定义中间平方法的种子
unsigned long seed = 0;

// 初始化中间平方法
void init_middle_square_method(unsigned long s) { seed = s; } // 设置种子

// 使用中间平方法生成一个32位的随机数
unsigned long middle_square_method() {
    seed *= seed;                       // 种子的平方
    seed = (seed >> 16) & 0x7fffffffUL; // 取种子平方的中间32位
    return seed;
}

// 使用中间平方法生成一个随机的RGB颜色
RGB generate_random_color_middle_square() {
    RGB color;
    color.r = middle_square_method() % 256; // 生成红色分量
    color.g = middle_square_method() % 256; // 生成绿色分量
    color.b = middle_square_method() % 256; // 生成蓝色分量
    return color;
}

// 使用中间平方法生成一个BMP图像
void generate_bmp_middle_square(const std::string &filename) {
    std::ofstream file(filename, std::ios::binary); // 创建二进制文件

    // 定义BMP文件头
    unsigned char fileHeader[14] = {
            'B', 'M',       // 文件类型标识符
            0,   0,   0, 0, // 文件大小
            0,   0,         // 保留字段1
            0,   0,         // 保留字段2
            54,  0,   0, 0  // 偏移量，即RGB数据距离文件头的偏移量
    };

    // 定义BMP信息头
    unsigned char infoHeader[40] = {
            40, 0, 0, 0, // 信息头大小
            0,  0, 0, 0, // 图像宽度
            0,  0, 0, 0, // 图像高度
            1,  0,       // 颜色平面数
            24, 0,       // 每个像素的位数
            0,  0, 0, 0, // 压缩类型
            0,  0, 0, 0, // 图像大小
            0,  0, 0, 0, // 水平分辨率
            0,  0, 0, 0, // 垂直分辨率
            0,  0, 0, 0, // 调色板中的颜色数
            0,  0, 0, 0, // 重要颜色数
    };

    // 设置图像的宽度和高度
    *(int *)&infoHeader[4] = WIDTH;
    *(int *)&infoHeader[8] =
            -HEIGHT; // 设置图像高度为负数，表示像素是从上到下的顺序

    // 写入文件头和信息头
    file.write((char *)fileHeader, 14);
    file.write((char *)infoHeader, 40);

    // 生成并写入像素数据
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            RGB color = generate_random_color_middle_square(); // 生成随机颜色
            file.write((char *)&color, 3); // 写入颜色数据
        }
    }

    file.close(); // 关闭文件
}

int main() {
    init_middle_square_method(123456789); // 使用一个种子初始化中间平方法
    generate_bmp_middle_square("random_middle_square.bmp"); // 生成BMP图像
    return 0;
}