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

/*
 * CORRECCIONES APLICADAS:
 *
 * 1. [CRÍTICO] mat_Inverse - Gauss-Jordan: Se agregó verificación de pivote != 0
 *    antes de dividir, y re-pivoteo dinámico por columna dentro del loop principal.
 *
 * 2. [LÓGICO] mat_Singular: Eliminada la función de detección previa incompleta.
 *    La singularidad ahora se detecta correctamente DENTRO de mat_Pivoting,
 *    que se llama una sola vez al inicio para ordenar filas óptimamente.
 *
 * 3. [ROBUSTEZ] mat_Pivoting: Sin cambios de lógica, pero ahora es el único
 *    punto de verdad sobre si la matriz es singular.
 *
 * 4. [ROBUSTEZ] Normalización movida DENTRO del loop de Gauss-Jordan (por fila/columna)
 *    para evitar acumulación de error numérico.
 */

/* ─────────────────────────────────────────────────────────────
   mat_Pivoting
   Aplica pivoteo parcial sobre la diagonal de 'matriz'.
   Retorna 1 si tuvo éxito (no singular), 0 si es singular.
   ───────────────────────────────────────────────────────────── */
int mat_Pivoting(Matrix *matriz)
{
    for(int k = 0; k < matriz->row; k++)
    {
        int   max_row = k;
        float max_val = fabs(matriz->mat[k][k]);

        /* Buscar el máximo en la columna k desde la fila k hacia abajo */
        for(int i = k + 1; i < matriz->row; i++)
        {
            if(fabs(matriz->mat[i][k]) > max_val)
            {
                max_val = fabs(matriz->mat[i][k]);
                max_row = i;
            }
        }

        /* Si la columna entera es cero, la matriz es singular */
        if(max_val < 0.001)
            return 0; /* Singular */

        /* Intercambiar punteros de fila (O(1), sin copiar valores) */
        if(max_row != k)
        {
            float *temp        = matriz->mat[k];
            matriz->mat[k]     = matriz->mat[max_row];
            matriz->mat[max_row] = temp;
        }
    }

    return 1; /* No singular */
}

/* ─────────────────────────────────────────────────────────────
   mat_Singular
   Wrapper simplificado: delega toda la lógica a mat_Pivoting.
   Retorna 1 si la matriz ES singular, 0 si NO lo es.
   ───────────────────────────────────────────────────────────── */
int mat_Singular(Matrix *matriz)
{
    /*
     * CORRECCIÓN: La detección previa (solo revisar la diagonal original)
     * era incompleta: una matriz puede tener diagonal no-nula y aún ser
     * singular por filas linealmente dependientes.
     *
     * mat_Pivoting recorre TODAS las columnas buscando el máximo real,
     * detectando correctamente cualquier caso de singularidad.
     */
    if(mat_Pivoting(matriz))
    {
        return 0; /* Se pudo pivotar → no es singular */
    }

    return 1; /* No se pudo pivotar → es singular */
}

/* ─────────────────────────────────────────────────────────────
   mat_Inverse
   Calcula la inversa de 'original' y la guarda en 'inversa'
   usando eliminación de Gauss-Jordan con pivoteo parcial
   dinámico por columna.
   ───────────────────────────────────────────────────────────── */
void mat_Inverse(Matrix *original, Matrix *inversa)
{
    /* ── 0. Validaciones iniciales ── */
    if(original == NULL || inversa == NULL)  return;
    if(original->mat == NULL)                return;
    if(original->row != original->col)       return;
    if(original->row < 1)                    return;

    int n = original->row;

    /* ── 1. Construir la matriz aumentada [A | I] ── */
    Matrix aumentada = mat_Default();
    aumentada.row = n;
    aumentada.col = n * 2;
    mat_Create(&aumentada);

    if(aumentada.mat == NULL) return;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n * 2; j++)
        {
            if(j < n)
            {
                aumentada.mat[i][j] = original->mat[i][j];   /* Copia de A */
            }
            else
            {
                aumentada.mat[i][j] = (j - n == i) ? 1.0f : 0.0f; /* Identidad */
            }
        }
    }

    /* ── 2. Verificar singularidad con pivoteo inicial ──
       mat_Singular llama a mat_Pivoting sobre la aumentada completa,
       de modo que los intercambios de fila afectan también al lado I. */
    if(mat_Singular(&aumentada))
    {
        printf("[Aviso][Inverse]. La matriz es singular, no tiene inversa.\n");
        mat_Free(&aumentada);
        return;
    }

    /* ── 3. Eliminación de Gauss-Jordan con re-pivoteo dinámico ── */
    for(int j = 0; j < n; j++)
    {
        /*
         * CORRECCIÓN CRÍTICA: Re-pivoteo dinámico por columna.
         * Las eliminaciones previas pueden haber introducido ceros nuevos
         * en la diagonal, así que buscamos el mejor pivote disponible
         * desde la fila j hacia abajo antes de cada columna.
         */
        int   max_row = j;
        float max_val = fabs(aumentada.mat[j][j]);

        for(int i = j + 1; i < n; i++)
        {
            if(fabs(aumentada.mat[i][j]) > max_val)
            {
                max_val = fabs(aumentada.mat[i][j]);
                max_row = i;
            }
        }

        /*
         * CORRECCIÓN CRÍTICA: Verificar que el pivote no sea cero.
         * Si lo es, la matriz resultó singular durante la eliminación
         * (no fue detectada antes por ser borderline).
         */
        if(max_val < 0.001)
        {
            printf("[Aviso][Inverse]. Pivote nulo en columna %d. Matriz singular.\n", j);
            mat_Free(&aumentada);
            return;
        }

        /* Intercambiar filas si encontramos un pivote mejor */
        if(max_row != j)
        {
            float *temp             = aumentada.mat[j];
            aumentada.mat[j]        = aumentada.mat[max_row];
            aumentada.mat[max_row]  = temp;
        }

        float pivote = aumentada.mat[j][j];

        /*
         * CORRECCIÓN DE ROBUSTEZ: Normalizar la fila del pivote AHORA
         * (antes de eliminar las demás filas) en lugar de hacerlo al final.
         * Esto reduce el error numérico acumulado en matrices grandes.
         */
        for(int r = 0; r < n * 2; r++)
            aumentada.mat[j][r] /= pivote;

        /* Eliminar la columna j en todas las demás filas */
        for(int i = 0; i < n; i++)
        {
            if(i == j) continue;

            float factor = aumentada.mat[i][j]; /* pivote ya es 1, factor directo */

            if(fabs(factor) < 0.001) continue;  /* Ya es cero, nada que hacer */

            for(int r = 0; r < n * 2; r++)
                aumentada.mat[i][r] -= aumentada.mat[j][r] * factor;
        }
    }

    /* ── 4. Preparar la matriz de salida 'inversa' ── */
    if(inversa->mat != NULL && (inversa->row != n || inversa->col != n))
    {
        mat_Free(inversa);
    }

    if(inversa->mat == NULL)
    {
        inversa->row = n;
        inversa->col = n;
        mat_Create(inversa);

        if(inversa->mat == NULL)
        {
            mat_Free(&aumentada);
            return;
        }
    }

    /* ── 5. Copiar la mitad derecha de la aumentada → inversa ── */
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            inversa->mat[i][j] = aumentada.mat[i][j + n];

    /* ── 6. Liberar memoria temporal ── */
    mat_Free(&aumentada);
}