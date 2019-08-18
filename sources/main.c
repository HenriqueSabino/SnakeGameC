#include <allegro.h>

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

	while (!exit_game)
	{
		if (key[KEY_ESC])
		{
			close_game();
		}

		textout_centre_ex(screen, font, "Hello snake game!", SCREEN_W / 2, SCREEN_H / 2, makecol(255, 255, 255), -1);
	}

	return 0;
}
END_OF_MAIN();