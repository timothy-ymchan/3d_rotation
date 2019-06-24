#ifndef _VECTOR_H_
#define _VECTOR_H_

typedef struct {
    float x,y,z;
} Vector;


Vector* Vector_Create(float x, float y, float z);
void Vector_Set(Vector* v, float x, float y, float z);
Vector* Vector_Scale(Vector* v, float s);
void Vector_ScaleInternal(Vector* v, float s);
float Vector_Dot(Vector* v1, Vector* v2);
Vector* Vector_Cross(Vector* v1, Vector* v2);
Vector* Vector_Add(Vector* v1, Vector* v2);
Vector* Vector_Sub(Vector* v1, Vector* v2);
void Vector_AddInternal(Vector* v1, Vector* v2);
void Vector_SubInternal(Vector* v1, Vector* v2);
float Vector_Magnitude(Vector* v);
void Vector_Free(Vector* v);
char* Vector_GetStr(Vector*v);

#endif
