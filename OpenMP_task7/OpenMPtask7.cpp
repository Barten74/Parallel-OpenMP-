#include "stdafx.h"
#include "omp.h"
#include <string.h>
#include <iostream>
using namespace std;



int function(const char* string, const char* substring, bool is_parallel)
{
	int result = -1;
#pragma omp parallel shared(string, substring) if(is_parallel)
	{
#pragma omp for
		for (int i = 0; i < strlen(string) - strlen(substring) + 1; i++)
		{
			int matches_count = 0;
			for (int j = 0; j < strlen(substring); j++)
			{
				if (string[i + j] != substring[j])
					break;
				matches_count++;
			}
			if (matches_count == strlen(substring))
			{
				
				result = i;
				
			}
		}
	}
	return result;
}



int main()
{

	auto string = "Donald Trump is considering what could become the most significant and dangerous branding effort of his presidency: labeling the 91-year-old Muslim Brotherhood a terrorist organization.";
	auto substring = "den";

	double start1 = omp_get_wtime();
	int result1 = function(string, substring, false);
	double end1 = omp_get_wtime();

	double start2 = omp_get_wtime();
	int result2 = function(string, substring, true);
	double end2 = omp_get_wtime();

	cout << "result1: " << result1 << endl;

	cout << "Single thread algorithm: " << (end1 - start1) * 1000 << " microseconds * 1000" << endl;

	cout << "result2: " << result2 << endl;

	cout << "Multy thread algorithm: " << (end2 - start2) * 1000 << " microseconds * 1000" << endl;

	return 0;
}