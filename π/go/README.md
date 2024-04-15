# Viète's Formula for π

这个程序使用了韦达公式来计算 π 的值。韦达公式是一个无穷乘积公式，可以用来计算 π 的值。公式如下：

![formula](https://latex.codecogs.com/gif.latex?%5Cfrac%7B2%7D%7B%5Cpi%7D%20%3D%20%5Cfrac%7B%5Csqrt%7B2%7D%7D%7B2%7D%20%5Ccdot%20%5Cfrac%7B%5Csqrt%7B2%20&plus;%20%5Csqrt%7B2%7D%7D%7D%7B2%7D%20%5Ccdot%20%5Cfrac%7B%5Csqrt%7B2%20&plus;%20%5Csqrt%7B2%20&plus;%20%5Csqrt%7B2%7D%7D%7D%7D%7B2%7D%20%5Ccdot%20%5Ccdots)

## 程序用法

这个程序接受两个命令行参数：

- `-i`：迭代次数，即公式中的无穷乘积项数。默认值为120000。
- `-p`：计算的精度，即计算结果的小数点后的位数。默认值为120000。

你可以通过以下方式运行这个程序：

```bash
go run Viète's formula.go -i 300 -p 500
```

这将会计算 π 的值，迭代次数为300，精度为500位小数。

注意：增加迭代次数和精度会增加计算的时间和内存使用量。
