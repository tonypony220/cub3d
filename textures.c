/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 20:25:30 by mehtel            #+#    #+#             */
/*   Updated: 2021/03/23 20:33:58 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			load_textures(t_vars *vars)
{
	char	i;

	i = -1;
	while (++i < NUM_MAP_PATHS)
	{
		if (vars->map->path_provided & (1 << i)
			&& !load_texture(vars, i)
			&& BEHAVE_HARD)
			return (0);
	}
	return (1);
}

int			load_texture(t_vars *vars, int tex_num)
{
	int		w;
	int		h;

	w = 0;
	h = 0;
	vars->texs[tex_num] = ft_calloc(sizeof(t_data), 1);
	if (ft_strnstr(vars->map->texture_path[tex_num], ".png",
				ft_strlen(vars->map->texture_path[tex_num])))
		vars->texs[tex_num]->img = mlx_png_file_to_image(
				vars->mlx, vars->map->texture_path[tex_num], &w, &h);
	else
		vars->texs[tex_num]->img = mlx_xpm_file_to_image(
				vars->mlx, vars->map->texture_path[tex_num], &w, &h);
	if (!vars->texs[tex_num]->img && (vars->map->invalid |= ERR_TEX))
		return (0);
	vars->texs[tex_num]->size[X] = w;
	vars->texs[tex_num]->size[Y] = h;
	vars->texs[tex_num]->addr = mlx_get_data_addr(vars->texs[tex_num]->img,
								&vars->texs[tex_num]->bits_per_pixel,
								&vars->texs[tex_num]->line_length,
								&vars->texs[tex_num]->endian);
	return (1);
}
