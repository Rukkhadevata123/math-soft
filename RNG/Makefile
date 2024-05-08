# 编译器
CXX = g++

# 编译器选项
CXXFLAGS = -Wall -std=c++11

# 目标文件
TARGETS = middle_square_method mersenne_twister

# 默认目标
all: $(TARGETS)

middle_square_method: middle_square_method.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

mersenne_twister: mersenne_twister.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# 运行目标
run: all
	./middle_square_method
	./mersenne_twister

# 清理目标
clean:
	rm -f $(TARGETS) *.bmp
