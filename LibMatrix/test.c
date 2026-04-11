#include"matrix.h"
#include "stdlib.h"

#define N 3

int main()
{
	float** mat;

	mat = mat_Create(N);
	
	mat_Identity(mat, N);

	mat_Show(mat, N);

	mat_Free(mat, N);

	return 0;
}