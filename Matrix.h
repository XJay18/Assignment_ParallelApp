#pragma once
#ifndef Matrix_H
#define Matrix_H
#include <iostream>
using namespace std;

class Matrix
{
private:
	double* val = NULL;
	int m = 0;
	int n = 0;

	void readMatrix(
		const string& prompt  /* in */
	);

public:
	Matrix(string /* title */);

	Matrix(
		int /* m */,
		int /* n */,
		bool = true /* verbose */
	);

	Matrix(
		double* /* matrix values */,
		int /* m */,
		int /* n */
	);

	Matrix(
		string /* title */,
		int /* m */,
		int /* n */
	);


	void printMatrix(
		const string& title /* in */
	);

	Matrix mulVec(
		Matrix other /* in */,
		bool = true /*
					true: parallel
					false: sequential
					*/
	);

	bool operator==(Matrix);
	bool operator!=(Matrix);

};
#endif
