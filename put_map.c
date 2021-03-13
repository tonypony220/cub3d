#include "cub3d.h"

int color_by_symbol(char val)
{
	if (val == '2')
		return (0xdeeddd);
	else if (val == CHAR_OF_EMPTY_SPACE)
		return (0x404040);
	else if (val == ' ')
		return (0x000000);
	else if (val == '1')
		return (0xf5f5f5);
	else if (val == '0')
		return (0x000005);
	return (0x888888);

}

void put_map(t_vars *vars)
{
	int		j = -1;
	char	val;
	int 	i;

	while (++j < vars->map->hight)
	{
		i = -1;
		while (++i < vars->map->width)
		{
			val = *(vars->map->map + i + (vars->map->width * j));
			pixel_put(vars, i, j, color_by_symbol(val));
		}
	}
}
