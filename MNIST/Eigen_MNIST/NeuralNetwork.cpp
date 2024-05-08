#include "NeuralNetwork.h"
#include <cmath>

NeuralNetwork::NeuralNetwork(int inputSize, int outputSize, int hiddenLayerSize)
    : weights1(Eigen::MatrixXd::Random(hiddenLayerSize, inputSize)),
      weights2(Eigen::MatrixXd::Random(outputSize, hiddenLayerSize)),
      bias1(Eigen::VectorXd::Random(hiddenLayerSize)),
      bias2(Eigen::VectorXd::Random(outputSize)) {}

Eigen::VectorXd NeuralNetwork::forward(const Eigen::VectorXd& input) {
    this->input = input;  // 保存输入层的值
    hiddenLayer = (weights1 * input + bias1).unaryExpr([](double x) { return 1 / (1 + std::exp(-x)); });
    outputLayer = (weights2 * hiddenLayer + bias2).unaryExpr([](double x) { return 1 / (1 + std::exp(-x)); });
    return outputLayer;
}

void NeuralNetwork::backward(const Eigen::VectorXd& output, const Eigen::VectorXd& target) {
    deltaOutput = output - target;
    deltaHidden = weights2.transpose() * deltaOutput;
}

void NeuralNetwork::updateWeights(double learningRate) {
    weights2 -= learningRate * deltaOutput * hiddenLayer.transpose();
    bias2 -= learningRate * deltaOutput;
    weights1 -= learningRate * deltaHidden * this->input.transpose();  // 使用输入层的转置
    bias1 -= learningRate * deltaHidden;
}