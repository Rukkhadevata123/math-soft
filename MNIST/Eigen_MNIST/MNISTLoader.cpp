#include "MNISTLoader.h"
#include <fstream>

MNISTLoader::MNISTLoader(const std::string& imagesPath, const std::string& labelsPath) {
    loadImages(imagesPath);
    loadLabels(labelsPath);
}

std::vector<Eigen::VectorXd> MNISTLoader::getImages() {
    return images;
}

std::vector<int> MNISTLoader::getLabels() {
    return labels;
}

void MNISTLoader::loadImages(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (file.is_open()) {
        int magicNumber = 0, numberOfImages = 0, nRows = 0, nCols = 0;
        file.read((char*)&magicNumber, sizeof(magicNumber));
        magicNumber = reverseInt(magicNumber);
        file.read((char*)&numberOfImages, sizeof(numberOfImages));
        numberOfImages = reverseInt(numberOfImages);
        file.read((char*)&nRows, sizeof(nRows));
        nRows = reverseInt(nRows);
        file.read((char*)&nCols, sizeof(nCols));
        nCols = reverseInt(nCols);
        for (int i = 0; i < numberOfImages; ++i) {
            Eigen::VectorXd image(nRows * nCols);
            for (int r = 0; r < nRows * nCols; ++r) {
                unsigned char temp = 0;
                file.read((char*)&temp, sizeof(temp));
                image[r] = (double)temp;
            }
            images.push_back(image);
        }
    }
}

void MNISTLoader::loadLabels(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (file.is_open()) {
        int magicNumber = 0, numberOfLabels = 0;
        file.read((char*)&magicNumber, sizeof(magicNumber));
        magicNumber = reverseInt(magicNumber);
        file.read((char*)&numberOfLabels, sizeof(numberOfLabels));
        numberOfLabels = reverseInt(numberOfLabels);
        for (int i = 0; i < numberOfLabels; ++i) {
            unsigned char temp = 0;
            file.read((char*)&temp, sizeof(temp));
            labels.push_back((int)temp);
        }
    }
}

int MNISTLoader::reverseInt(int i) {
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8) & 255;
    ch3 = (i >> 16) & 255;
    ch4 = (i >> 24) & 255;
    return ((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}