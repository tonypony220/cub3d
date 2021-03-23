/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 21:15:35 by mehtel            #+#    #+#             */
/*   Updated: 2021/03/23 21:16:08 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		fill_half_screen(t_vars *vars, int which_half, int color)
{
	int		x;
	int		y;
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

int			only_symbols(char *symbols, char *line)
{
	while (*line)
	{
		if (!ft_strchr(symbols, *line++))
			return (0);
	}
	return (1);
}

/*
** count number of chars in string
*/

int			strchrs(char *str, char c)
{
	int		counter;

	counter = 0;
	while (*str)
	{
		if (*str == c)
			counter++;
		str++;
	}
	return (counter);
}

void		wtf_it_must_be_done_that_way(char **tex_ids)
{
	tex_ids[NO] = "NO";
	tex_ids[SO] = "SO";
	tex_ids[WE] = "WE";
	tex_ids[EA] = "EA";
	tex_ids[S] = "S";
	tex_ids[F] = "F";
	tex_ids[C] = "C";
}
