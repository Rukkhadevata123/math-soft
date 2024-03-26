// main.c
#include <stdio.h>
#include <stdlib.h>
#include "fractal.h"

int main() {
    int width = 12288;
    int height = 12288;

    BITMAPFILEHEADER bfh = {0x4D42, 54 + width * height * 3, 0, 0, 54};
    BITMAPINFOHEADER bih = {40, width, height, 1, 24, 0, width * height * 3, 0, 0, 0, 0};
    RGBTRIPLE* image = malloc(width * height * sizeof(RGBTRIPLE));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double real = (x - width / 2.0) * 4.0 / width;
            double imag = (y - height / 2.0) * 4.0 / height;
            int value = mandelbrot(real, imag);
            color_map(value, &image[y * width + x]); // 使用颜色映射函数
        }
    }

    FILE* file = fopen("mandelbrot.bmp", "wb");
    fwrite(&bfh, sizeof(bfh), 1, file);
    fwrite(&bih, sizeof(bih), 1, file);
    fwrite(image, sizeof(RGBTRIPLE), width * height, file);
    fclose(file);

    free(image);

    return 0;
}
