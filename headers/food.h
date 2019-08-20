#ifndef FOOD_H
#define FOOD_H

#include "vector.h"
#include "snake.h"

typedef struct food
{
    Vector pos;
} Food;

int init_food(Food *, Snake *, Vector, Vector);
void check_food_eaten(Food *, Snake *, Vector, Vector);

#endif