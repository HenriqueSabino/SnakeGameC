#include "../headers/keyboard.h"

void keyboard_input()
{
    for (int i = 0; i < KEY_MAX; i++)
    {
        p_keys[i] = key[i];
    }

    poll_keyboard();
}

int key_down(int k)
{
    return !p_keys[k] && key[k];
}

int key_up(int k)
{
    return p_keys[k] && !key[k];
}

int key_holding(int k)
{
    return p_keys[k] && key[k];
}