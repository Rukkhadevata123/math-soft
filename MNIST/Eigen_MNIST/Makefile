# 指定编译器
CXX = g++

# 指定头文件路径
INCLUDES = -I/usr/include/eigen3/

# 指定源文件
SRCS = main.cpp NeuralNetwork.cpp MNISTLoader.cpp

# 指定输出文件名
OUTFILE = mnist

# 默认目标
all: $(OUTFILE)

# 编译规则
$(OUTFILE): $(SRCS)
	$(CXX) $(INCLUDES) $(SRCS) -o $(OUTFILE)

# 清理目标
clean:
	rm -f $(OUTFILE)
