#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

Vector* Vector_Create(float x, float y, float z)
{
    Vector* v = (Vector*) malloc(sizeof(Vector));
    v->x = x; v->y = y; v->z = z;
    return v;
}

void Vector_Set(Vector* v, float x, float y, float z)
{
    v->x = x; v->y = y; v->z = z;
    return ;
}

void Vector_Free(Vector* v)
{
    free(v);
    return ;
}

Vector* Vector_Scale(Vector* v, float s)
{
    return Vector_Create(v->x*s, v->y*s, v->z*s);
}

void Vector_ScaleInternal(Vector* v, float s)
{
    v->x *= s; v->y *= s; v->z *= s;
    return;
}

float Vector_Dot(Vector* v1, Vector* v2)
{
    return (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
}

Vector* Vector_Cross(Vector* v1, Vector* v2)
{
    Vector* v3 = Vector_Create(0,0,0);
    v3->x = + (v1->y * v2->z - v1->z * v2->y);
    v3->y = - (v1->x * v2->z - v1->z * v2->x);
    v3->z = + (v1->x * v2->y - v1->y * v2->x);
    return v3;
}

Vector* Vector_Add(Vector* v1, Vector* v2)
{
    return Vector_Create(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
}

Vector* Vector_Sub(Vector* v1, Vector* v2)
{
    return Vector_Create(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
}

void Vector_AddInternal(Vector* v1, Vector* v2)
{
    v1->x += v2->x; v1->y += v2->y; v1->z += v2->z;
    return;
}

void Vector_SubInternal(Vector* v1, Vector* v2)
{
    v1->x -= v2->x; v1->y -= v2->y; v1->z -= v2->z;
    return;
}

float Vector_Magnitude(Vector* v)
{
    return sqrt(Vector_Dot(v,v));
}

char* Vector_GetStr(Vector* v)
{
    static char buffer[51];
    sprintf(buffer,"(%.2f,%.2f,%.2f)",v->x,v->y,v->z);
    return buffer;
}
