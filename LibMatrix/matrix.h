#include "stdio.h"

typedef struct{
	int row;
	int col;
	float **mat;
}Matrix ;
Matrix mat_Default();//ROBUSTO
void mat_Create(Matrix*);//ROBUSTO
void mat_Copy(Matrix*, Matrix*);//ROBUSTO
void mat_Show(Matrix*);//ROBUSTO
void mat_Free(Matrix*);//ROBUSTO
void mat_Identity(Matrix*);//ROBUSTO
void mat_Transpose(Matrix*, Matrix*);//ROBUSTO
void mat_Multiplication(Matrix*, Matrix*, Matrix*);//ROBUSTO
void mat_Inverse(Matrix *, Matrix*);

