#include"matrix.h"
#include "stdlib.h"

#define N 3
#define M 3

int main()
{
	Matrix A = {0, 0, NULL};
	Matrix B = {0, 0, NULL};
	Matrix C = {0, 0, NULL};
	A.row = N;
	A.col = M;
	B.row = N;
	B.col = M;
	C.row = N;
	C.col = M;

	mat_Create(&A);
	mat_Create(&B);

	mat_Identity(&B);
	A.mat[1][2] = 2;
	A.mat[2][1] = 12;
	A.mat[0][2] = 7;

	mat_Multiplication(&A,&B,&C);

	mat_Show(&A);
	mat_Show(&B);
	mat_Show(&C);


	mat_Free(&A);

	return 0;
}