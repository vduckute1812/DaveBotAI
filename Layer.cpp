#include "Layer.h"

Layer::Layer()
{
    m_numDim = 0;
    m_numNodes = 0;
}


// Input layer
Layer::Layer(const Matrix& pointData, int numNextNode, bool isFinal)
{
    m_numNodes = pointData.GetNumRow();
    m_numDim = pointData.GetNumCol();

    X = pointData;
    b = Matrix(numNextNode, 1, false);
    W = Matrix(m_numNodes, numNextNode, true);
    Z = W.T().Dot(X) + b;       // Z = W_T.X + B

    if(isFinal){
        A = SoftMax(Z);
    }
    else{
        A = ReLuFunc(Z);
    }
}

void Layer::SetBias(const Matrix& mat)
{
    b = mat;
}

void Layer::Feedforward()
{
    // Update A and Z
    Z = W.T().Dot(X) + b;       // Z = W_T.X + B

    if(isFinal){
        A = SoftMax(Z);
    }
    else{
        A = ReLuFunc(Z);
    }
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
