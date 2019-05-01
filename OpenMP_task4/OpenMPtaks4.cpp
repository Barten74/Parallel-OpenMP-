// OpenMPtask4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include "omp.h"
using namespace std;

int main()
{
	const int n = 200;
	const int m = n;
	int matrix_1[n][m];
	int matrix_2[n][m];
	int matrix_ans[n][m];
	int sum = 0;
	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < m; j++)
		{
			matrix_1[i][j] = i + j;
			matrix_2[i][j] = i - j;
			matrix_ans[i][j] = 0;
		}
	}


	double start = omp_get_wtime();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			sum = 0;
			for (int q = 0; q < n; q++)
			{
				sum += matrix_1[i][q] * matrix_2[q][j];
			}
			matrix_ans[i][j] = sum;
		}
	}
	double end = omp_get_wtime();
	cout << "Without parallel, time: " << (end - start) * 1000 << endl;


	cout << "Matrix Answer: " << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			// Вывод матрицы на экран
			//cout << matrix_ans[i][j] << " ";
			matrix_ans[i][j] = 0;
		}
		//cout << endl;
	}




	
#pragma omp parallel private(i,j,q) shared(matrix_ans, matrix_1, matrix_2) reduction(+: sum)
	{
		start = omp_get_wtime();
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				sum = 0;
				#pragma omp for  
				for (int q = 0; q < n; q++)
				{
					sum += matrix_1[i][q] * matrix_2[q][j];
				}
				matrix_ans[i][j] = sum;
			}
		}
	}
	end = omp_get_wtime();
	cout << "With parallel, time: " << (end - start) * 1000 << endl;


	cout << "Matrix Answer: " << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			// Вывод матрицы на экран
			//cout << matrix_ans[i][j] << " ";
		}
		//cout << endl;
	}









	return 0;
}

