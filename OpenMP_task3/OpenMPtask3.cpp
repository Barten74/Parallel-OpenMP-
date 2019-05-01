#include "stdafx.h"
#include "omp.h"
#include <iostream>

using namespace std;



int get_min(int* line, int m)
{
	int min = line[0];
	for (int j = 0; j < m; j++)
	{
		if (line[j] < min)
		{
			min = line[j];
		}
	}
	return min;
}

int max_search(int** array, int n, int m, bool is_parallel)
{
	int* min_elements = new int[n];

#pragma omp parallel if(is_parallel) 
	{
#pragma omp for
		for (int i = 0; i < n; i++)
		{
			min_elements[i] = get_min(array[i], m);
		}
	}

	int max = min_elements[0];
#pragma omp parallel for
	for (int i = 0; i < n; i++)
	{
		if (min_elements[i] > max)
		{
			max = min_elements[i];
		}
	}
	return max;
}



int main()
{
	int n = 10000;
	int m = 10000;
	int** array = new int*[n];
	for (int i = 0; i < n; i++)
	{
		array[i] = new int[m];
		for (int j = 0; j < m; j++)
		{
			array[i][j] = i+j % 100000;
		}
	}

	double start1 = omp_get_wtime();
	double result1 = max_search(array, n, m, false);
	double end1 = omp_get_wtime();

	double start2 = omp_get_wtime();
	double result2 = max_search(array, n, m, true);
	double end2 = omp_get_wtime();

	cout << "result1: " << result1 << endl;
	cout << "Without Parallel: " << (end1 - start1) * 1000 << " microseconds" << endl;

	cout << "result2: " << result2 << endl;
	cout << "With Parallel: " << (end2 - start2) * 1000 << " microseconds" << endl;
	return 0;
}

