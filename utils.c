
#include "cub3d.h"
void		fill_half_screen(t_vars *vars, int which_half, int color)
{
	int 	x;
	int 	y;
	int		fill_to;

	x = 0;
	y = -1;
	fill_to = vars->map->resolution_hight / 2;

	if (which_half)
	{
		y = fill_to - 1;
		fill_to = vars->map->resolution_hight;
	}
	while (++y < fill_to)
	{
		while (++x < vars->map->resolution_width)
			pixel_put(vars, x, y, color);
		x = -1;
	}
}

int		only_symbols(char *symbols, char *line)
{
	while (*line)
	{
		if (!ft_strchr(symbols, *line++))
			return (0);
	}
	return (1);
}

int		strchrs(char *str, char c)
/*count number of chars in string */
{
	int counter;

	counter = 0;
	while (*str)
	{
		if (*str == c)
			counter++;
		str++;
	}
	return (counter);
}
