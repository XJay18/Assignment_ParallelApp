#include "Matrix.h"
#include <iostream>
#include <omp.h>
using namespace std;

double VALUES[100000];

Matrix::Matrix(string prompt)
{
	cout << "Initialize for " << prompt << endl;
	cout << "Enter the number of rows\n";
	cin >> m;
	cout << "Enter the number of columns\n";
	cin >> n;
	if (m <= 0 || n <= 0) {
		cerr << "m and n must be positive\n";
		exit(-1);
	}
	val = VALUES;
	readMatrix(prompt);
	cout << endl;
}

Matrix::Matrix(int m, int n, bool verbose)
{
	if (verbose) {
		cout << "Random initialize matrix(vector) with shape:"
			<< "(" << m << ", " << n << ")\n";
	}
	this->m = m;
	this->n = n;
	val = VALUES;
	int i, j;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			val[i * n + j] = rand() % 100;
}

Matrix::Matrix(double* mat, int m, int n)
{
	val = mat;
	this->m = m;
	this->n = n;
}

Matrix::Matrix(string prompt, int m, int n)
{
	this->m = m;
	this->n = n;
	if (m <= 0 || n <= 0) {
		cerr << "m and n must be positive\n";
		exit(-1);
	}
	val = VALUES;
	readMatrix(prompt);
}

void Matrix::readMatrix(const string& prompt)
{
	int i, j;
	cout << (n == 1 ? "Enter the vector " : "Enter the matrix ")
		<< prompt << endl;

	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			cin >> val[i * n + j];
}

void Matrix::printMatrix(const string& title)
{
	int i, j;
	if (n == 1)
	{
		cout << "\nThe vector " << title << endl;
		cout << "[";
		for (i = 0; i < m; i++)
		{
			cout << val[i] << (i == m - 1 ? "" : ", ");
		}
		cout << "]" << endl;
	}
	else
	{
		cout << "\nThe matrix " << title << endl;
		cout << "[";
		for (i = 0; i < m; i++) {
			cout << (i > 0 ? " [" : "[");
			for (j = 0; j < n; j++)
				cout << val[i * n + j] << (j == n - 1 ? "" : ", ");
			cout << (i == m - 1 ? "]]" : "]");
			cout << endl;
		}
	}

}

Matrix Matrix::mulVec(Matrix other, bool p)
{
	int i, j;
	if (other.m != n || other.n != 1)
	{
		cerr << "Size mismatch A: (" << m << ", " << n << ")";
		cerr << " x: (" << other.m << ", " << other.n << ")" << endl;
		exit(-1);
	}
	double* y = new double[m];
	double sum = 0.0;
	if (p)
	{
#pragma omp parallel for num_threads(4) default(none) private(i,j,sum)
		for (i = 0; i < m; i++) {
			sum = 0.0;
			for (j = 0; j < n; j++)
				sum += this->val[i * n + j] * other.val[j];
			y[i] = sum;
		}
	}
	else
	{
		for (i = 0; i < m; i++) {
			y[i] = 0.0;
			for (j = 0; j < n; j++)
				y[i] += this->val[i * n + j] * other.val[j];
		}
	}
	return Matrix(y, m, 1);
}

bool Matrix::operator==(Matrix other)
{
	if (m != other.m || n != other.n)
		return false;
	if (val == NULL && other.val != NULL || val != NULL && other.val == NULL)
		return false;
	for (auto i = 0; i < m; i++)
	{
		for (auto j = 0; j < n; j++)
		{
			if (val[i * n + j] != other.val[i * n + j])
				return false;
		}
	}
	return true;
}

bool Matrix::operator!=(Matrix other)
{
	return !(*this == other);
}


