#include "cub3d.h"

void		free_map(t_map *map)
{
	int 	i;

	i = -1;
	while (++i < NUM_MAP_PATHS && map->texture_path[i])
		free(map->texture_path[i]);
	if (map->map)
		free(map->map);
	free(map);
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
		}
	}
}

int 		cub_exit(t_vars *vars, int exit_code)
{
	if (vars->map)
		free_map(vars->map);
	free_texs(vars);
	if (vars->data->img)
		mlx_destroy_image(vars->mlx, vars->data->img);
	if (vars->data->buffer)
		free(vars->data->buffer);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	///if (vars->mlx) ???

	if (exit_code)
	{
		printf("ERROR\n");
		printf("errno: '%s'\n", strerror(errno));
	}
	return (exit_code);
}
