#include <stdio.h>
#include <malloc.h>

struct Matrix
{
	double* values;
	int rows;
	int cols;
};

struct Matrix create_matrix(int cols, int rows, double* values) {
	struct Matrix newMatrix;
	newMatrix.rows = rows;
	newMatrix.cols = cols;	
	newMatrix.values = malloc(sizeof(double) * rows * cols);
	//newMatrix.values = values;

	//fix later
	for (int i = 0; i < rows * cols; i++) {
		newMatrix.values[i] = values[i];	}
	return newMatrix;

}

void print_matrix(struct Matrix* matrix) {
	int rows = matrix->rows;
	int cols = matrix->cols;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%10.2lf ", matrix->values[i*cols + j]);
		}
		printf("\n\n");
	}
	return;
}

void multiply_by_constant(struct Matrix* matrix, double constant) {
	int rows = matrix->rows;
	int cols = matrix->cols;
	for (int i = 0; i < rows*cols; i++) {
		matrix->values[i] *= constant;
	}
	return;
}

struct Matrix multiply_matrix(struct Matrix* matA, struct Matrix* matB){
	//also fix later

	if (matA->cols != matB->rows) {
		return create_matrix(0, 0, NULL);
	}
	int batchSize = matA->cols;
	int newRows = matA->rows;
	int newCols = matB->cols;
	double* newValues = malloc(sizeof(double) * newRows * newCols);
	for (int row = 0; row < newRows; row++) {
		for (int col = 0; col < newCols; col++) {
			double result = 0;
			
			for (int shift = 0; shift < batchSize; shift++) {
				result += matA->values[(row * matA->cols) + shift] * matB->values[col + (matB->cols*shift)];
			}
			newValues[(newCols * row) + col] = result;
		}
	}
	struct Matrix ret = create_matrix(newCols, newRows, newValues);
	free(newValues);
	return ret;
}

int main(void) {
	/*double test[20] =
	{
		1, 2, 3, 4, 5,
		6, 7, 8, 9, 10,
		11, 12, 13, 14, 15,
		16, 17, 18, 19, 20
	};*/

	double matrixAValues[10] =
	{
		1,
		2,
		3,
		4,
		5,
		6,
		7,
		8,
		9,
		10
	};

	double matrixBValues[10] =
	{
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10
	};

	//struct Matrix testMatrix = create_matrix(5, 4, test);
	struct Matrix matrixA = create_matrix(1, 10, matrixAValues);
	struct Matrix matrixB = create_matrix(10, 1, matrixBValues);

	//printf("===== test matrix =====\n\n");
	//print_matrix(&testMatrix);
	//printf("===== after multiplication =====\n\n");
	//multiply_by_constant(&testMatrix, 21.37);
	//print_matrix(&testMatrix);
	printf("matrix A \n");
	print_matrix(&matrixA);
	printf("matrix B \n");
	print_matrix(&matrixB);

	struct Matrix matrixC = multiply_matrix(&matrixA, &matrixB);
	printf("result of A x B \n");
	print_matrix(&matrixC);


	//stress test

	int size = 10000;
	int area = size * size;

	double* data = malloc(sizeof(double) * area);

	for (int i = 0; i < area; i++) {
		data[i] = i;
	}

	struct Matrix A = create_matrix(size, size, data);
	struct Matrix B = create_matrix(size, size, data);

	struct Matrix C = multiply_matrix(&A, &B);

	free(data);

	print_matrix(&C);

	getchar();

	return 0;
}