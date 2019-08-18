#include <allegro.h>
#include "../headers/vector.h"

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
	struct vector pos;
	pos.x = 0;
	pos.y = SCREEN_H / 2;

	while (!exit_game)
	{
		//User input
		if (key[KEY_ESC])
		{
			close_game();
		}

		//Variable updates
		pos.x++;

		//Drawing
		//slowing the circle velocity
		circlefill(buffer, pos.x / 10, pos.y, 50, makecol(255, 0, 0));

		draw_sprite(screen, buffer, 0, 0);
		clear(buffer);
	}

	return 0;
}
END_OF_MAIN();