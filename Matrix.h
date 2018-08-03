#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>

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
    Matrix(const std::vector< double> & data);
    Matrix(const std::vector<std::vector< double > >& datas);
	Matrix(const Matrix& mat);
	~Matrix();
	int GetNumRow() const;
	int GetNumCol() const;
	void PrintToConsole();
	void SetValue(int r, int c, double data);
    Matrix MaxMatArr();

    Matrix T() const;
    Matrix Dot(const Matrix& mat) const;
    Matrix operator*(const Matrix& mat) const;
    Matrix operator*(const double& alpha) const;
    Matrix operator+(const Matrix& mat) const;
    Matrix operator-(const Matrix& mat) const;
    Matrix logarit() const;
    Matrix Sum(int direct) const;
    double SumAllElem() const;
    void operator=(const Matrix& mat);
    double GetValue(int r, int c) const;
    void Type()const;

    friend const std::ostream &operator << (std::ostream &out, const Matrix& mat);
};

#endif
