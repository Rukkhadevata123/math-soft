#pragma pack(push, 1) // 设置结构体按照1字节对齐
struct BITMAPFILEHEADER { // 定义位图文件头结构体
    unsigned short bfType; // 位图文件类型
    unsigned int bfSize; // 位图文件大小
    unsigned short bfReserved1; // 保留字段1
    unsigned short bfReserved2; // 保留字段2
    unsigned int bfOffBits; // 位图数据偏移量
};

struct BITMAPINFOHEADER { // 定义位图信息头结构体
    unsigned int biSize; // 位图信息头大小
    int biWidth; // 位图宽度
    int biHeight; // 位图高度
    unsigned short biPlanes; // 位图平面数
    unsigned short biBitCount; // 每个像素的位数
    unsigned int biCompression; // 压缩类型
    unsigned int biSizeImage; // 位图数据大小
    int biXPelsPerMeter; // 水平分辨率
    int biYPelsPerMeter; // 垂直分辨率
    unsigned int biClrUsed; // 使用的颜色数
    unsigned int biClrImportant; // 重要的颜色数
};

struct RGBTRIPLE { // 定义RGB像素结构体
    unsigned char rgbBlue; // 蓝色分量
    unsigned char rgbGreen; // 绿色分量
    unsigned char rgbRed; // 红色分量
};
#pragma pack(pop) // 恢复默认的结构体对齐方式