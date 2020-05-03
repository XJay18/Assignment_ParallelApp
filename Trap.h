#pragma once
#ifndef TRAP_H
#define TRAP_H
class Trap
{
private:
	double (*f)(double) = nullptr;
public:
	Trap(double(*func)(double));

	double integral(
		double /* lower bound */,
		double /* upper bound */,
		int /* num trapezoids */,
		bool = true /*
					true: parallel
					false: sequential
					*/
	);
};
#endif
