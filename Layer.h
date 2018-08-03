#ifndef LAYER_H
#define LAYER_H
#include "Matrix.h"
#include <math.h>

class Layer
{
private:
    // Z = W.T*X + b
    // A = f(Z)
    Matrix b;       // [C, 1] We separate it in W. It's useful with weight decay way for avoiding overfitting.
    Matrix W;       // [N, C] It's a matrix
    Matrix Z;       // [C, d] It's a vector with d(l) elements
    Matrix A;       // [C, d] It's a vector with d(l) elements

    Matrix E;       // d(J)/d(z)
    Matrix dW;
    Matrix db;

    int m_numPoints;
    int m_numNodes;
    bool m_isFinal;
    int m_indexLayer;

    // Rectified linear unit function (ReLU)
    Matrix ReLuFunc(const Matrix& mat);
    Matrix SoftMax(const Matrix& mat);
public:
    Layer();
    Layer(const Matrix& pointData, int numNextNode, int indexLayer, bool isFinal = false);

    void SetBias(const Matrix&);
    void SetDatas(const Matrix&);
    void SetWeights(const Matrix&);

    Matrix GetBias() const;
    Matrix GetDatas() const;
    Matrix GetWeights() const;
    Matrix GetActFuncVal() const;
    Matrix GetE() const;
    int GetIndexLayer() const;
    // Feedforward
    void FeedForward(const Matrix& pointData);
    // Backpropagation
    void Backpropagation(const Matrix&, const Matrix&,const Matrix&m, double eta);
};

#endif // LAYER_H
