#include "../headers/food.h"
#include "../headers/food.h"
#include "../headers/constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//This method tries to initialize a new position to the food, if it is successful, it return 1, otherwise 0
int init_food(Food *food, Snake *snake, Vector min_pos, Vector max_pos)
{
    int width = max_pos.x - min_pos.x;
    int height = max_pos.y - min_pos.y;

    //making sure the point chosen is within the grid
    width /= PIXEL_SIZE;
    height /= PIXEL_SIZE;

    srand(time(0));
    //picking a random number ranging from [0, width)
    int new_x = rand() % width;
    new_x *= PIXEL_SIZE;
    new_x += min_pos.x;
    //picking a random number ranging from [0, height)
    int new_y = rand() % height;
    new_y *= PIXEL_SIZE;
    new_y += min_pos.y;

    for (int i = 0; i < snake->parts_size; i++)
    {
        //checking if the new position is on the snake tail or head
        if (snake->parts[i].x == new_x && snake->parts[i].y == new_y)
        {
            //if it is, do not update and return 0
            return 0;
        }
    }

    //else update the food position and return 1
    food->pos.x = new_x;
    food->pos.y = new_y;

    return 1;
}

void check_food_eaten(Food *food, Snake *snake, Vector min_pos, Vector max_pos)
{
    //if the snake's head reached the food
    if (food->pos.x == snake->parts[0].x && food->pos.y == snake->parts[0].y)
    {
        //make the snake grow and choose a new position to the food
        grow(snake);

        int successful = init_food(food, snake, min_pos, max_pos);
        while (!successful)
        {
            successful = init_food(food, snake, min_pos, max_pos);
        }
    }
}