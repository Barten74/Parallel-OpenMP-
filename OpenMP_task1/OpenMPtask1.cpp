// OpenMPtask1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include "omp.h"
using namespace std;

int main()
{
	double sum = 0;
	const int n = 100000;
	double start = omp_get_wtime();
	for (int i = 0; i < n; i += 1)
	{
		sum = sum + 4.0 / (1 + (double(i)/n)*(double(i) / n));
	}
	sum = sum/n;
	double end = omp_get_wtime();
	cout << "Without parallel, time: "<< (end - start) * 1000 << endl;
	cout << "Answer: " << sum << endl;


	sum = 0;
	start = omp_get_wtime();
#pragma omp parallel for 
	for (int i = 0; i < n; i += 1)
	{
		sum = sum + 4.0 / (1 + (double(i) / n)*(double(i) / n));
	}
	sum = sum / n;
	end = omp_get_wtime();
	
	cout << "With parallel, time: " << (end - start) * 1000 << endl;
	cout << "Answer: " << sum << endl;

	sum = 0;
#pragma omp parallel reduction(+: sum)
	{
		start = omp_get_wtime();
		#pragma omp for 
		for (int i = 0; i < n; i += 1)
		{
			sum = sum + 4.0 / (1 + (double(i) / n)*(double(i) / n));
		}
		sum = sum / n;
		end = omp_get_wtime();
	}
	cout << "With parallel reduction, time: " << (end - start) * 1000 << endl;
	cout << "Answer: " << sum << endl;
	




	return 0;
}

