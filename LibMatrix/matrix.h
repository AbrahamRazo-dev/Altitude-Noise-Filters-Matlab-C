#include "stdio.h"

typedef struct{
	int row;
	int col;
	float **mat;
}Matrix ;
void mat_Create(Matrix*);
void mat_Show(Matrix*);
void mat_Free(Matrix*);
void mat_Identity(Matrix*);
void mat_Transpose(Matrix*, Matrix*);
void mat_Multiplication(Matrix*, Matrix*, Matrix*);
void mat_Inverse();

