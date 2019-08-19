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

	LOCK_VARIABLE(counter);
	LOCK_FUNCTION(increment);
	install_int_ex(increment, BPS_TO_TIMER(15));

	//Double buffer
	BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);

	Snake snake;
	init_snake(&snake, 4, SCREEN_W / 2, SCREEN_H / 2);

	while (!exit_game)
	{
		while (counter > 0)
		{
			//User input
			if (key[KEY_ESC])
			{
				close_game();
			}
			if (key[KEY_W])
			{
				change_dir(&snake, UP);
			}
			else if (key[KEY_A])
			{
				change_dir(&snake, LEFT);
			}
			else if (key[KEY_S])
			{
				change_dir(&snake, DOWN);
			}
			else if (key[KEY_D])
			{
				change_dir(&snake, RIGHT);
			}

			//Variable updates
			update_snake(&snake);
			counter--;
		}
		//Drawing

		draw_snake(buffer, snake);
		draw_sprite(screen, buffer, 0, 0);
		clear(buffer);
	}

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