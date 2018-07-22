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
    Matrix X;       // [N, d]
    Matrix Z;       // [C, d] It's a vector with d(l) elements
    Matrix A;       // [C, d] It's a vector with d(l) elements

    int m_numDim;
    int m_numNodes;

    // Rectified linear unit function (ReLU)
    Matrix ReLuFunc(const Matrix& mat);
    Matrix SoftMax(const Matrix& mat);
public:
    Layer();
    Layer(const Matrix& pointData, int numNextNode, bool isFinal = false);

    void SetBias(const Matrix&);
    void SetDatas(const Matrix&);
    void SetWeights(const Matrix&);
    void SetNumNode(int numNode);

    Matrix GetBias() const;
    Matrix GetDatas() const;
    Matrix GetWeights() const;
    Matrix GetActFuncVal() const;
    int GetNumNode() const;
};

#endif // LAYER_H
