#include "stdafx.h"
#include "omp.h"
#include <iostream>
using namespace std;



int* row_product(int** a, int* b, int m, int n, unsigned int threads_num)
{
	int* result = new int[m];
	for (int i = 0; i < m; i++)
	{
		result[i] = 0;
	}
#pragma omp parallel shared(a, b, result) num_threads(threads_num)
	{
#pragma omp for nowait
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				result[i] += a[i][j] * b[j];
			}
		}
	}
	return result;
}

int* column_product(int** a, int* b, int m, int n, unsigned int threads_num)
{
	int* result = new int[m];
	for (int i = 0; i < m; i++)
	{
		result[i] = 0;
	}
#pragma omp parallel shared(a, b, result) num_threads(threads_num)
	{
#pragma omp for
		for (int j = 0; j < n; j++)
		{
			for (int i = 0; i < m; i++)
			{
				result[i] += a[i][j] * b[j];
			}
		}
	}
	return result;
}

int* block_product(int** a, int* b, int m, int n, unsigned int threads_num)
{
	int* result = new int[m];
	for (int i = 0; i < m; i++)
	{
		result[i] = 0;
	}
#pragma omp parallel shared(a, b, result) num_threads(threads_num)
	{
		int s = omp_get_num_threads();
		int q = s;
		int block_height = m / s;
		int block_width = n / q;

#pragma omp for
		for (int block_count = 0; block_count < s*q; block_count++)
		{
			int i = block_count / q;
			int j = block_count % q;
			for (int k = i*block_height; k < (i + 1) * block_height; k++)
				for (int l = j*block_width; l < (j + 1) * block_width; l++)
					result[k] += a[k][l] * b[l];
		}
	}
	return result;
}




int main()
{
	

	int max_threads_number = 16;
	int max_dimention = 100000;




	for (int threads_number = 1; threads_number < max_threads_number + 1; threads_number *= 2)
	{
		cout << "Threads number: " << threads_number << endl;
		for (int dimention = 12; dimention < max_dimention; dimention *= 10)
		{
			cout << "Dimention: " << dimention << endl;
			int m = dimention;
			int n = dimention;
			int** a = new int*[m];
			for (int i = 0; i < m; i++)
			{
				a[i] = new int[n];
				for (int j = 0; j < n; j++)
				{
					a[i][j] = rand() % 10;
					//cout << a[i][j] << " ";
				}
				//cout << endl;
			}
			//cout << endl;
			int* b = new int[n];
			for (int i = 0; i < n; i++)
			{
				b[i] = rand() % 10;
				//cout << b[i] << " ";
			}
			//cout << endl;

			double start1 = omp_get_wtime();
			int* result1 = row_product(a, b, m, n, threads_number);
			double end1 = omp_get_wtime();

			cout << (end1 - start1) * 1000 << endl;

			double start2 = omp_get_wtime();
			int* result2 = column_product(a, b, m, n, threads_number);
			double end2 = omp_get_wtime();

			cout << (end2 - start2) * 1000  << endl;

			double start3 = omp_get_wtime();
			int* result3 = block_product(a, b, m, n, threads_number);
			double end3 = omp_get_wtime();

			cout << (end3 - start3) * 1000 << endl;



			for (int i = 0; i < m; i++)
			{
				delete[] a[i];
			}
			delete[] a;
			delete[] b;
			delete[] result1;
			delete[] result2;
			delete[] result3;
		}


	}


	return 0;
}