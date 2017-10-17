#include "sdl2_tools.h"

void	sdl2_put_pixel(t_sdl2_tools *my_sdl2, int color, int x, int y)
{
	my_sdl2->pixels[y * 800 + x] = color;
}