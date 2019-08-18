#include "../headers/snake.h"
#include "../headers/constants.h"
#include <stdlib.h>
#include <stdio.h>

void init_snake(struct snake *snake, int size, int x, int y)
{
    snake->parts = malloc(sizeof(Vector) * size);
    for (int i = 0; i < size; i++)
    {
        //sets the body parts one after the other in a line
        snake->parts[i].x = x - i * PIXEL_SIZE;
        snake->parts[i].y = y;
    }

    //sets the snake direction to the left
    snake->parts_size = size;
    snake->dir.x = 1;
    snake->dir.y = 0;
}

void update_snake(Snake *snake)
{

    //the head cannot be updated first
    for (int i = snake->parts_size - 1; i >= 1; i--)
    {
        //updates the body parts positions
        snake->parts[i] = snake->parts[i - 1];
    }

    snake->parts[0].x += snake->dir.x * PIXEL_SIZE;
    snake->parts[0].y += snake->dir.y * PIXEL_SIZE;
}

void change_dir(Snake *snake, Vector new_dir)
{
    //if the new direction is not the current direction reversed
    if ((new_dir.x != 0 && snake->dir.x != -new_dir.x) || (new_dir.y != 0 && snake->dir.y != -new_dir.y))
    {
        snake->dir = new_dir;
    }
}

void grow(Snake *snake)
{
    Vector old[snake->parts_size];
    for (int i = 0; i < snake->parts_size; i++)
    {
        old[i] = snake->parts[i];
    }

    snake->parts_size++;
    free(snake->parts);
    snake->parts = malloc(sizeof(Vector) * snake->parts_size);

    for (int i = 0; i < snake->parts_size - 1; i++)
    {
        snake->parts[i] = old[i];
    }

    //setting the added part to be at the head position, this will be changed in the next update_snake
    snake->parts[snake->parts_size - 1] = snake->parts[0];
}