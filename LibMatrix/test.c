#include"matrix.h"
#include "stdlib.h"

#define N 3
#define M 2

int main()
{
	Matrix A = mat_Default();
	Matrix B = mat_Default();
	Matrix C = mat_Default();
	A.row = M;
	A.col = M;
	B.row = M;
	B.col = N;
	//C.row = N;
	//C.col = M;

	mat_Create(&A);
	mat_Create(&B);

	mat_Identity(&A);
	B.mat[0][1] = 3;
	B.mat[0][2] = 5;
	B.mat[1][2] = 9;
	B.mat[1][0] = 10;

	mat_Multiplication(&A,&B,&C);

	mat_Show(&A);
	mat_Show(&B);
	mat_Show(&C);


	mat_Free(&A);
	mat_Free(&B);
	mat_Free(&C);

	return 0;
}