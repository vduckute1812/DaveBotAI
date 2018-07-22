#include "Layer.h"

Layer::Layer()
{
    m_numDim = 0;
    m_numNodes = 0;
}


// Input layer
Layer::Layer(const Matrix& pointData, int numNextNode, bool isFinal)
{
    m_numDim = pointData.GetNumRow();
    m_numNodes = pointData.GetNumCol();

    X = pointData;
    std::cout << std::endl << "X::: ";
    std::cout << X;

    std::cout << "b::: ";
    b = Matrix(numNextNode, 1, false);
    std::cout << b;

    std::cout << "W::: ";
    W = Matrix(m_numDim, numNextNode, true);
    std::cout << W;

    std::cout << "Z::: ";
    Z = W.T().Dot(X) + b;       // Z = W_T.X + B
    std::cout << Z;

    std::cout << "A::: ";
    if(isFinal)
        A = SoftMax(Z);
    else{
        A = ReLuFunc(Z);
    }
    std::cout << A;
}

void Layer::SetBias(const Matrix& mat)
{
    b = mat;
}

void Layer::SetDatas(const Matrix& mat)
{
    X = mat;
}

void Layer::SetWeights(const Matrix& mat)
{
    W = mat;
}

void Layer::SetNumNode(int numNode)
{
    m_numNodes = numNode;
}

Matrix Layer::GetBias() const
{
    return b;
}

Matrix Layer::GetDatas() const
{
    return X;
}

Matrix Layer::GetWeights() const
{
    return W;
}

int Layer::GetNumNode() const
{
    return m_numNodes;
}

Matrix Layer::ReLuFunc(const Matrix& mat)
{
    Matrix result = Matrix(mat.GetNumRow(), mat.GetNumCol(), false);
    double value;

    for(int i =0; i< mat.GetNumRow(); ++i)
    {
        for(int j=0; j< mat.GetNumCol(); ++j)
        {
            value = mat.GetValue(i, j);
            if(value > 0)
            {
                result.SetValue(i, j, value);
            }
        }
    }
    return result;
}



// Stable Softmax
Matrix Layer::SoftMax(const Matrix& mat)
{
    Matrix result = mat;
    result = result - result.MaxMatArr().T();
    std::cout << result;

    double maxValue;

    for(int j =0; j< mat.GetNumCol(); ++j)
    {   maxValue = 0;

        for(int i=0; i< mat.GetNumRow(); ++i)
        {
            result.SetValue(i, j, exp(result.GetValue(i, j)));
            maxValue+=result.GetValue(i, j);
        }

        for(int i=0; i< mat.GetNumRow(); ++i)
        {
            result.SetValue(i, j, result.GetValue(i, j)/maxValue);
        }
    }
    return result;
}

Matrix Layer::GetActFuncVal() const
{
    return A;
}
