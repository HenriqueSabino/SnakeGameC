#ifndef SNAKE_H
#define SNAKE_H

#include "vector.h"

typedef struct snake
{
    Vector *parts;
    int parts_size;
    Vector dir;
} Snake;

void init_snake(Snake *, int, int, int);
void update_snake(Snake *);
void change_dir(Snake *, Vector);
void grow(Snake *);
int check_death(Snake *, Vector, Vector);

#endif
