/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 20:06:11 by mehtel            #+#    #+#             */
/*   Updated: 2021/03/23 20:06:45 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*free_map(t_map *map)
{
	int	i;

	i = -1;
	while (++i < NUM_MAP_PATHS && map->texture_path[i])
	{
		free(map->texture_path[i]);
		map->texture_path[i] = 0;
	}
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
	free(map);
	return ((void*)0);
}

void	free_texs(t_vars *vars)
{
	int	tex_num;

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

char 	*err_msg(int err_code)
{
	if (err_code == ERR_COLOR)
		return ("Can't parse color");
	if (err_code == ERR_DBL)
		return ("Parameter seems provided twice");
	if (err_code == ERR_FILE)
		return ("Bad file descriptor");
	if (err_code == ERR_NONE)
		return ("Not all parameters provided");
	if (err_code == ERR_PATH)
		return ("Bad pathway of texture");
	if (err_code == ERR_RES)
		return ("Bad screen resolution");
	if (err_code == ERR_PARAM)
		return ("Unknown parameter");
	if (err_code == ERR_MALLOC)
		return ("Malloc error");
	if (err_code == ERR_RSPWN)
		return ("Must be one respawn");
	if (err_code == ERR_MAP)
		return ("World map not valid");
	if (err_code == ERR_TEX)
		return ("Texture path not correct");
	return ("some error occurred :)");
}

void	put_err_msg(t_vars *vars, int exit_code)
{
	int i;

	if (exit_code)
	{
		printf("%sError\n%s", RED, RESET);
		i = -1;
		while (++i < 13)
		{
			if (vars->map && ((1 << i) & vars->map->invalid))
				printf("%s%s\n%s", RED, err_msg(1 << i), RESET);
		}
		if (exit_code == 2)
			printf("%sBad arguments\n%s", RED, RESET);
	}

}

int		cub_exit(t_vars *vars, int exit_code)
{
	put_err_msg(vars, exit_code);
	if (vars->map)
		free_map(vars->map);
	free_texs(vars);
	if (vars->data)
	{
		mlx_destroy_image(vars->mlx, vars->data->img);
		if (vars->data->buffer)
			free(vars->data->buffer);
		free(vars->data);
	}
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		free(vars->mlx);
	if (LEAKS)
		system("leaks --fullStacks cub3D\n");
	return (exit_code);
}
