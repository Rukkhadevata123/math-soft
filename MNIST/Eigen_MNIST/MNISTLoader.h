#include <Eigen/Dense>
#include <vector>
#include <string>

class MNISTLoader {
public:
    MNISTLoader(const std::string& imagesPath, const std::string& labelsPath);

    std::vector<Eigen::VectorXd> getImages();
    std::vector<int> getLabels();

private:
    std::vector<Eigen::VectorXd> images;
    std::vector<int> labels;

    void loadImages(const std::string& path);
    void loadLabels(const std::string& path);
    int reverseInt(int i);
};