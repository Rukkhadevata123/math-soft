#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// 利布尼茨级数的C语言实现
double leibniz_series(int terms)
{
    double pi = 0.0;
    int sign = 1;
    for (int i = 0; i < terms; i++)
    {
        double term = 1.0 / (2 * i + 1);
        pi += sign * term;
        sign *= -1;
    }
    return pi * 4;
}

// 尼拉坎塔级数的C语言实现
double nilakantha_series(int terms)
{
    double pi = 3.0;
    int sign = 1;
    for (int i = 2; i < terms * 2; i += 2)
    {
        double term = 4.0 / (i * (i + 1.0) * (i + 2.0));
        pi += sign * term;
        sign *= -1;
    }
    return pi;
}

// 瓦利斯公式的C语言实现
double wallis_product(int terms)
{
    double pi_product = 1.0;
    for (int i = 1; i <= terms; i++)
    {
        double term = (2.0 * i) / (2.0 * i - 1) * (2.0 * i) / (2.0 * i + 1);
        pi_product *= term;
    }
    return pi_product * 2;
}

// 蒙特卡洛方法的C语言实现
double monte_carlo(int iterations)
{
    srand(time(NULL));
    int inside_circle = 0;
    for (int i = 0; i < iterations; i++)
    {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1.0)
        {
            inside_circle++;
        }
    }
    return 4.0 * inside_circle / iterations;
}

// BBP公式的C语言实现
double bbp_formula(int terms)
{
    double pi = 0.0;
    for (int k = 0; k < terms; k++)
    {
        double term = 1.0 / pow(16, k) * (4.0 / (8 * k + 1) - 2.0 / (8 * k + 4) - 1.0 / (8 * k + 5) - 1.0 / (8 * k + 6));
        pi += term;
    }
    return pi;
}

// Chudnovsky公式的C语言实现
double factorial(int n)
{
    double fact = 1.0;
    for (int i = 2; i <= n; i++)
    {
        fact *= i;
    }
    return fact;
}

double chudnovsky_algorithm(int terms)
{
    double pi = 0.0;
    for (int k = 0; k < terms; k++)
    {
        double numerator = pow(-1, k) * exp(lgamma(6 * k + 1)) * (545140134 * k + 13591409);
        double denominator = exp(lgamma(3 * k + 1)) * pow(exp(lgamma(k + 1)), 3) * pow(640320, 3 * k + 3.0 / 2.0);
        pi += numerator / denominator;
    }
    pi *= 12.0;
    pi = 1.0 / pi;
    return pi;
}

int main()
{
    int terms = 10000;
    int iterations = 1000000;

    printf("Leibniz series approximation for pi: %.15f\n", leibniz_series(terms));
    printf("Nilakantha series approximation for pi: %.15f\n", nilakantha_series(terms));
    printf("Wallis product approximation for pi: %.15f\n", wallis_product(terms));
    printf("Monte Carlo method approximation for pi: %.15f\n", monte_carlo(iterations));
    printf("BBP formula approximation for pi: %.15f\n", bbp_formula(terms));
    printf("Chudnovsky algorithm approximation for pi: %.15f\n", chudnovsky_algorithm(terms));

    return 0;
}
