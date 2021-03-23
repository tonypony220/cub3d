/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 19:24:24 by mehtel            #+#    #+#             */
/*   Updated: 2021/03/23 19:24:53 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		combinate_all_moves(char *move)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (++i < 8)
	{
		move[i] = j % 2 - 2 * ((j & 3) == 3 && 1);
		if (i == 3)
			continue;
		j++;
	}
}

void		dfs(t_map *map, char *mv, int x, int y)
{
	int		xx;
	int		yy;
	int		i;

	if (map->invalid)
		return ;
	*(map->visited + x + y * map->width) = 1;
	if (x == 0 || x == (map->width - 1) || y == 0 || y == (map->hight - 1))
		map->invalid++;
	i = -1;
	while (++i < 4)
	{
		xx = x + mv[i];
		yy = y + mv[i + 4];
		if (xx >= 0 && xx < map->width && yy >= 0 && yy < map->hight)
		{
			if (!*(map->visited + xx + yy * map->width)
				&& *(map->map + xx + yy * map->width) == CHAR_OF_EMPTY_SPACE)
				map->invalid++;
			if (!*(map->visited + xx + yy * map->width)
				&& ft_strchr("N02", *(map->map + xx + yy * map->width)))
				dfs(map, mv, xx, yy);
		}
	}
}
