#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(const Matrix& datas, const Matrix& labels, std::vector<int> numNodeHidden)
{
    m_numClass = numNodeHidden.at(numNodeHidden.size() - 1);        // Final layer
    // Input Layer
    m_listLayer.push_back(Layer(datas, numNodeHidden.at(0)));
    bool isFinal = false;
    for(int i = 1; i< static_cast<int>(numNodeHidden.size()); ++i)      // ignore input and output layer
    {
        if(i == static_cast<int>(numNodeHidden.size()) - 1)
        {
            isFinal = true;
        }
        m_listLayer.push_back(Layer((m_listLayer.end()-1)->GetActFuncVal(), numNodeHidden.at(i), isFinal));
    }
    Y = labels;
    TransToOneHot(m_numClass);
}


NeuralNetwork::~NeuralNetwork()
{
}


Matrix NeuralNetwork::GetLabels() const
{
    return Y;
}

void NeuralNetwork::TransToOneHot(int numClasses)
{
    if( Y.GetNumRow() != 1)
    {
        std::cout<<"Can't transform this matrix to OneHotLabel";
    }
    else
    {
        Matrix result(numClasses, Y.GetNumCol(), false);
        for(int i=0; i < Y.GetNumCol(); ++i)
        {
            result.SetValue(Y.GetValue(0, i), i, 1.0);
        }
        Y = result;
    }
}

int NeuralNetwork::GetMaxLabels() const
{
    int max_Class = 0;
    for(int i=0; i<Y.GetNumCol(); ++i)
    {
        if(max_Class < Y.GetValue(0, i))
        {
            max_Class = Y.GetValue(0, i);
        }
    }
    return max_Class + 1;
}

void NeuralNetwork::SetLabels(const Matrix& mat)
{
    Y = mat;
    TransToOneHot(m_numClass);
}

void NeuralNetwork::SetLabels(const std::vector<double>& labels)
{
    Y = Matrix(labels);
    TransToOneHot(m_numClass);      //Get one hot
}

int NeuralNetwork::GetNumClass() const
{
    return m_numClass;
}

void NeuralNetwork::CheckAlgorithm() const
{
    std::cout << std::endl << "SIZE: " <<  m_listLayer.size();
    for(int i=0; i< static_cast<int>(m_listLayer.size()); ++i)
    {
        m_listLayer[i].GetWeights().Type();
    }
}
