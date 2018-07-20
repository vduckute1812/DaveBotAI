#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

class Matrix
{
private:
	std::vector<std::vector<double>> m_datas;
	int m_numRow;
	int m_numCol;
	void GenerateRandomData(bool isRandom);
public:
    Matrix();
    Matrix(int numRow, int numCol, bool isRandom);
	Matrix(const std::vector<std::vector< double > >& datas);
	Matrix(const Matrix& mat);
	~Matrix();
	int GetNumRow() const;
	int GetNumCol() const;
	void PrintToConsole();
	void SetValue(int r, int c, double data);
    void Type() const;

    Matrix T();
    Matrix Dot(const Matrix& mat);
    Matrix operator*(const Matrix& mat);
	Matrix operator*(const double& alpha);
	Matrix operator+(const Matrix& mat);
    void operator=(const Matrix& mat);

    double GetValue(int r, int c) const;

    friend const std::ostream &operator << (std::ostream &out, const Matrix& mat);
};

#endif
