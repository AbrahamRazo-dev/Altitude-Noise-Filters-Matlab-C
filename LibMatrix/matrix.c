#include "matrix.h"
#include "stdlib.h"

Matrix mat_Default()
{
	Matrix mat;
	mat.row = 0;
	mat.col = 0;
	mat.mat = NULL;

	return mat;
}

void mat_Create(Matrix *ptr)
{
	ptr->mat = (float**)malloc(ptr->row * sizeof(float*));

	if(ptr->mat == NULL) return;

	for(int i=0; i< ptr->row; i++)
	{	
		ptr->mat[i] = (float*)calloc(ptr->col, sizeof(float));
		if(ptr->mat[i] == NULL)
		{
            for (int j = 0; j < i; j++) 
            {
            	free(ptr->mat[j]);
            }
            free(ptr->mat);
            return;
        }
	}
}

void mat_Copy(Matrix *original, Matrix *copy)
{
	if(original->mat == copy->mat) return; 
	//No tiene sentido copiar valores de una matriz a si misma

	if(original->row <= 0 || original->col <= 0 || original->mat == NULL) return;
	//validar original
	mat_Free(copy);
	copy->row = original->row;
	copy->col = original->col;
	mat_Create(copy);

	if(copy->mat == NULL) return; //no se pudo crear copy por falta de memoria.

	for(int i = 0; i < original->row; i++)
	{
		for(int j = 0; j < original->col; j++)
		{
			copy->mat[i][j] = original->mat[i][j];
		}
	}
}

void mat_Show(Matrix *ptr)
{
	printf("\n");
	for(int i = 0; i < ptr->row; i++)
	{
		for(int j=0; j < ptr->col; j++)
		{
			printf("%.4f ", ptr->mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void mat_Free(Matrix *ptr)
{
	if(ptr->mat == NULL) return;

	for(int i=0; i< ptr->row; i++)
	{
		if(ptr->mat[i] != NULL)
		{
			free(ptr->mat[i]);
		}
	}
	free(ptr->mat);
	*ptr = mat_Default();
}

void mat_Identity(Matrix *ptr)
{
	if(ptr->col != ptr->row)
	{
		printf("Error. No se puede hacer matriz identidad porque la matriz no es cuadrada\n");
		return;
	}
	for(int i = 0; i < ptr->row; i++)
	{
		for(int j = 0; j < ptr->col; j++)
		{
			ptr->mat[i][j] = 0;
			if(i==j) ptr->mat[i][j] = 1;
		}
	}
}



void mat_Transpose(Matrix *original, Matrix *trans) {

    //1.0 Validar si las matrices existen
    if(original->mat == NULL)
    {
    	printf("La matriz original no existe.\n");
    	return;
    }
    
    //1.1 Validar dimensiones de trans
    if(original->mat != trans->mat && (original->row != trans->col || original->col != trans->row))
    {
		mat_Free(trans);
    }

    //2.0 Validar si la trans existe
    if(trans->mat == NULL)
    {
    	
    	trans->row = original->col;
    	trans->col = original->row;
    	mat_Create(trans);
    	if(trans->mat == NULL) return; //falla de creacion de memoria.
    }

    // Caso 1: Si son matrices distintas, transponemos directo
    if (original->mat != trans->mat)
    {
        for(int i = 0; i < original->row; i++)
        {
            for(int j = 0; j < original->col; j++)
            {
                trans->mat[j][i] = original->mat[i][j];
            }
        }
    }
    else
    {
        Matrix temp = mat_Default();
		mat_Copy(original, &temp);
		mat_Free(trans);
		trans->row = temp.col;
		trans->col = temp.row;
		mat_Create(trans);
        for(int i = 0; i < temp.row; i++)
        {
            for(int j = 0; j < temp.col; j++)
            {
                trans->mat[j][i] = temp.mat[i][j];
            }
        }
        mat_Free(&temp);
    } 
}

void mat_Multiplication(Matrix *A, Matrix *B, Matrix *C)
{
	if(A->col != B->row)//validar dimensiones
	{
		printf("No se puede realizar la multiplicacion. Las dimensiones no coinciden\n");
		return;
	}

	if(C->mat != NULL)//verificar si la matriz resultado (C) ya existe
	{//la matriz ya existe
		if(C->row != A->row || C->col != B->col)
		{//Ya existe la matriz. Corroboramos dimensiones.
			mat_Free(C);
		}
	}
	
	if(C->mat == NULL)
	{
		C->row = A->row;
		C->col = B->col;
		mat_Create(C);
		if(C->mat == NULL) return; //falla en la creacion de memoria.
	}

	float sum = 0;
	for(int i = 0; i < A->row; i++)
	{
		for(int j = 0; j < B->col; j++)
		{
			for(int k = 0; k < A->col; k++)
			{
				sum += A->mat[i][k] * B->mat[k][j];
			}
			C->mat[i][j] = sum;
			sum = 0;
		}
	}

}