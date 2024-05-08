#include "tiny_dnn/tiny_dnn.h"
#include <vector>

using namespace tiny_dnn;
using namespace tiny_dnn::activation;

int main() {
    // 创建一个神经网络
    network<sequential> net;

    // 添加三层全连接层，每层有50个神经元，使用sigmoid激活函数
    net << fully_connected_layer<sigmoid>(784, 50)   // 输入层，784个神经元（对应28x28像素的MNIST图像）
        << fully_connected_layer<sigmoid>(50, 50)    // 隐藏层，50个神经元
        << fully_connected_layer<sigmoid>(50, 10);   // 输出层，10个神经元（对应10个数字类别）

    // 加载MNIST数据集
    std::vector<label_t> train_labels, test_labels;
    std::vector<vec_t> train_images, test_images;

    parse_mnist_labels("data/train-labels-idx1-ubyte", &train_labels);
    parse_mnist_images("data/train-images-idx3-ubyte", &train_images, -1.0, 1.0, 2, 2);
    parse_mnist_labels("data/t10k-labels-idx1-ubyte", &test_labels);
    parse_mnist_images("data/t10k-images-idx3-ubyte", &test_images, -1.0, 1.0, 2, 2);

    // 训练模型
    int epochs = 20;  // 训练轮数
    int batch_size = 10;  // 批次大小
    double learning_rate = 0.1;  // 学习率

    adagrad optimizer;  // 使用Adagrad优化器
    net.train<cross_entropy>(optimizer, train_images, train_labels, batch_size, epochs);

    // 保存模型
    net.save("model");

    return 0;
}