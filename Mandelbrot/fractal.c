#include "fractal.h"
#include <math.h>

int mandelbrot(double real, double imag)
{
    int max_iter = 5000; // 增加迭代次数以增加复杂性
    double r = 0.0;
    double i = 0.0;
    int n = 0;
    for (; n < max_iter && r * r + i * i <= 4.0; n++)
    {
        double temp = r * r - i * i + real;
        i = 2 * r * i + imag;
        r = temp;
    }

    // 平滑颜色算法
    if (n == max_iter)
    {
        return 0; // 如果点在Mandelbrot集合中，返回黑色
    }
    else
    {
        // 如果点不在Mandelbrot集合中，使用平滑颜色算法计算颜色
        double zn = sqrt(r * r + i * i);
        int nu = log2(1.75 + log2(log2(zn))) / log2(2);
        n = n + 1 - nu;
        return n;
    }
}

void color_map(int value, RGBTRIPLE *color)
{
    if (value == 0)
    {
        color->rgbRed = 0;
        color->rgbGreen = 0;
        color->rgbBlue = 0;
    }
    else
    {
        color->rgbRed = value % 8 * 32;
        color->rgbGreen = value % 16 * 16;
        color->rgbBlue = value % 32 * 8;
    }
}