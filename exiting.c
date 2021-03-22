#include "cub3d.h"

int			free_map(t_map *map)
{
	int 	i;

	i = -1;
#if 1
	while (++i < NUM_MAP_PATHS && map->texture_path[i])
	{
		printf("freeing %s path\n", map->texture_path[i]);
		free(map->texture_path[i]);
		map->texture_path[i] = 0;
		printf("%p -> path\n", map->texture_path[i]);
	}
	printf("addr %p\n", map->sprites);
	printf("addr %p\n", map->sprites_dist);
	printf("addr %p\n", map->sprites_order);
	printf("addr %p\n", map->zbuf);
	printf("addr %p\n", map->visited);
	printf("addr %p\n", map->map);

	if (map->sprites)
		free(map->sprites);
	if (map->sprites_dist)
		free(map->sprites_dist);
	if (map->sprites_order)
		free(map->sprites_order);
	if (map->zbuf)
		free(map->zbuf);
	if (map->visited)
		free(map->visited);
	if (map->map)
		free(map->map);
	ft_memset(map, 0, sizeof(t_map));
	printf("addr %p\n", map->sprites);
	printf("addr %p\n", map->sprites_dist);
	printf("addr %p\n", map->sprites_order);
	printf("addr %p\n", map->zbuf);
	printf("addr %p\n", map->visited);
	printf("addr %p\n", map->map);
	free(map);
#endif
	return (0);
}

void		free_texs(t_vars *vars)
{
	int 	tex_num;

	tex_num = -1;
	while (++tex_num < NUM_MAP_PATHS && vars->texs[tex_num])
	{
		if (vars->texs[tex_num]->addr && vars->texs[tex_num]->img)
			mlx_destroy_image(vars->mlx, vars->texs[tex_num]->img);
		else if (vars->texs[tex_num]->addr)
		{
			free(vars->texs[tex_num]->addr);
			free(vars->texs[tex_num]);
			printf("%d tex freed \n", tex_num);
		}
	}
}

int 		cub_exit(t_vars *vars, int exit_code)
{
	if (vars->map)
		free_map(vars->map);
	printf("map free\n");
	free_texs(vars);
	printf("texs free\n");
	if (vars->data)
	{
		mlx_destroy_image(vars->mlx, vars->data->img);
		if (vars->data->buffer)
			free(vars->data->buffer);
		printf("buff free\n");
		free(vars->data);
	}
	printf("img free\n");
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	///if (vars->mlx) ???
	printf("mlx %p\n", vars->mlx);
	if (vars->mlx)
		free(vars->mlx);
	if (exit_code)
	{
		printf(RED);
		printf("ERROR\n");
		printf("errno: '%s'\n", strerror(errno));
		printf(RESET);
	}
	system("leaks run");
	return (exit_code);
}
