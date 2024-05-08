#include "NeuralNetwork.h"
#include "MNISTLoader.h"
#include <iostream>

int main() {
    // 加载MNIST数据
    MNISTLoader loader("data/train-images-idx3-ubyte", "data/train-labels-idx1-ubyte");
    auto trainImages = loader.getImages();
    auto trainLabels = loader.getLabels();

    MNISTLoader loaderTest("data/t10k-images-idx3-ubyte", "data/t10k-labels-idx1-ubyte");
    auto testImages = loaderTest.getImages();
    auto testLabels = loaderTest.getLabels();

    // 创建神经网络
    NeuralNetwork nn(28*28, 10, 100);

    // 训练神经网络
    int i = 0;
    for (int i = 0; i < trainImages.size(); ++i) {
        auto input = trainImages[i];  // 输入向量
        Eigen::VectorXd target = Eigen::VectorXd::Zero(10);  // 目标向量
        target[trainLabels[i]] = 1;
        auto output = nn.forward(input);
        nn.backward(output, target);
        nn.updateWeights(0.01);

        // 每训练100个样本，就输出一次结果
        if (i % 100 == 0) {
            int correct = 0;
            for (int j = 0; j < testImages.size(); ++j) {
                auto input = testImages[j];
                auto output = nn.forward(input);
                if (output.maxCoeff() == testLabels[j]) {
                    correct++;
                }
            }
            std::cout << "After " << i << " training samples, accuracy: " << correct / static_cast<double>(testImages.size()) << std::endl;
        }
    }

    // 测试神经网络
    int correct = 0;
    for (int i = 0; i < testImages.size(); ++i) {
        auto input = testImages[i];
        auto output = nn.forward(input);
        if (output.maxCoeff() == testLabels[i]) {
            correct++;
        }
    }
    std::cout << "Final accuracy: " << correct / static_cast<double>(testImages.size()) << std::endl;

    return 0;
}