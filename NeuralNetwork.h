#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "Layer.h"

class NeuralNetwork
{
private:

    std::vector<Layer> m_listLayer;
    int m_numClass;
    double m_eta;
    Matrix X;
    Matrix Y;       // [d(l), 1] It's a vector with d(l) elements
    void TransToOneHot(int numClasses);

public:
    NeuralNetwork(const Matrix& datas, const Matrix& labels, std::vector<int> numNodeHidden);
	~NeuralNetwork();
    Matrix GetLabels() const;
    void CheckAlgorithm() const;
    int GetMaxLabels() const;
    int GetNumClass() const;
    void SetLabels(const Matrix& mat);
    void SetLabels(const std::vector<double>& labels);
    void CalFeedForward();
    void CalBackpropa();
    double GetCost();
    void Train(int numStep, double eta);
};

#endif
