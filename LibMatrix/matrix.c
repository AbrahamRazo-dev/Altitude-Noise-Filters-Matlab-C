#include "matrix.h"
#include "stdlib.h"
//its assumed, every matrix is square. Hence mat[n][n]
float** mat_Create(int n)
{
	float **mat = (float**)malloc(n * sizeof(float*));

	if(mat == NULL) return NULL;

	for(int i=0; i<n; i++)
	{	
		mat[i] = (float*)calloc(n, sizeof(float));
		if(mat[i] == NULL)
		{
            for (int j = 0; j < i; j++) 
            {
            	free(mat[j]);
            }
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

void mat_Transpose(float **mat, float **trans, int n) {
    // Caso 1: Si son matrices distintas, transponemos directo
    if (mat != trans)
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                trans[j][i] = mat[i][j];
            }
        }
    } 
    // Caso 2: Si es la misma matriz, usamos un SWAP
    else
    {
        float temp = 0;
        for(int i=0; i<n; i++)
        {
            for(int j=i+1; j<n; j++)
            {
                temp = mat[i][j];
                mat[i][j] = mat[j][i];
                mat[j][i] = temp;
            }
        }
    }
}

void mat_Multiplication(float **A, float **B, float **C, int colA, int rowA, int colB, int rowB)
{
	if(colA!=rowB)
	{
		printf("No se puede realizar la multiplicacion. Las dimensiones no coinciden\n");
		return;
	}

	float sum = 0;
	for(int i=0; i<rowA; i++)
	{
		for(int j=0; j<colB; j++)
		{
			for(int k=0; k<colA; k++)
			{
				sum += A[i][k] * B[k][j];
			}
			C[i][j] = sum;
			sum = 0;
		}
	}

}