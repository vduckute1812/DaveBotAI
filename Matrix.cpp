#include "Matrix.h"

Matrix::Matrix()
{
    this->m_numRow = 0;
    this->m_numCol = 0;
}

void Matrix::GenerateRandomData(bool isRandom)
{
    std::vector<double> tmp_datas;
	double rand_value;
	for (int i = 0; i < m_numRow; i++)
	{
		for (int j = 0; j < m_numCol; j++)
		{
			rand_value = 1.0 / double((rand() % 100 + 1.0));
			if (isRandom)
			{
				tmp_datas.push_back(rand_value);
			}
			else {
				tmp_datas.push_back(0);
			}
		}
		m_datas.push_back(tmp_datas);
		tmp_datas.clear();
	}
}

Matrix::Matrix(int numRow, int numCol, bool isRandom)
{
	m_numRow = numRow;
	m_numCol = numCol;

	GenerateRandomData(isRandom);
}

Matrix::Matrix(const std::vector< double> & data)
{
    m_numRow = 1;
    m_numCol = static_cast<int>(data.size());

    m_datas.push_back(data);
}


Matrix::Matrix(const std::vector<std::vector<double> >& datas)
{
	m_numRow = static_cast<int>(datas.size());
	m_numCol = static_cast<int>(datas[0].size());
	std::vector<double> tmp_datas;
	for (int i = 0; i < m_numRow; i++)
	{
		for (int j = 0; j < m_numCol; j++)
		{
			tmp_datas.push_back(datas[i][j]);
		}
		m_datas.push_back(tmp_datas);
		tmp_datas.clear();
	}
}

Matrix::Matrix(const Matrix & mat)
{
    m_numRow = mat.GetNumRow();
	m_numCol = mat.GetNumCol();
	std::vector<double> tmp_datas;
    for (int i = 0; i < m_numRow; i++)
	{
		for (int j = 0; j < m_numCol; j++)
		{
			tmp_datas.push_back(mat.GetValue(i, j));
		}
		m_datas.push_back(tmp_datas);
		tmp_datas.clear();
	}
}

Matrix::~Matrix()
{
}

void Matrix::SetValue(int r, int c, double data)
{
	m_datas[r][c] = data;
}

double Matrix::GetValue(int r, int c) const
{
    return m_datas[r][c];
}

int Matrix::GetNumRow() const
{
    return m_numRow;
}

int Matrix::GetNumCol() const
{
    return m_numCol;
}

