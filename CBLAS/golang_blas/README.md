# 矩阵乘法方法比较

本项目提供了三种矩阵乘法方法的实现：标准乘法、分块乘法和稀疏乘法。以下是对这三种方法的简要介绍和它们对密集矩阵和稀疏矩阵的处理。

## 标准乘法

标准乘法是最直接的矩阵乘法方法。它通过遍历两个矩阵的所有元素来计算结果矩阵的每个元素。这种方法的时间复杂度是 O(n^3)，其中 n 是矩阵的行数或列数。

对于密集矩阵，标准乘法需要处理所有的元素，即使它们是零。对于稀疏矩阵，标准乘法的效率较低，因为它会浪费大量时间处理零元素。

## 分块乘法

分块乘法是一种优化的矩阵乘法方法。它将矩阵分成多个小块，然后对每个块进行标准乘法。这种方法可以利用缓存和并行计算来提高效率。

对于密集矩阵，分块乘法通常比标准乘法更快。对于稀疏矩阵，分块乘法的效率取决于非零元素的分布。如果非零元素均匀分布，分块乘法可能比标准乘法更快。如果非零元素集中在某些块中，分块乘法可能不如标准乘法。

## 稀疏乘法

稀疏乘法是专门为稀疏矩阵设计的矩阵乘法方法。它只处理非零元素，从而大大提高了效率。

对于密集矩阵，稀疏乘法的效率较低，因为它需要处理所有的元素。对于稀疏矩阵，稀疏乘法通常比标准乘法和分块乘法更快。

## 测试用例

你可以使用以下命令来运行测试用例：

```bash
go run three_methods.go time_maintest.go -size=640 -density=0.1 -sparse=true -blockSize=8
```

这个命令会创建一个 640x640 的稀疏矩阵，其中 10% 的元素是非零的。然后，它会使用三种方法进行矩阵乘法，并输出每种方法的运行时间。

## 测试结果

以下是对稀疏矩阵和密集矩阵进行测试的结果：

### 对于稀疏矩阵

 - 标准乘法耗时：911.890257ms
 - 分块乘法耗时：489.463654ms
 - 稀疏乘法耗时：87.895163ms

### 对于密集矩阵

 - 标准乘法耗时：984.16647ms
 - 分块乘法耗时：496.145951ms
 - 稀疏乘法耗时：3.535204558s

从结果可以看出，对于稀疏矩阵，稀疏乘法的效率最高。而对于密集矩阵，分块乘法的效率最高。这证明了我们前面对这三种方法的分析。