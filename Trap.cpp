#include "Trap.h"
#include <iostream>
#include <omp.h>
using namespace std;

Trap::Trap(double (*func)(double))
{
	f = func;
}

double Trap::integral(double a, double b, int n, bool p)
{
	double result = 0.0;
	double h = (b - a) / n;
	int k;

	result = (f(a) + f(b)) / 2.0;

	if (p)
	{
		double sum = result;
#pragma omp parallel for private(k) reduction(+:sum)
		for (k = 1; k <= n - 1; k++)
		{
			sum += f(a + k * h);
		}
		result = sum * h;
	}
	else
	{
		for (k = 1; k <= n - 1; k++)
		{
			result += f(a + k * h);
		}
		result = result * h;
	}

	return result;
}
