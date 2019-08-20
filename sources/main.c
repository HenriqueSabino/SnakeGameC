#include <allegro.h>
#include <stdio.h>
#include "../headers/vector.h"
#include "../headers/snake.h"
#include "../headers/constants.h"

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

void draw_snake(BITMAP *buffer, Snake snake);

int main()
{
	allegro_init();
	install_timer();
	install_keyboard();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 600, 400, 0, 0);

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

	while (!exit_game)
	{
		//checking if the counter was incremented to update the game status
		while (counter > 0)
		{
			//User input
			if (key[KEY_ESC])
			{
				close_game();
			}
			if (key[KEY_W] || key[KEY_UP])
			{
				change_dir(&snake, UP);
			}
			else if (key[KEY_A] || key[KEY_LEFT])
			{
				change_dir(&snake, LEFT);
			}
			else if (key[KEY_S] || key[KEY_DOWN])
			{
				change_dir(&snake, DOWN);
			}
			else if (key[KEY_D] || key[KEY_RIGHT])
			{
				change_dir(&snake, RIGHT);
			}

			//Variable updates
			update_snake(&snake);

			//checking if the passed the boarders or bumped into its tail
			int dead = check_death(&snake, (Vector){.x = 0, .y = 0}, (Vector){.x = SCREEN_W, .y = SCREEN_H});

			if (dead)
			{
				init_snake(&snake, INITIAL_SIZE, SCREEN_W / 2, SCREEN_H / 2);
			}

			//resetting the counter to zero
			counter--;
		}
		//Drawing

		draw_snake(buffer, snake);
		draw_sprite(screen, buffer, 0, 0);
		clear(buffer);
	}

	destroy_bitmap(buffer);
	free(snake.parts);

	return 0;
}
END_OF_MAIN();

void draw_snake(BITMAP *buffer, Snake snake)
{
	for (int i = 0; i < snake.parts_size; i++)
	{
		rectfill(buffer, snake.parts[i].x, snake.parts[i].y,
				 snake.parts[i].x + PIXEL_SIZE, snake.parts[i].y + PIXEL_SIZE, makecol(255, 255, 255));
		rect(buffer, snake.parts[i].x, snake.parts[i].y,
			 snake.parts[i].x + PIXEL_SIZE, snake.parts[i].y + PIXEL_SIZE, makecol(0, 0, 0));
	}
}