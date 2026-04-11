#include"matrix.h"
#include "stdlib.h"

#define N 3

int main()
{
	float **mat, **trans;

	mat = mat_Create(N);
	trans = mat_Create(N);
	
	mat_Identity(mat, N);
	mat[1][2] = 2;

	mat_Transpose(mat, trans, N);

	mat_Show(mat, N);
	printf("\n");
	mat_Show(trans, N);

	mat_Transpose(trans, trans, N);

	printf("\n");
	mat_Show(trans, N);	
	mat_Transpose(trans, trans, N);

	printf("\n");
	mat_Show(trans, N);	

	mat_Free(mat, N);
	mat_Free(trans, N);

	return 0;
}