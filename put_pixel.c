/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 19:27:14 by mehtel            #+#    #+#             */
/*   Updated: 2021/03/23 19:27:16 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->data->addr + (y * vars->data->line_length + x
			* (vars->data->bits_per_pixel / 8));
	if (x >= 0
		&& y >= 0
		&& x < vars->map->resolution_width
		&& y < vars->map->resolution_hight)
		*(unsigned int*)dst = color;
}
