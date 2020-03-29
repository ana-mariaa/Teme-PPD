#include <iostream>
#include <omp.h>
#include <time.h>

void create_matrix(int **mat, int rows, int cols);
void create_vector(int *vector, int dim, bool dimForMul_Result);
void multiplyMatrixVector(int **mat, int *vector, int *result, int rows, int cols);
void multiplyMatrixVector_parallel(int **mat, int *vector, int *result, int rows, int cols);

int main()
{
	int rows = 1000;
	int cols = rows;

	int **mat = new int*[rows];
	for (int i = 0; i < rows; ++i)
	{
		mat[i] = new int[cols];
	}

	int dim = rows;
	int *vector = new int[dim];
	int *result = new int[dim];

	//alocare valori matrice / vector / rezultat
	create_matrix(mat, rows, cols);
	create_vector(vector, dim, false);
	create_vector(result, dim, true);

	clock_t startTime = clock();
		multiplyMatrixVector(mat, vector, result, rows, cols);
	clock_t stop = clock();

	std::cout << "Timpul - secvential: " << double(stop - startTime)/CLOCKS_PER_SEC << std::endl;


	//------------------------------------------------- paralel -------------------------------------//
	omp_set_num_threads(10);
	
	clock_t startTime_parallel = clock();
		multiplyMatrixVector_parallel(mat, vector, result, rows, cols);
	clock_t stop_parallel = clock();

	std::cout << "Timpul - paralel: " << double(stop_parallel - startTime_parallel) / CLOCKS_PER_SEC << std::endl;

	
	//dealocare
	for (int i = 0; i < rows; ++i)
	{
		delete[] mat[i];
	} 
	delete[] mat;
	delete[] vector; 
	delete[] result;

}

void create_matrix(int **mat, int rows, int cols)
{
	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < cols; ++c)
		{
			mat[r][c] = rand() % 100;
		}
	}
}

void create_vector(int *vector, int dim, bool dimForMul_Result)
{
	for (int i = 0; i < dim; ++i)
	{
		if (dimForMul_Result)
			vector[i] = 0;
		else
			vector[i] = rand() % 100;
	}
}

void multiplyMatrixVector(int **mat, int *vector, int *result, int rows, int cols)
{
	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < cols; ++c)
		{
			result[r] += mat[r][c] * vector[c];
		}
	}
}

void multiplyMatrixVector_parallel(int **mat, int *vector, int *result, int rows, int cols)
{
#pragma omp parallel 
	{
		int id = omp_get_thread_num();
		int nrThreads = omp_get_num_threads();
		int iStart = id * rows / nrThreads;
		int iEnd = (id + 1)*rows / nrThreads;

		for (int i = iStart; i < iEnd; ++i)
		{
			for (int c = 0; c < cols; ++c)
			{
				result[i] += mat[i][c] * vector[c];
			}
		}
	}
}