#include "../headers/vector.h"

Vector create_vector(float x, float y)
{
    Vector new = {.x = x, .y = y};
    return new;
}

const Vector UP = {.x = 0, .y = -1};
const Vector DOWN = {.x = 0, .y = 1};
const Vector LEFT = {.x = -1, .y = 0};
const Vector RIGHT = {.x = 1, .y = 0};