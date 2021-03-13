#include "cub3d.h"

void        pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel /
			8));
	if (x >= 0 && y >= 0 && x < screen_width && y < screen_hight)
		*(unsigned int*)dst = color;
}