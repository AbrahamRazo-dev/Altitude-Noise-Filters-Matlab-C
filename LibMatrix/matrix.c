#include "matrix.h"
#include "stdlib.h"
//its assumed, every matrix is square. Hence mat[n][n]
float** mat_Create(int n)
{
	float **mat = (float**)malloc(sizeof(float*)*3);

	if(mat == NULL) return NULL;

	for(int i=0; i<n; i++)
	{	
		mat[i] = (float*)malloc(sizeof(float)*3);
		if(mat[i] == NULL)
		{
            for (int j = 0; j < i; j++) free(mat[j]);
            free(mat);
            return NULL;
        }
	}
	return mat;
}

void mat_Show(float** mat, int n)
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			printf("%4f ", mat[i][j]);
		}
		printf("\n");
	}
}

void mat_Free(float** mat, int n)
{
	for(int i=0; i<n; i++)
	{
		free(mat[i]);
	}
	free(mat);
}

void mat_Identity(float **matrix, int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			matrix[i][j] = 0;
			if(i==j) matrix[i][j] = 1;
		}
	}
}

float** mat_Transpose(float **mat, int n)
{
	float **trans = mat_Create(n);

	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			trans[j][i] = mat[i][j];
		}
	}

	return trans;
}