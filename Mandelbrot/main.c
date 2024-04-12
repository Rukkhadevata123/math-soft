#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fractal.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s <width> <height> <num_images>\n", argv[0]);
        return 1;
    }

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int num_images = atoi(argv[3]);
    double zoom_factor = 0.05; // 每次放大的因子
    double center_real = -1.5; // 视图中心的实部
    double center_imag = 0.0;  // 视图中心的虚部

    for (int i = 0; i < num_images; i++)
    {
        BITMAPFILEHEADER bfh = {0x4D42, 54 + width * height * 3, 0, 0, 54};
        BITMAPINFOHEADER bih = {40, width, height, 1, 24, 0, width * height * 3, 0, 0, 0, 0};
        RGBTRIPLE *image = malloc(width * height * sizeof(RGBTRIPLE));

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                double real = (x - width / 2.0) * 4.0 / (width * pow(1 + zoom_factor, i)) + center_real;
                double imag = (y - height / 2.0) * 4.0 / (height * pow(1 + zoom_factor, i)) + center_imag;
                int value = mandelbrot(real, imag);
                color_map(value, &image[y * width + x]); // 使用颜色映射函数
            }
        }

        char filename[50];
        sprintf(filename, "mandelbrot_%03d.bmp", i); // 为每一张图片使用一个不同的文件名
        FILE *file = fopen(filename, "wb");
        fwrite(&bfh, sizeof(bfh), 1, file);
        fwrite(&bih, sizeof(bih), 1, file);
        fwrite(image, sizeof(RGBTRIPLE), width * height, file);
        fclose(file);

        free(image);
    }

    return 0;
}