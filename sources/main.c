#include <allegro.h>
#include <stdio.h>
#include "../headers/vector.h"
#include "../headers/snake.h"
#include "../headers/constants.h"

volatile int exit_game = FALSE;

void close_game()
{
	exit_game = TRUE;
}
END_OF_FUNCTION(close_game);

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

	//Double buffer
	BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);

	Snake snake;
	init_snake(&snake, 4, SCREEN_W / 2, SCREEN_H / 2);

	for (int i = 0; i < snake.parts_size; i++)
	{
		printf("%f, %f\n", snake.parts[i].x, snake.parts[i].y);
	}
	printf("\n");

	update_snake(&snake);
	for (int i = 0; i < snake.parts_size; i++)
	{
		printf("%f, %f\n", snake.parts[i].x, snake.parts[i].y);
	}

	printf("\n");

	Vector newDir;
	newDir.x = 0;
	newDir.y = -1;

	printf("%f, %f\n", snake.dir.x, snake.dir.y);
	change_dir(&snake, newDir);
	printf("%f, %f\n", snake.dir.x, snake.dir.y);

	printf("\n");

	grow(&snake);

	for (int i = 0; i < snake.parts_size; i++)
	{
		printf("%f, %f\n", snake.parts[i].x, snake.parts[i].y);
	}

	update_snake(&snake);

	printf("\n");
	for (int i = 0; i < snake.parts_size; i++)
	{
		printf("%f, %f\n", snake.parts[i].x, snake.parts[i].y);
	}

	while (!exit_game)
	{
		//User input
		if (key[KEY_ESC])
		{
			close_game();
		}

		//Variable updates

		//Drawing
		//slowing the circle velocity

		draw_sprite(screen, buffer, 0, 0);
		clear(buffer);
	}

	return 0;
}
END_OF_MAIN();