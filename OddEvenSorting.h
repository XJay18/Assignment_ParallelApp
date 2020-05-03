#pragma once
#ifndef ODDEVENSORTING_H
#define ODDEVENSORTING_H
#include <iostream>
using namespace std;


class OddEvenSorting
{
private:
	int* val;
	int n;
	const int RMAX = 100;
public:
	OddEvenSorting(
		int /* list length */,
		bool = true /* random initialize */
	);

	// copy constructor
	OddEvenSorting(OddEvenSorting&);

	void printList(string);

	void sort(
		int /* sort length */,
		bool = true /*
					true: parallel
					false: sequential
					*/
	);

	bool operator==(OddEvenSorting);
	bool operator!=(OddEvenSorting);
};
#endif
