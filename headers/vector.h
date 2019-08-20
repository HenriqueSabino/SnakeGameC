#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector
{
    float x;
    float y;
} Vector;

Vector create_vector(float, float);
const Vector UP;
const Vector DOWN;
const Vector LEFT;
const Vector RIGHT;

#endif