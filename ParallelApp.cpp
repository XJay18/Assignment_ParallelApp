// ParallelApp.cpp : This file contains the 'main' function.
// Program execution begins and ends there.
//

#include "Matrix.h"
#include "Trap.h"
#include "OddEvenSorting.h"
#include <iostream>
#include <cmath>
#include <omp.h>

void testMatrixVectorMul(int total = 10000, int m = 500, int n = 500);
void testTrapIntegral(int total = 10000, int range = 100, int n = 1000000);
void testOddEvenSorting(int total = 10000, int n = 1000);

/* Modify 2 lines below if needed */
int num_cores = 5;  // Specify the number of cores
int cores[] = { 1, 2, 4, 6, 8 };  // Specify the sequence of cores to run your test on.

int main(int argc, char* argv[])
{
	int command = atoi(argv[1]);

	if (command == 1)
	{
		std::cout << "Running Matrix Vector Multiplication Test...\n";
		if (argc == 5)
			testMatrixVectorMul(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
		else if (argc == 4)
			testMatrixVectorMul(10000, atoi(argv[2]), atoi(argv[3]));
		else if (argc == 3)
			testMatrixVectorMul(atoi(argv[2]));
		else if (argc == 2)
			testMatrixVectorMul();
		exit(0);
	}
	else if (command == 2)
	{
		std::cout << "Running Trap Integral Test...\n";
		if (argc == 5)
			testTrapIntegral(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
		if (argc == 4)
			testTrapIntegral(10000, atoi(argv[2]), atoi(argv[3]));
		else if (argc == 3)
			testTrapIntegral(atoi(argv[2]));
		else if (argc == 2)
			testTrapIntegral();
		exit(0);
	}
	else if (command == 3)
	{
		std::cout << "Running Odd Even Sorting Test...\n";
		if (argc == 4)
			testOddEvenSorting(atoi(argv[2]), atoi(argv[3]));
		else if (argc == 3)
			testOddEvenSorting(10000, atoi(argv[2]));
		else if (argc == 2)
			testOddEvenSorting();
		exit(0);
	}

	std::cerr << "Argument Error.\n\n";
	std::cerr << "Available Arguments:\n"
		<< "\t1 - Test Matrix Vector Multiplication.\n"
		<< "\t2 - Test Trap Integral.\n\t3 - Test Odd Even Sorting.\n";
	exit(-1);
}

void testMatrixVectorMul(int total, int m, int n)
{
	if (m * n > MAX_MATRIX_SIZE)
	{
		std::cerr << "Allocation Failed. m*n: " << m * n << " is too large.\n";
	}
	std::cout << "Average " << total << " times\n";
	std::cout << "m: " << m << ", n:" << n << "\n\n";

	double start[num_cores], end[num_cores];
	double elapse[num_cores] = { 0.0, 0.0, 0.0, 0.0, 0.0 };

	srand(1); // fixed the random seed
	for (auto i = 0; i < total; i++)
	{
		Matrix A(m, n, false);
		Matrix x(n, 1, false);

#pragma omp barrier
		start[0] = omp_get_wtime();
		A.mulVec(x, false);
#pragma omp barrier
		end[0] = omp_get_wtime();

		elapse[0] += end[0] - start[0];
	}

	std::cout << "Mat mul vec. [Serial]\t\tTotal time: " << elapse[0] * 1000 << "ms\t"
		<< "Average time: " << elapse[0] * 1000 / total << "ms\n\n";

	for (auto i = 1; i < num_cores; i++)
	{
		srand(1); // fixed the random seed
		omp_set_num_threads(cores[i]);
		for (auto j = 0; j < total; ++j)
		{
			Matrix A(m, n, false);
			Matrix x(n, 1, false);

			// for checking the results
			Matrix y1 = A.mulVec(x, false);

#pragma omp barrier
			start[i] = omp_get_wtime();
			Matrix y2 = A.mulVec(x);
#pragma omp barrier
			end[i] = omp_get_wtime();

			// Check whether the results are reliable.
			if (y1 != y2)
			{
				std::cerr << "Check failed." << std::endl;
				exit(-1);
			}
			elapse[i] += end[i] - start[i];
		}

		std::cout << "Mat mul vec. [Parallel " << cores[i] << "]\tTotal time: " << elapse[i] * 1000 << "ms\t";
		std::cout << "Average time: " << elapse[i] * 1000 / total << "ms\n\n";
	}
}

void testTrapIntegral(int total, int range, int n)
{
	std::cout << "Average " << total << " times\n";
	std::cout << "range: " << range << ", #trapezoids: " << n << "\n\n";

	double start[num_cores], end[num_cores];
	double elapse[num_cores] = { 0.0, 0.0, 0.0, 0.0, 0.0 };
	auto func = [](double x) { return x * x; };
	Trap trap(func);

	srand(1);
	for (auto i = 0; i < total; i++)
	{
		int a = rand() % 100;
		int b = a + range;

#pragma omp barrier
		start[0] = omp_get_wtime();
		trap.integral(a, b, n, false);
#pragma omp barrier
		end[0] = omp_get_wtime();

		elapse[0] += end[0] - start[0];
	}

	std::cout << "Integral func: x*x. [Serial]\t\tTotal time: " << elapse[0] * 1000 << "ms\t"
		<< "Average time: " << elapse[0] * 1000 / total << "ms\n\n";

	for (auto i = 1; i < num_cores; i++)
	{
		srand(1); // fixed the random seed
		omp_set_num_threads(cores[i]);
		for (auto j = 0; j < total; j++)
		{
			int a = rand() % 100;
			int b = a + range;


			// for checking the results
			double result_x = trap.integral(a, b, n, false);

#pragma omp barrier
			start[i] = omp_get_wtime();
			double result_y = trap.integral(a, b, n);
#pragma omp barrier
			end[i] = omp_get_wtime();

			// Check whether the results are reliable.
			if (fabs(result_y - result_x) > 1)
			{
				std::cerr << "Check failed." << std::endl;
				exit(-1);
			}
			elapse[i] += end[i] - start[i];
		}
		std::cout << "Integral func: x*x. [Parallel " << cores[i] << "]\tTotal time: " << elapse[i] * 1000 << "ms\t";
		std::cout << "Average time: " << elapse[i] * 1000 / total << "ms\n\n";
	}
}

void testOddEvenSorting(int total, int n)
{
	std::cout << "Average " << total << " times\n";
	std::cout << "list length: " << n << "\n\n";

	double start[num_cores], end[num_cores];
	double elapse[num_cores] = { 0.0, 0.0, 0.0, 0.0, 0.0 };

	srand(1);
	for (auto i = 0; i < total; i++)
	{
		OddEvenSorting prob1(n);

#pragma omp barrier
		start[0] = omp_get_wtime();
		prob1.sort(n, false);
#pragma omp barrier
		end[0] = omp_get_wtime();

		elapse[0] += end[0] - start[0];
	}

	std::cout << "OddEvenSort. [Serial]\t\tTotal time: " << elapse[0] * 1000 << "ms\t"
		<< "Average time: " << elapse[0] * 1000 / total << "ms\n\n";

	for (auto i = 1; i < num_cores; i++)
	{
		srand(1); // fixed the random seed
		omp_set_num_threads(cores[i]);
		for (auto j = 0; j < total; j++)
		{
			OddEvenSorting prob2(n);
			OddEvenSorting prob1(prob2);

			// for checking the results
			prob1.sort(n, false);

#pragma omp barrier
			start[i] = omp_get_wtime();
			prob2.sort(n);
#pragma omp barrier
			end[i] = omp_get_wtime();

			// Check whether the results are reliable.
			if (prob1 != prob2)
			{
				std::cerr << "Check failed." << std::endl;
				exit(-1);
			}
			elapse[i] += end[i] - start[i];
		}
		std::cout << "OddEvenSort. [Parallel " << cores[i] << "]\tTotal time: " << elapse[i] * 1000 << "ms\t";
		std::cout << "Average time: " << elapse[i] * 1000 / total << "ms\n\n";
	}
}
