#include <allegro.h>
#include <stdio.h>
#include "../headers/vector.h"
#include "../headers/snake.h"
#include "../headers/constants.h"
#include "../headers/food.h"
#include "../headers/keyboard.h"

volatile int exit_game = FALSE;
volatile long counter = 0;

void close_game()
{
	exit_game = TRUE;
}
END_OF_FUNCTION(close_game);

void increment()
{
	//this increment will be used to determine if it is a frame that updating can be done
	counter++;
}
END_OF_FUNCTION(increment);

void draw_snake(BITMAP *bitmap, Snake snake);
void draw_food(BITMAP *bitmap, Food food);

int main()
{
	allegro_init();
	install_timer();
	install_keyboard();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 600, 500, 0, 0);

	//Attaching a function to the exit button
	LOCK_VARIABLE(exit_program);
	LOCK_FUNCTION(close_program);
	set_close_button_callback(close_game);

	//setting game max fps
	LOCK_VARIABLE(counter);
	LOCK_FUNCTION(increment);
	//this function call increment every 1.0 / FPS seconds
	install_int_ex(increment, MSEC_TO_TIMER(1.0 / FPS * 1000));

	//Double buffer
	BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);

	Snake snake;
	init_snake(&snake, INITIAL_SIZE, SCREEN_W / 2, SCREEN_H / 2);

	//the player's score
	int player_score = 0;
	int game_paused = TRUE;

	Food food;

	int successful = init_food(&food, &snake, create_vector(0, 100), create_vector(SCREEN_W, SCREEN_H));
	//while it was not successful initializing the food, keep trying
	while (!successful)
	{
		successful = init_food(&food, &snake, create_vector(0, 100), create_vector(SCREEN_W, SCREEN_H));
	}

	while (!exit_game)
	{

		clear_to_color(buffer, makecol(BG_COL, BG_COL, BG_COL));
		rectfill(buffer, 0, 0, SCREEN_W, 100, makecol(BG_COL + 20, BG_COL + 20, BG_COL + 20));
		char text[15];

		//Text outputs
		snprintf(text, 15, "Score: %d", player_score);
		textout_ex(buffer, font, text, 0, 0, makecol(255, 255, 255), -1);

		textout_right_ex(buffer, font, "Press P to pause/unpause", SCREEN_W, 0, makecol(255, 255, 255), -1);
		keyboard_input();

		//User input
		if (key_down(KEY_ESC))
		{
			close_game();
		}
		if (key_down(KEY_P))
		{
			game_paused = !game_paused;
		}

		if (!game_paused)
		{

			if (key_down(KEY_W) || key_down(KEY_UP))
			{
				change_next_dir(&snake, UP);
			}
			else if (key_down(KEY_A) || key_down(KEY_LEFT))
			{
				change_next_dir(&snake, LEFT);
			}
			else if (key_down(KEY_S) || key_down(KEY_DOWN))
			{
				change_next_dir(&snake, DOWN);
			}
			else if (key_down(KEY_D) || key_down(KEY_RIGHT))
			{
				change_next_dir(&snake, RIGHT);
			}
		}

		//checking if the counter was incremented to update the game status
		while (counter > 0)
		{
			if (!game_paused)
			{

				if (snake.next_dir.x != snake.dir.x && snake.next_dir.y != snake.dir.y)
				{
					change_dir(&snake);
				}

				//Variable updates
				update_snake(&snake);

				//checking if the passed the boarders or bumped into its tail
				int dead = check_death(&snake, create_vector(0, 100), create_vector(SCREEN_W, SCREEN_H));

				if (dead)
				{
					init_snake(&snake, INITIAL_SIZE, SCREEN_W / 2, SCREEN_H / 2);
					int successful = init_food(&food, &snake, create_vector(0, 100), create_vector(SCREEN_W, SCREEN_H));

					//while it was not successful initializing the food, keep trying
					while (!successful)
					{
						successful = init_food(&food, &snake, create_vector(0, 100), create_vector(SCREEN_W, SCREEN_H));
					}
				}
				else
				{
					check_food_eaten(&food, &snake, create_vector(0, 100), create_vector(SCREEN_W, SCREEN_H));
					player_score = snake.parts_size - INITIAL_SIZE;
				}
			}
			//resetting the counter to zero
			counter--;
		}
		//Drawing

		draw_snake(buffer, snake);
		draw_food(buffer, food);
		draw_sprite(screen, buffer, 0, 0);
	}

	destroy_bitmap(buffer);
	free(snake.parts);

	return 0;
}
END_OF_MAIN();

void draw_snake(BITMAP *bitmap, Snake snake)
{
	for (int i = 0; i < snake.parts_size; i++)
	{
		rectfill(bitmap, snake.parts[i].x, snake.parts[i].y,
				 snake.parts[i].x + PIXEL_SIZE, snake.parts[i].y + PIXEL_SIZE, makecol(255, 255, 255));
		rect(bitmap, snake.parts[i].x, snake.parts[i].y,
			 snake.parts[i].x + PIXEL_SIZE, snake.parts[i].y + PIXEL_SIZE, makecol(BG_COL, BG_COL, BG_COL));
	}
}

void draw_food(BITMAP *bitmap, Food food)
{
	rectfill(bitmap, food.pos.x, food.pos.y,
			 food.pos.x + PIXEL_SIZE, food.pos.y + PIXEL_SIZE, makecol(255, 0, 0));
	rect(bitmap, food.pos.x, food.pos.y,
		 food.pos.x + PIXEL_SIZE, food.pos.y + PIXEL_SIZE, makecol(BG_COL, BG_COL, BG_COL));
}