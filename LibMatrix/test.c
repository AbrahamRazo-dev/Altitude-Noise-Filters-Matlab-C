#include"matrix.h"
#include "stdlib.h"

#define N 3

int main()
{
	float **mat, **trans, **result;

	mat = mat_Create(N);
	trans = mat_Create(N);
	result = mat_Create(N);
	
	mat_Identity(mat, N);

	mat[0][1] = 2;
	mat[1][2] = 4;	

	mat_Transpose(mat, trans, N);

	mat_Multiplication(mat, trans, result, N, N, N, N);

	mat_Show(mat, N);
	printf("\n");
	mat_Show(trans, N);
	printf("\n");
	mat_Show(result, N);
	printf("\n");

	mat_Free(mat, N);
	mat_Free(trans, N);
	mat_Free(result, N);

	return 0;
}