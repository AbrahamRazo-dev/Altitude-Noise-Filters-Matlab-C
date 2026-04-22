#include "math.h"
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
	if(ptr->row <= 0|| ptr->col <= 0) return; //validar que las dimensiones sean mayores a 0

	ptr->mat = (float**)malloc(ptr->row * sizeof(float*));

	if(ptr->mat == NULL) 
	{
		*ptr = mat_Default();
		return;
	}

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
	if(ptr->mat == NULL)
	{
		printf("[Aviso][Show]. Matriz vacia.\n");
		return;
	}
	if(ptr->col <= 0 || ptr->row <= 0) return;

	printf("\n");
	for(int i = 0; i < ptr->row; i++)
	{
		for(int j=0; j < ptr->col; j++)
		{
			printf("%8.4f ", ptr->mat[i][j]);
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
	if(ptr->col != ptr->row || ptr->col <= 0 || ptr->row <= 0)
	{
		printf("[Error][Identity]. No se puede hacer matriz identidad porque la matriz no es cuadrada.\n");
		return;
	}

	if(ptr->mat == NULL)
	{
		mat_Create(ptr);
		if(ptr->mat == NULL) return;//fallo de creacion de memoria
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
    	printf("[Error][Transpose]. La matriz original no existe.\n");
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
	if(A->col != B->row || A->mat == NULL || B->mat == NULL )//validar dimensiones
	{//mat_Create ya valida que col y row de cada matriz sean mayores a 0
		printf("[Error][Multiplication]. No se puede realizar la multiplicacion. Las dimensiones no coinciden.\n");
		return;
	}

	if(C->mat != NULL && C->mat != A->mat && C->mat != B->mat)//verificar si la matriz resultado (C) ya existe
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
	//Caso donde C es solo A, B es diferente
	if(C->mat == A->mat && C->mat != B->mat)
	{
		Matrix temp = mat_Default();
		mat_Copy(A,&temp);

		for(int i = 0; i < temp.row; i++)
		{
			for(int j = 0; j < B->col; j++)
			{
				for(int k = 0; k < temp.col; k++)
				{
					sum += temp.mat[i][k] * B->mat[k][j];
				}
				C->mat[i][j] = sum;
				sum = 0;
			}
		}
		mat_Free(&temp);
	}
	//Caso donde C es solo B, A es diferente
	else if(C->mat == B->mat && C->mat != A->mat)
	{
		Matrix temp = mat_Default();
		mat_Copy(B,&temp);

		for(int i = 0; i < A->row; i++)
		{
			for(int j = 0; j < temp.col; j++)
			{
				for(int k = 0; k < A->col; k++)
				{
					sum += A->mat[i][k] * temp.mat[k][j];
				}
				C->mat[i][j] = sum;
				sum = 0;
			}
		}
		mat_Free(&temp);
	}
	//Caso donde C es B y A. Es decir A = B = C
	else if(C->mat == B->mat && C->mat == A->mat)
	{
		Matrix temp = mat_Default();
		mat_Copy(A,&temp);

		for(int i = 0; i < temp.row; i++)
		{
			for(int j = 0; j < temp.col; j++)
			{
				for(int k = 0; k < temp.col; k++)
				{
					sum += temp.mat[i][k] * temp.mat[k][j];
				}
				C->mat[i][j] = sum;
				sum = 0;
			}
		}
		mat_Free(&temp);
	}
	//Caso donde ninguna es la misma
	else if(C->mat != A->mat && C->mat != B->mat)
	{
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

}

void mat_Inverse(Matrix *original, Matrix *inversa)
{

	//Matriz Aumentada
	Matrix aumentada = mat_Default();
	aumentada.row = original->row;
	aumentada.col = original->col*2;
	mat_Create(&aumentada);

	for(int i = 0; i < aumentada.row; i++)
	{
		for(int j = 0; j < aumentada.col; j++)
		{
			if(j < original->col)
			{//copiamos matriz original
				aumentada.mat[i][j] = original->mat[i][j];
			}
			else
			{ //hacemos matriz identidad
				if(j - original->col == i)
				{
					aumentada.mat[i][j] = 1;
				}
				else
				{
					aumentada.mat[i][j] = 0;
				}
			}
		}
	}

	//Metodo Gauss Jordan
    float pivote = 0;
    float factor = 0;
    for(int j = 0; j < original->col; j++)
    {
        pivote = aumentada.mat[j][j];
        
        // Iteramos sobre TODAS las filas, no solo las de abajo
        for(int i = 0; i < original->row; i++) 
        {
            if (i == j) continue; // Nos saltamos la fila pivote
            
            if(fabs(aumentada.mat[i][j]) > 0.001)
            {
                factor = -(aumentada.mat[i][j] / pivote);
                
                // Sumar las filas multiplicadas en un solo paso SIN destruir la fila j
                for(int r = 0; r < aumentada.col; r++)
                {
                    aumentada.mat[i][r] += aumentada.mat[j][r] * factor;
                }
            }
        }
    }
	//Normalizar para hacer identidad
	for(int i = 0; i < aumentada.row; i++)
	{
		pivote = aumentada.mat[i][i];
		for(int j = 0; j < aumentada.col; j++)
		{
			aumentada.mat[i][j] = aumentada.mat[i][j]/pivote;
		}
	}

	//Copiar resultado en inversa
	for(int i = 0; i < aumentada.row; i++)
	{
		for(int j = original->col; j < aumentada.col; j++)
		{
			inversa->mat[i][j-original->col] = aumentada.mat[i][j];
		}
	}

	mat_Free(&aumentada);
}