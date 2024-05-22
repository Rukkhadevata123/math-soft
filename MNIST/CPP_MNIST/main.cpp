#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <cmath>
#include <algorithm>

// 可能需要一些额外的库，例如Eigen库来处理矩阵运算

// 定义一些函数
int reverseInt(int i)
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8) & 255;
    ch3 = (i >> 16) & 255;
    ch4 = (i >> 24) & 255;
    return ((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

void loadMNISTData(const std::string &filename, std::vector<std::vector<double>> &data)
{
    std::ifstream file(filename, std::ios::binary);

    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;

        file.read((char *)&magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);

        if (magic_number == 2051)
        {
            file.read((char *)&number_of_images, sizeof(number_of_images));
            number_of_images = reverseInt(number_of_images);
            file.read((char *)&n_rows, sizeof(n_rows));
            n_rows = reverseInt(n_rows);
            file.read((char *)&n_cols, sizeof(n_cols));
            n_cols = reverseInt(n_cols);

            for (int i = 0; i < number_of_images; ++i)
            {
                std::vector<double> tp;
                for (int r = 0; r < n_rows; ++r)
                {
                    for (int c = 0; c < n_cols; ++c)
                    {
                        unsigned char temp = 0;
                        file.read((char *)&temp, sizeof(temp));
                        tp.push_back((double)temp);
                    }
                }
                data.push_back(tp);
            }
        }
        else if (magic_number == 2049)
        {
            file.read((char *)&number_of_images, sizeof(number_of_images));
            number_of_images = reverseInt(number_of_images);

            for (int i = 0; i < number_of_images; ++i)
            {
                unsigned char temp = 0;
                file.read((char *)&temp, sizeof(temp));
                std::vector<double> tp(10, 0.0);
                tp[(int)temp] = 1.0;
                data.push_back(tp);
            }
        }
    }
}

class Layer;
class Neuron
{
private:
    double output;               // 神经元的输出
    double gradient;             // 神经元的梯度
    std::vector<double> weights; // 神经元的权重

    // sigmoid激活函数
    double activationFunction(double x)
    {
        return 1.0 / (1.0 + exp(-x));
    }

    // sigmoid激活函数的导数
    double activationFunctionDerivative(double x)
    {
        double sigmoid = activationFunction(x);
        return sigmoid * (1 - sigmoid);
    }

public:
    // 构造函数
    Neuron(int numInputs)
    {
        for (int i = 0; i < numInputs; ++i)
        {
            weights.push_back(((double)rand() / (RAND_MAX)) * 2 - 1); // 初始化权重为[-1, 1]的随机数
        }
    }

    // 设置神经元的值
    void setValue(double value)
    {
        output = value;
    }

    // 获取神经元的输出
    double getOutput() const
    {
        return output;
    }

    // 前向传播
    void feedForward(const Layer &prevLayer);

    // 计算输出梯度
    void calculateOutputGradient(double targetVal)
    {
        double delta = targetVal - output;
        gradient = delta * activationFunctionDerivative(output);
    }

    // 更新输入权重
    void updateInputWeights(double learningRate)
    {
        for (int i = 0; i < weights.size(); ++i)
        {
            double oldWeight = weights[i];
            weights[i] += learningRate * gradient * oldWeight;
        }
    }
};

class Layer
{
private:
    std::vector<Neuron *> neurons;   // 层中的神经元
    std::vector<double> outputCache; // 层的输出缓存

public:
    // 构造函数
    Layer(int numNeurons, int numInputsPerNeuron)
    {
        for (int i = 0; i < numNeurons; ++i)
        {
            neurons.push_back(new Neuron(numInputsPerNeuron));
        }
    }

    // 获取神经元的数量
    size_t size() const
    {
        return neurons.size();
    }

    // 设置神经元的值
    void setNeuronValues(const std::vector<double> &values)
    {
        assert(values.size() == neurons.size());
        for (int i = 0; i < neurons.size(); ++i)
        {
            neurons[i]->setValue(values[i]);
        }
    }

    // 通过索引访问神经元
    Neuron *operator[](int index)
    {
        assert(index >= 0 && index < neurons.size());
        return neurons[index];
    }

    // 通过索引访问神经元（const版本）
    const Neuron *operator[](int index) const
    {
        assert(index >= 0 && index < neurons.size());
        return neurons[index];
    }

    // 前向传播
    void feedForward(const Layer &prevLayer)
    {
        outputCache.clear();
        for (auto &neuron : neurons)
        {
            neuron->feedForward(prevLayer);
            outputCache.push_back(neuron->getOutput());
        }
    }

    // 获取输出值
    std::vector<double> getOutputValues() const
    {
        std::vector<double> outputValues;
        for (const auto &neuron : neurons)
        {
            outputValues.push_back(neuron->getOutput());
        }
        return outputValues;
    }

    // 计算误差
    void calculateErrors(const std::vector<double> &expectedOutput)
    {
        for (int i = 0; i < neurons.size(); ++i)
        {
            neurons[i]->calculateOutputGradient(expectedOutput[i]);
        }
    }

    // 更新权重
    void updateWeights(double learningRate)
    {
        for (auto &neuron : neurons)
        {
            neuron->updateInputWeights(learningRate);
        }
    }

    // 获取预测的类别索引
    int getPredictedClassIndex() const
    {
        auto maxElementIter = std::max_element(outputCache.begin(), outputCache.end());
        return std::distance(outputCache.begin(), maxElementIter);
    }
};

void Neuron::feedForward(const Layer &prevLayer)
{
    double sum = 0.0;
    for (int i = 0; i < prevLayer.size(); ++i)
    {
        sum += prevLayer[i]->getOutput() * weights[i];
    }
    output = activationFunction(sum);
}

class NeuralNetwork
{
private:
    std::vector<Layer *> layers; // 神经网络的层
    double learningRate = 0.01;  // 学习率

public:
    // 添加一层到神经网络
    void addLayer(Layer *layer)
    {
        layers.push_back(layer);
    }

    // 前向传播
    std::vector<double> feedForward(const std::vector<double> &input)
    {
        layers[0]->setNeuronValues(input);
        for (int i = 1; i < layers.size(); ++i)
        {
            layers[i]->feedForward(*layers[i - 1]);
        }
        return layers.back()->getOutputValues();
    }

    // 反向传播
    void backPropagation(const std::vector<double> &expectedOutput)
    {
        int lastLayerIndex = layers.size() - 1;
        layers[lastLayerIndex]->calculateErrors(expectedOutput);
        layers[lastLayerIndex]->updateWeights(learningRate);

        for (int i = lastLayerIndex - 1; i >= 0; --i)
        {
            layers[i]->calculateErrors(layers[i + 1]->getOutputValues());
            layers[i]->updateWeights(learningRate);
        }
    }

    // 计算准确率
    double getAccuracy(std::vector<std::vector<double>> &data, std::vector<std::vector<double>> &labels)
    {
        int correctCount = 0;
        for (int i = 0; i < data.size(); ++i)
        {
            std::vector<double> output = feedForward(data[i]);
            int predicted = std::distance(output.begin(), std::max_element(output.begin(), output.end()));
            int actual = std::distance(labels[i].begin(), std::max_element(labels[i].begin(), labels[i].end()));
            if (predicted == actual)
            {
                ++correctCount;
            }
        }
        return static_cast<double>(correctCount) / data.size();
    }
};

NeuralNetwork trainNeuralNetwork(std::vector<std::vector<double>> &trainData, std::vector<std::vector<double>> &trainLabels)
{
    // 初始化神经网络
    NeuralNetwork nn;
    nn.addLayer(new Layer(784, 128)); // 输入层
    nn.addLayer(new Layer(128, 10));  // 输出层

    // 分割训练集和验证集
    int validSize = trainData.size() / 10; // 使用训练集的10%作为验证集
    std::vector<std::vector<double>> validData(trainData.end() - validSize, trainData.end());
    std::vector<std::vector<double>> validLabels(trainLabels.end() - validSize, trainLabels.end());
    trainData.resize(trainData.size() - validSize);
    trainLabels.resize(trainLabels.size() - validSize);

    // 训练神经网络
    for (int epoch = 0; epoch < 100; ++epoch)
    { // 训练100个epoch
        for (int i = 0; i < trainData.size(); ++i)
        {                                       // 对每个训练样本
            nn.feedForward(trainData[i]);       // 前向传播
            nn.backPropagation(trainLabels[i]); // 反向传播

            // 每训练100个样本，输出一次准确率
            if (i % 100 == 0)
            {
                double accuracy = nn.getAccuracy(validData, validLabels);
                std::cout << "Epoch: " << epoch << " Sample: " << i << " Accuracy: " << accuracy << std::endl;
            }
        }
    }

    return nn;
}

double testNeuralNetwork(NeuralNetwork &nn, std::vector<std::vector<double>> &testData, std::vector<std::vector<double>> &testLabels)
{
    // 使用测试数据计算准确率
    double accuracy = nn.getAccuracy(testData, testLabels);

    return accuracy;
}

int main()
{
    // 加载训练数据和测试数据
    std::vector<std::vector<double>> trainData, trainLabels, testData, testLabels;
    loadMNISTData("data/train-images-idx3-ubyte", trainData);
    loadMNISTData("data/train-labels-idx1-ubyte", trainLabels);
    loadMNISTData("data/t10k-images-idx3-ubyte", testData);
    loadMNISTData("data/t10k-labels-idx1-ubyte", testLabels);

    NeuralNetwork nn = trainNeuralNetwork(trainData, trainLabels);
    double testAccuracy = testNeuralNetwork(nn, testData, testLabels);
    std::cout << "Test Accuracy: " << testAccuracy << std::endl;
}
