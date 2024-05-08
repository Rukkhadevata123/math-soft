#include <Eigen/Dense>

class NeuralNetwork {
public:
    NeuralNetwork(int inputSize, int outputSize, int hiddenLayerSize);
    Eigen::VectorXd forward(const Eigen::VectorXd& input);
    void backward(const Eigen::VectorXd& output, const Eigen::VectorXd& target);
    void updateWeights(double learningRate);

private:
    Eigen::MatrixXd weights1;
    Eigen::MatrixXd weights2;
    Eigen::VectorXd bias1;
    Eigen::VectorXd bias2;
    Eigen::VectorXd hiddenLayer;
    Eigen::VectorXd outputLayer;
    Eigen::VectorXd deltaOutput;
    Eigen::VectorXd deltaHidden;
    Eigen::VectorXd input;  // 添加这行
};