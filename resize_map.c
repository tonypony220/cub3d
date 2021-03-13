#include "cub3d.h"

void		fill_square(t_map *map, int x, int y, char *new_map, int times)
{
	int		j;
	int		jj;
	char	val;

	jj = y * times;
	val = *(map->map + x + map->width * y);

	while (jj < (y * times + times))
	{
		j = x * times;
		while (j < (x * times + times))
		{
			*(new_map + j + jj * map->width * times) = val;
			j++;
		}
		jj++;
	}
}

void		resize_map(t_map *map, int times)
{
	char 	*new_map;
	int 	x;
	int 	y;

	new_map = ft_calloc(1, map->width * times * map->hight * times);
	y = -1;
	while (++y < map->hight)
	{
		x = -1;
		while (++x < map->width)
			fill_square(map, x, y, new_map, times);
	}

#if 0
	int		j = -1;
	char	val;
	int 	i;

	while (++j < map->hight * times)
	{
		i = -1;
		while (++i < map->width * times)
		{
			//if (!(new_map + i (map->width * j)))
			val = *(new_map + i + (map->width * j * times));
			if (!val)
				write(1,"*", 1);
			else
				write(1, &val, 1);
				//write(1, new_map + i + (map->width * j * times), 1);
		}
		write(1, "\n", 1);
	}
#endif
	/* delete */
	free(map->map);
	map->map = new_map;
	map->width *= times;
	map->hight *= times;
	map->respawn[X] *= times;
	map->respawn[Y] *= times;
}