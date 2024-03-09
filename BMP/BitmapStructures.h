/**
 * @file BitmapStructures.h
 * @brief 该文件包含了位图文件中使用的结构体的定义。
 */

#pragma pack(push, 1) // 设置结构体按照1字节对齐

/**
 * @brief 位图文件的文件头结构体。
 */
struct BITMAPFILEHEADER {
    unsigned short bfType; ///< 位图文件的类型。
    unsigned int bfSize; ///< 位图文件的大小。
    unsigned short bfReserved1; ///< 保留字段1。
    unsigned short bfReserved2; ///< 保留字段2。
    unsigned int bfOffBits; ///< 位图数据的偏移量。
};

/**
 * @brief 位图文件的信息头结构体。
 */
struct BITMAPINFOHEADER {
    unsigned int biSize; ///< 信息头的大小。
    int biWidth; ///< 位图的宽度。
    int biHeight; ///< 位图的高度。
    unsigned short biPlanes; ///< 位图的平面数。
    unsigned short biBitCount; ///< 每个像素的位数。
    unsigned int biCompression; ///< 压缩类型。
    unsigned int biSizeImage; ///< 位图数据的大小。
    int biXPelsPerMeter; ///< 水平分辨率。
    int biYPelsPerMeter; ///< 垂直分辨率。
    unsigned int biClrUsed; ///< 使用的颜色数。
    unsigned int biClrImportant; ///< 重要的颜色数。
};

/**
 * @brief 表示一个RGB像素的结构体。
 */
struct RGBTRIPLE {
    unsigned char rgbBlue; ///< 蓝色分量。
    unsigned char rgbGreen; ///< 绿色分量。
    unsigned char rgbRed; ///< 红色分量。
};

#pragma pack(pop) // 恢复默认的结构体对齐方式