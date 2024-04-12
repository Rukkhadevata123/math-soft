#pragma once

#pragma pack(push, 1)
typedef struct
{
    unsigned short bfType;
    unsigned int bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int bfOffBits;
} BITMAPFILEHEADER;

typedef struct
{
    unsigned int biSize;
    int biWidth;
    int biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
} BITMAPINFOHEADER;

typedef struct
{
    unsigned char rgbBlue;
    unsigned char rgbGreen;
    unsigned char rgbRed;
} RGBTRIPLE;
#pragma pack(pop)

int mandelbrot(double real, double imag);
void color_map(int value, RGBTRIPLE *color);