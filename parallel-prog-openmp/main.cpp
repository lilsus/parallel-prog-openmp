#include <iostream>
#include <omp.h>
#include <time.h>

#define N 2048

double** generate_matrix() {
	double** matrix = new double* [N];
	
	for (int i = 0; i < N; i++) {
		matrix[i] = new double[N];
		for (int j = 0; j < N; j++) {
			matrix[i][j] = i + j;
		}
	}

	return matrix;
}

void multiply_matrix(double** A, double** B, double** C) {
	#pragma omp parallel for shared(A, B, C)
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			C[i][j] = 0.0;
			for (int k = 0; k < N; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

void main() {
	double** a = generate_matrix();
	double** b = generate_matrix();

	double start_time, end_time;

	for (int t = 1; t <= omp_get_num_procs(); t++) {
		double** c = new double* [N];
		for (int i = 0; i < N; i++) {
			c[i] = new double[N];
		}
		
		omp_set_num_threads(t);
		start_time = omp_get_wtime();
		multiply_matrix(a, b, c);
		end_time = omp_get_wtime();
		std::cout << t << " : " << end_time - start_time << std::endl;
	}
}