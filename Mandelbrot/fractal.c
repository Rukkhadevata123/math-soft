// fractal.c
#include "fractal.h"

int mandelbrot(double real, double imag) {
    int n;
    double r = 0.0;
    double i = 0.0;
    for(n = 0; n < 256; n++) {
        double r2 = r*r;
        double i2 = i*i;
        if(r2 + i2 > 4.0) break;
        i = 2*r*i + imag;
        r = r2 - i2 + real;
    }
    return n;
}