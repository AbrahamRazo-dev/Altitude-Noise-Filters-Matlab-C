#include"matrix.h"
#include "stdlib.h"

#define N 3
#define M 2

int main()
{
	Matrix A = mat_Default();
	Matrix B = mat_Default();	

	A.row = N;
	A.col = N;
	B.row = N;
	B.col = N;


	mat_Create(&A);
	mat_Create(&B);


	mat_Identity(&A);
	A.mat[0][0] = 2;
	A.mat[1][1] = 5;
	A.mat[2][2] = 9;
	A.mat[0][2] = 10;
	A.mat[2][0] = 7;

	mat_Show(&A);

	mat_Inverse(&A,&A);

	mat_Show(&A);


	mat_Free(&A);
	mat_Free(&B);

	return 0;
}