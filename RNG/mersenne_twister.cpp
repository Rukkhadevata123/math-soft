#include <iostream>
#include <fstream>

#define N 624                   // 状态向量的长度
#define M 397                   // 用于生成下一个状态向量的位移量
#define MATRIX_A 0x9908b0dfUL   // 用于生成下一个状态向量的常数
#define UPPER_MASK 0x80000000UL // 用于取状态向量的上半部分
#define LOWER_MASK 0x7fffffffUL // 用于取状态向量的下半部分

static unsigned long mt[N]; // 状态向量
static int mti = N + 1;     // 状态向量的索引

// 初始化状态向量
void init_genrand(unsigned long s) {
    mt[0] = s & 0xffffffffUL;
    for (mti = 1; mti < N; mti++) {
        mt[mti] = (1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);
        mt[mti] &= 0xffffffffUL;
    }
}

// 生成一个32位的随机数
unsigned long genrand_int32(void) {
    unsigned long y;
    static unsigned long mag01[2] = {0x0UL, MATRIX_A};
    if (mti >= N) { // 如果状态向量已经用完，就生成下一个状态向量
        int kk;
        for (kk = 0; kk < N - M; kk++) {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (; kk < N - 1; kk++) {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
        mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];
        mti = 0;
    }
    y = mt[mti++];
    y ^= (y >> 11);                // 混淆函数
    y ^= (y << 7) & 0x9d2c5680UL;  // 混淆函数
    y ^= (y << 15) & 0xefc60000UL; // 混淆函数
    y ^= (y >> 18);                // 混淆函数
    return y;
}

// 生成一个64位的随机数
unsigned long long genrand_int64(void) {
    return ((unsigned long long)genrand_int32() << 32) | genrand_int32();
}

// BMP图像的宽度和高度
#define WIDTH 512
#define HEIGHT 512

// 用于生成BMP图像的RGB颜色结构体
struct RGB {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

// 初始化梅森旋转算法
void init_mersenne_twister(unsigned long seed) {
    init_genrand(seed);
}

// 生成一个随机的RGB颜色
RGB generate_random_color() {
    RGB color;
    unsigned long long rand_value = genrand_int64();
    color.r = rand_value % 256;
    rand_value >>= 8;
    color.g = rand_value % 256;
    rand_value >>= 8;
    color.b = rand_value % 256;
    return color;
}

// 生成一个BMP图像
void generate_bmp(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);

    // BMP文件头
    unsigned char fileHeader[14] = {
        'B', 'M',  // 魔数
        0, 0, 0, 0,  // 文件大小
        0, 0,  // 保留字段
        0, 0,  // 保留字段
        54, 0, 0, 0  // 偏移量到像素数据
    };

    // BMP信息头
    unsigned char infoHeader[40] = {
        40, 0, 0, 0,  // 信息头大小
        0, 0, 0, 0,  // 图像宽度
        0, 0, 0, 0,  // 图像高度
        1, 0,  // 颜色平面数
        24, 0,  // 每像素位数
        0, 0, 0, 0,  // 压缩类型
        0, 0, 0, 0,  // 图像大小
        0, 0, 0, 0,  // 水平分辨率
        0, 0, 0, 0,  // 垂直分辨率
        0, 0, 0, 0,  // 颜色表中的颜色数
        0, 0, 0, 0,  // 重要颜色数
    };

    // 设置图像的宽度和高度
    *(int*)&infoHeader[4] = WIDTH;
    *(int*)&infoHeader[8] = -HEIGHT;  // 负的高度表示像素顺序从上到下

    // 写入文件头和信息头
    file.write((char*)fileHeader, 14);
    file.write((char*)infoHeader, 40);

    // 生成并写入像素数据
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            RGB color = generate_random_color();
            file.write((char*)&color, 3);
        }
    }

    file.close();
}

int main() {
    init_mersenne_twister(123456789);  // 使用一个种子初始化梅森旋转算法
    generate_bmp("random32.bmp");  // 生成32位随机颜色的BMP图像
    generate_bmp("random64.bmp");  // 生成64位随机颜色的BMP图像
    return 0;
}