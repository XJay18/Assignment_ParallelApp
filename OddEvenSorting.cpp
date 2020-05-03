#include "OddEvenSorting.h"
#include <omp.h>
using namespace std;


OddEvenSorting::OddEvenSorting(int n, bool random)
{
	this->n = n;
	val = new int[n];
	if (random)
	{
		for (int i = 0; i < n; ++i)
		{
			val[i] = rand() % RMAX;
		}
	}
	else
	{
		cout << "Enter the list:\n";
		for (int i = 0; i < n; ++i)
		{
			cin >> val[i];
		}
	}
}

OddEvenSorting::OddEvenSorting(OddEvenSorting& other)
{
	val = other.val;
	n = other.n;
}

void OddEvenSorting::printList(string title)
{
	int i;

	cout << "The list: " << title << endl;
	cout << "[";
	for (int i = 0; i < n; ++i)
	{
		cout << val[i] << (i == n - 1 ? "" : ", ");
	}
	cout << "]\n";
}

void OddEvenSorting::sort(int n, bool p)
{
	int phase, i, temp;

	if (p)
	{
		int* arr = new int[this->n]; 
		memcpy(arr, val, this->n * sizeof(int));

		for (phase = 0; phase < n; phase++) {
			if ((phase & 1) == 0)
			{ /* Even phase */
#pragma omp parallel for num_threads(4) shared(arr,n) private(i)
				for (i = 1; i < n; i += 2)
					if (arr[i - 1] > arr[i])
					{
						temp = arr[i];
						arr[i] = arr[i - 1];
						arr[i - 1] = temp;
					}
			}
			else
			{ /* Odd phase */
#pragma omp parallel for num_threads(4) shared(arr,n) private(i)
				for (i = 1; i < n - 1; i += 2)
					if (arr[i] > arr[i + 1])
					{
						temp = arr[i];
						arr[i] = arr[i + 1];
						arr[i + 1] = temp;
					}
			}
		}
		val = arr;
	}
	else
	{
		for (phase = 0; phase < n; phase++)
			if (phase % 2 == 0)
			{ /* Even phase */
				for (i = 1; i < n; i += 2)
					if (val[i - 1] > val[i])
					{
						temp = val[i];
						val[i] = val[i - 1];
						val[i - 1] = temp;
					}
			}
			else
			{ /* Odd phase */
				for (i = 1; i < n - 1; i += 2)
					if (val[i] > val[i + 1])
					{
						temp = val[i];
						val[i] = val[i + 1];
						val[i + 1] = temp;
					}
			}
	}
}

bool OddEvenSorting::operator==(OddEvenSorting other)
{
	if (n != other.n)
	{
		return false;
	}
	for (int i = 0; i < n; i++)
	{
		if (val[i] != other.val[i])
		{
			return false;
		}
	}
	return true;
}

bool OddEvenSorting::operator!=(OddEvenSorting other)
{
	return !(*this == other);
}

