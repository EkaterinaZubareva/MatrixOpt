#include "pch.h"

#include <iostream>
#include <ctime>
using namespace std;

int MatrixMult(int **a, const int n, int **b, int **c) {
	int **bT = new int *[n];
	for (int i = 0; i < n; i++) bT[i] = new int[n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			bT[i][j] = b[j][i];
		}
	}
#pragma omp parallel 
#pragma omp for
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			c[i][j] = 0;
			for (int k = 0; k < n; k++) {
				c[i][j] += a[i][k] * bT[j][k];
			}//cout << c[i][j] << " ";
		}//cout << "\n";
	}
		return 0;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	const int size = 1000;
	int **A=new int *[size];
	for (int i = 0; i < size; i++) A[i] = new int [size];
	int **B = new int *[size];
	for (int i = 0; i < size; i++) B[i] = new int[size];
	int **C = new int *[size];
	for (int i = 0; i < size; i++) C[i] = new int[size];
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			A[i][j] = rand() % 100 + 1;
			//cout << A[i][j] << " ";
		}//cout << "\n";
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			B[i][j] = rand() % 100 + 1;
			//cout << B[i][j] << " ";
		}//cout << "\n";
	}
	
	MatrixMult(A, size, B, C);
	
	delete []A;
	delete[]B;
	delete[]C;
	return 0;
}

