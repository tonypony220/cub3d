#include "cub3d.h"

void        pixel_put(t_vars *vars, int x, int y, int color)
{
	char    *dst;

	dst = vars->data->addr + (y * vars->data->line_length + x
			* (vars->data->bits_per_pixel / 8));
	if (x >= 0
		&& y >= 0
		&& x < vars->map->resolution_width
		&& y < vars->map->resolution_hight)
			*(unsigned int*)dst = color;
}