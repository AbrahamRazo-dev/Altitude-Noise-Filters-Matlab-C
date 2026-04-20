#include"matrix.h"
#include "stdlib.h"

#define N 3
#define M 2

int main()
{
	Matrix A = mat_Default();

	A.row = 1;
	A.col = N;


	mat_Create(&A);


	mat_Identity(&A);
	//A.mat[0][1] = 3;
	//A.mat[0][2] = 5;
	//A.mat[1][2] = 9;
	//A.mat[1][0] = 10;

	mat_Show(&A);

	mat_Multiplication(&A,&A,&A);

	mat_Show(&A);

	mat_Transpose(&A,&A);

	mat_Show(&A);

	mat_Free(&A);

	return 0;
}