void Matrix::PrintToConsole()
{
    std::cout << std::endl << "=====MATRIX VALUE======" << std::endl;
    for (int i = 0; i < m_numRow; i++)
    {
        for (int j = 0; j < m_numCol; j++)
        {
            std::cout << m_datas[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::Dot(const Matrix& mat) const
{
    Matrix result(this->GetNumRow(), mat.GetNumCol(), false);
    double data;

    if (this->GetNumCol() != mat.GetNumRow())
    {
        std::cout << "Can't dot (" << this->GetNumRow() << ", " << this->GetNumCol()
            << ") * (" << mat.GetNumRow() << ", " << mat.GetNumCol() <<")" << std::endl;
        return result;
    }

    for (int i = 0; i < this->GetNumRow(); i++)
    {
        for (int j = 0; j < this->GetNumCol(); j++)
        {
            for (int k = 0; k < mat.GetNumCol(); k++)
            {
                data = result.GetValue(i, k);
                data += m_datas[i][j] * mat.GetValue(j, k);
                result.SetValue(i, k, data);
            }
        }
    }
    return result;
}

Matrix Matrix::T() const
{
    Matrix result(this->GetNumCol(), this->GetNumRow(), false);

    for(int i=0; i < this->GetNumRow(); ++i)
    {
        for(int j=0; j<this->GetNumCol(); ++j)
        {
            result.SetValue(j, i, m_datas[i][j]);
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix & mat) const
{
    Matrix result(this->GetNumRow(), this->GetNumCol(), false);
    double data;
    if (this->GetNumRow() != mat.GetNumRow() && this->GetNumCol() != mat.GetNumCol())
    {
        std::cout << "Can't multiply (" << this->GetNumRow() << ", " << this->GetNumCol()
            << ") * (" << mat.GetNumRow() << ", " << mat.GetNumCol() <<")" << std::endl;
        return result;
    }

    for(int i=0; i < this->GetNumRow(); ++i)
    {
        for(int j=0; j<this->GetNumCol(); ++j)
        {
            data = m_datas[i][j]*mat.GetValue(i,j);
            result.SetValue(i, j, data);
        }
    }
    return result;
}

Matrix Matrix::operator*(const double & _alpha) const
{
	Matrix result = *this;
	double data;

	for (int i = 0; i < this->GetNumRow(); i++)
	{
		for (int j = 0; j < this->GetNumCol(); j++)
		{
			data = _alpha* result.GetValue(i, j);
			result.SetValue(i, j, data);
		}
	}
	return result;
}

Matrix Matrix::operator+(const Matrix & mat) const
{
	Matrix result(this->GetNumRow(), this->GetNumCol(), false);
	double data;

    if (this->GetNumCol() == mat.GetNumCol() && this->GetNumRow() == mat.GetNumRow())
	{
        for (int i = 0; i < this->GetNumRow(); i++)
        {
            for (int j = 0; j < this->GetNumCol(); j++)
            {
                data = this->m_datas[i][j] + mat.GetValue(i, j);
                result.SetValue(i, j, data);
            }
        }
	}
    else if(mat.GetNumCol()==1)
    {
        for (int i = 0; i < this->GetNumRow(); i++)
        {
            for (int j = 0; j < this->GetNumCol(); j++)
            {
                data = this->m_datas[i][j] + mat.GetValue(i, 0);
                result.SetValue(i, j, data);
            }
        }
    }
    else if(mat.GetNumRow()==1)
    {
        for (int j = 0; j < this->GetNumCol(); j++)
        {
            for (int i = 0; i < this->GetNumRow(); i++)
            {
                data = this->m_datas[i][j] + mat.GetValue(0, j);
                result.SetValue(i, j, data);
            }
        }
    }
    else
    {
        std::cout << "Can't add (" << this->GetNumRow() << ", " << this->GetNumCol()
            << ") * (" << mat.GetNumRow() << ", " << mat.GetNumCol() << ")" << std::endl;
        return result;
    }

	return result;
}

Matrix Matrix::operator-(const Matrix & mat) const
{
    Matrix result(this->GetNumRow(), this->GetNumCol(), false);
    double data;

    if (this->GetNumCol() == mat.GetNumCol() && this->GetNumRow() == mat.GetNumRow())
    {
        for (int i = 0; i < this->GetNumRow(); i++)
        {
            for (int j = 0; j < this->GetNumCol(); j++)
            {
                data = this->m_datas[i][j] - mat.GetValue(i, j);
                result.SetValue(i, j, data);
            }
        }
    }
    else if(mat.GetNumCol()==1)
    {
        for (int i = 0; i < this->GetNumRow(); i++)
        {
            for (int j = 0; j < this->GetNumCol(); j++)
            {
                data = this->m_datas[i][j] - mat.GetValue(i, 0);
                result.SetValue(i, j, data);
            }
        }
    }
    else if(mat.GetNumRow()==1)
    {
        for (int j = 0; j < this->GetNumCol(); j++)
        {
            for (int i = 0; i < this->GetNumRow(); i++)
            {
                data = this->m_datas[i][j] - mat.GetValue(0, j);
                result.SetValue(i, j, data);
            }
        }
    }
    else
    {
        std::cout << "Can't substract (" << this->GetNumRow() << ", " << this->GetNumCol()
            << ") * (" << mat.GetNumRow() << ", " << mat.GetNumCol() << ")" << std::endl;
        return result;
    }

    return result;
}

void Matrix::operator = (const Matrix& mat)
{
    std::vector<double> tmp_datas;

    m_numRow = mat.GetNumRow();
    m_numCol = mat.GetNumCol();
    m_datas.clear();

    for(int i = 0; i < mat.GetNumRow(); ++i )
    {
        for(int j =0; j < mat.GetNumCol(); ++j)
        {
            tmp_datas.push_back(mat.GetValue(i, j));
        }
        m_datas.push_back(tmp_datas);
        tmp_datas.clear();
    }
}

Matrix Matrix::MaxMatArr()
{
    Matrix result = Matrix(GetNumCol(), 1, false);
    double maxValue;
    for(int j=0; j< GetNumCol(); ++j)
    {   maxValue = 0;
        for(int i=0; i< GetNumRow(); ++i)
        {
            if(maxValue <  GetValue(i, j))
            {
                maxValue = GetValue(i, j);
            }
        }
        result.SetValue(j, 0, maxValue);
    }
    return result;
}

void Matrix::Type() const
{
    std::cout << std::endl << "=====MATRIX SHAPE======" << std::endl;
    std::cout << "[" << GetNumRow() << ", " << GetNumCol() << "]" << std::endl;
}

const std::ostream &operator << (std::ostream &out, const Matrix &mat){
    out << std::endl << "=====MATRIX VALUE======" << std::endl;
    out << "[";
    for (int i = 0; i < mat.GetNumRow(); i++)
    {
        out << std::endl << "[";
        for (int j = 0; j < mat.GetNumCol(); j++)
        {
            out << mat.GetValue(i, j) << " ";
        }
        out << "]";
    }
    out << "]" << std::endl;
    return out;
}



Matrix Matrix::Sum(int dim) const
{
    Matrix result;
    double sum;

    if(dim == 0) // X dimention
    {
        result = Matrix(GetNumCol(), 1, false);
        for(int i=0; i< GetNumCol(); ++i)
        {
            sum = 0;
            for (int j=0; j< GetNumRow(); ++j)
            {
                sum += GetValue(j, i);
            }
            result.SetValue(i, 0, sum);
        }
    }
    else if(dim == 1)           // Y dimention
    {
        result = Matrix( GetNumRow(), 1, false);
        for(int i=0; i< GetNumRow(); ++i)
        {
            sum = 0;
            for (int j=0; j< GetNumCol(); ++j)
            {
                sum+= GetValue(i, j);
            }
            result.SetValue(i, 0, sum);
        }
    }
    return result;
}

double Matrix::SumAllElem() const
{
    double sum = 0;
    for(int i=0; i< GetNumRow(); ++i)
    {
        for (int j=0; j< GetNumCol(); ++j)
        {
            sum+=GetValue(i, j);
        }
    }
    return sum;
}

Matrix Matrix::logarit() const
{
    Matrix result(GetNumRow(), GetNumCol(), false);
    for(int i = 0; i < GetNumRow(); ++i)
    {
        for(int j = 0; j < GetNumCol(); ++j)
        {
            result.SetValue(i, j, log(GetValue(i, j)));
        }
    }
    return result;
}
