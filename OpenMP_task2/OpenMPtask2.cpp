// OpenMPtask5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include "omp.h"
using namespace std;

int main()
{
	int vector_A[100000] = {};
	int vector_B[100000] = {};
	for (int i = 0; i < 100000; i++) {
		vector_A[i] = i % 50;
		vector_B[i] = i % 50;
	}

	int dot_prod = 0;
	int dot_prod_omp = 0;
	system("pause");
	double start = omp_get_wtime();
	for (int i = 0; i <= 100000; i++) {
		dot_prod += vector_A[i] * vector_B[i];


	}
	double end = omp_get_wtime();
	cout << (end - start) * 1000 << endl;
	cout << dot_prod << endl;
	system("pause");

#pragma omp parallel shared	(vector_A, vector_B) reduction(+: dot_prod_omp)
	{
		start = omp_get_wtime();
#pragma omp for 
		for (int i = 0; i <= 100000; i++)
		{
			dot_prod_omp += vector_A[i] * vector_B[i];


		}
		end = omp_get_wtime();
	}
	end = omp_get_wtime();

	cout << (end - start) * 1000 << endl;
	cout << dot_prod_omp << endl;

	system("pause");

	return 0;
}

