/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 19:28:26 by mehtel            #+#    #+#             */
/*   Updated: 2021/03/23 19:30:28 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		find_ray_dir_and_initial_len(t_vars *vars, t_ray *cords)
{
	if (cords->ray_dir[X] < 0)
	{
		cords->move[X] = -1;
		cords->ray_len[X] = (vars->player[X] - cords->on_map[X])
							* cords->delta_len[X];
	}
	else
	{
		cords->move[X] = 1;
		cords->ray_len[X] = (cords->on_map[X] + 1.0 - vars->player[X])
							* cords->delta_len[X];
	}
	if (cords->ray_dir[Y] < 0)
	{
		cords->move[Y] = -1;
		cords->ray_len[Y] = (vars->player[Y] - cords->on_map[Y])
							* cords->delta_len[Y];
	}
	else
	{
		cords->move[Y] = 1;
		cords->ray_len[Y] = (cords->on_map[Y] + 1.0 - vars->player[Y])
							* cords->delta_len[Y];
	}
}

void		cast_ray(t_vars *vars, t_ray *cords)
{
	char	block;

	cords->wall_reached = 0;
	while (cords->wall_reached == 0)
	{
		if (cords->ray_len[X] < cords->ray_len[Y])
		{
			cords->ray_len[X] += cords->delta_len[X];
			cords->on_map[X] += cords->move[X];
			cords->side = X;
		}
		else
		{
			cords->ray_len[Y] += cords->delta_len[Y];
			cords->on_map[Y] += cords->move[Y];
			cords->side = Y;
		}
		block = *(vars->map->map + (int)(cords->on_map[X])
				+ vars->map->width * (int)(cords->on_map[Y]));
		if (block != '0' && block != 'N' && block != '2')
		{
			cords->wall_reached = 1;
		}
	}
}

void		init_player_screen(t_vars *vars, t_ray *cords)
{
	cords->dir[X] = sin(vars->player[RAD]);
	cords->dir[Y] = cos(vars->player[RAD]);
	cords->plane[X] = 0.66 * cos(vars->player[RAD]);
	cords->plane[Y] = -0.66 * sin(vars->player[RAD]);
}

void		init_ray(t_vars *vars, t_ray *cords, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)vars->map->resolution_width - 1;
	cords->ray_dir[X] = cords->dir[X] + cords->plane[X] * camera_x;
	cords->ray_dir[Y] = cords->dir[Y] + cords->plane[Y] * camera_x;
	cords->on_map[X] = (int)(vars->player[X]);
	cords->on_map[Y] = (int)(vars->player[Y]);
	cords->delta_len[X] = fabs(1 / cords->ray_dir[X]);
	cords->delta_len[Y] = fabs(1 / cords->ray_dir[Y]);
}

void		calculate_perp_dist(t_vars *vars, t_ray *cords)
{
	cords->perpWallDist = (cords->on_map[cords->side]
						- vars->player[cords->side]
						+ (1.0 - cords->move[cords->side]) / 2)
						/ cords->ray_dir[cords->side];
}
