// Assignment_ParallelApp.cpp : This file contains the 'main' function.
// Program execution begins and ends there.
//

#include "Matrix.h"
#include "Trap.h"
#include "OddEvenSorting.h"
#include <iostream>
#include <omp.h>
using namespace std;

void testMatrixVectorMul(int total = 10000, int m = 100, int n = 100);
void testTrapIntegral(int total = 10000, int range = 100, int n = 10000);
void testOddEvenSorting(int total = 10000, int n = 1000);

int main(int argc, char* argv[])
{
	int command = atoi(argv[1]);
	if (command == 1)
	{
		cout << "Running Matrix Vector Multiplication Test...\n";
		if (argc == 4)
			testMatrixVectorMul(10000, atoi(argv[2]), atoi(argv[3]));
		else if (argc == 2)
			testMatrixVectorMul();
		else
			exit(-1);
	}
	else if (command == 2)
	{
		cout << "Running Trap Integral Test...\n";
		if (argc == 4)
			testTrapIntegral(10000, atoi(argv[2]), atoi(argv[3]));
		else if (argc == 2)
			testTrapIntegral();
		else
			exit(-1);
	}
	else if (command == 3)
	{
		cout << "Running Odd Even Sorting Test...\n";
		if (argc == 3)
			testOddEvenSorting(10000, atoi(argv[2]));
		else if (argc == 2)
			testOddEvenSorting();
		else
			exit(-1);
	}
	else
	{
		cerr << "Argument Error.\n\n";
		cerr << "Available Arguments:\n1 - Test Matrix Vector Multiplication.\n";
		cerr << "2 - Test Trap Integral.\n3 - Test Odd Even Sorting.\n";
	}
}

void testMatrixVectorMul(int total, int m, int n)
{
	if (m * n > 100000)
	{
		cerr << "Allocation Failed. m*n: " << m * n << " is too large.\n";
	}
	cout << "m: " << m << ", n:" << n << endl;
	double start_x, end_x, start_y, end_y;
	auto elapse_x = 0.0, elapse_y = 0.0;
	for (int i = 0; i < total; i++)
	{
		Matrix A(m, n, false);
		Matrix x(n, 1, false);

		start_x = omp_get_wtime();
		Matrix y1 = A.mulVec(x, false);
		end_x = omp_get_wtime();

		start_y = omp_get_wtime();
		Matrix y2 = A.mulVec(x);
		end_y = omp_get_wtime();
		//y.printMatrix("y");

		// Check whether the results are reliable.
		if (y1 != y2)
		{
			cerr << "Check failed." << endl;
			exit(-1);
		}

		elapse_x += end_x - start_x;
		elapse_y += end_y - start_y;
	}
	cout << "Mat mul vec. [Sequence] Total time: " << elapse_x * 1000 << "ms" << endl;
	cout << "Mat mul vec. [Sequence] Average time: " << elapse_x * 1000 / total << "ms" << endl << endl;
	cout << "Mat mul vec. [Parallel] Total time: " << elapse_y * 1000 << "ms" << endl;
	cout << "Mat mul vec. [Parallel] Average time: " << elapse_y * 1000 / total << "ms" << endl;
}

void testTrapIntegral(int total, int range, int n)
{
	double start_x, end_x, start_y, end_y;
	auto elapse_x = 0.0, elapse_y = 0.0;
	auto func = [](double x) {return x * x; };
	Trap trap(func);

	cout << "range: " << range << ", #trapezoids: " << n << endl;
	for (auto i = 0; i < total; i++)
	{
		int a = rand() % 100;
		int b = a + range;
		double result_x = 0.0, result_y = 0.0;

		start_x = omp_get_wtime();
		result_x = trap.integral(a, b, n, false);
		end_x = omp_get_wtime();

		start_y = omp_get_wtime();
		result_y = trap.integral(a, b, n);
		end_y = omp_get_wtime();

		// Check whether the results are reliable.
		if (abs(result_y - result_x) > 1)
		{
			cerr << "Check failed." << endl;
			exit(-1);
		}

		elapse_x += end_x - start_x;
		elapse_y += end_y - start_y;
	}
	cout << "Integral func: x*x. [Sequence] Total time: " << elapse_x * 1000 << "ms" << endl;
	cout << "Integral func: x*x. [Sequence] Average time: " << elapse_x * 1000 / total << "ms" << endl;
	cout << "Integral func: x*x. [Parallel] Total time: " << elapse_y * 1000 << "ms" << endl;
	cout << "Integral func: x*x. [Parallel] Average time: " << elapse_y * 1000 / total << "ms" << endl;
}

void testOddEvenSorting(int total, int n)
{
	double start_x, end_x, start_y, end_y;
	auto elapse_x = 0.0, elapse_y = 0.0;

	cout << "list length: " << n << endl;
	for (auto i = 0; i < total; i++)
	{
		OddEvenSorting prob1(n);
		OddEvenSorting prob2(prob1);

		start_x = omp_get_wtime();
		prob1.sort(n, false);
		end_x = omp_get_wtime();

		start_y = omp_get_wtime();
		prob2.sort(n);
		end_y = omp_get_wtime();

		elapse_x += end_x - start_x;
		elapse_y += end_y - start_y;

		// Check whether the results are reliable.
		if (prob1 != prob2)
		{
			cerr << "Check failed." << endl;
			exit(-1);
		}
	}

	cout << "OddEvenSort. [Sequence] Total time: " << elapse_x * 1000 << "ms" << endl;
	cout << "OddEvenSort. [Sequence] Average time: " << elapse_x * 1000 / total << "ms" << endl;
	cout << "OddEvenSort. [Parallel] Total time: " << elapse_y * 1000 << "ms" << endl;
	cout << "OddEvenSort. [Parallel] Average time: " << elapse_y * 1000 / total << "ms" << endl;
}

