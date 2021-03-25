/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 20:35:29 by mehtel            #+#    #+#             */
/*   Updated: 2021/03/23 20:35:41 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				parse_color(char *line, int i, t_map *map)
{
	int			color[3];
	int			k;
	int			com;

	k = -1;
	com = 1;
	ft_memset(color, 0, sizeof(color));
	while (++k < 3)
	{
		while (!((*line <= '9' && *line >= '0') || *line == '-')
				&& *line && (com+= *line == ',') && (com+= *line == '+'))
			line++;
		if (!*line)
			map->invalid |= ERR_COLOR;
		color[k] = ft_atoi(line);
		if ((unsigned int)color[k] > 255)
			map->invalid |= ERR_COLOR;
		while ((*line <= '9' && *line >= '0') && *line)
			line++;
	}
	if (com != 3 || *line)
		map->invalid |= ERR_COLOR;
	if (i == F)
		map->floor_color = create_trgb(0, color[0], color[1], color[2]);
	else if (i == C)
		map->ceiling_color = create_trgb(0, color[0], color[1], color[2]);
	return (0);
}

static void		parse_resolution(char *p, t_map *map)
{
	if (!only_symbols("123456890 \t", p))
		map->invalid |= ERR_RES;
	while (*p > '9' && *p < '0')
		p++;
	map->resolution_width = ft_atoi(p);
	while (*p <= '9' && *p >= '0')
		p++;
	map->resolution_hight = ft_atoi(p);
}

void			parse_line(char *line, t_map *map)
{
	char		*p;
	int			i;
	static char *identifiers[NUM_PARAMS];

	if (!identifiers[0])
		wtf_it_must_be_done_that_way(identifiers);
	i = -1;
	while (++i < 8)
	{
		if ((p = ft_strnstr(line, identifiers[i], 2))
			&& !((map->path_provided & (1 << i)) && (map->invalid |= ERR_DBL)))
		{
			map->path_provided |= (1 << i);
			if (i < 5)
				map->texture_path[i] = ft_strtrim(p + 2, " ");
			else if (i == R)
				parse_resolution(p + 1, map);
			else
				parse_color(p + 1, i, map);
			return ;
		}
	}
}

void			fill_map(t_map *map, char *line)
{
	static int	line_number;
	char		symbol_to_put;
	int			i;

	i = 0;
	while (line[i])
	{
		symbol_to_put = ft_strchr("\t ", line[i]) ? EMPTY_CHR : line[i];
		if (ft_strchr("NSWE", symbol_to_put) && !check_respawn(map))
		{
			map->respawn[X] = i;
			map->respawn[Y] = line_number;
			map->respawns = symbol_to_put;
		}
		else if (symbol_to_put == '2')
		{
			map->sprites[map->sprite_counter].cord[X] = i + 0.5;
			map->sprites[map->sprite_counter].cord[Y] = line_number + 0.5;
			map->sprite_counter--;
		}
		*(map->map + i++ + line_number * map->width) = symbol_to_put;
	}
	while (i < map->width)
		*(map->map + i++ + line_number * map->width) = EMPTY_CHR;
	line_number++;
}

/*
** for correct index filling
*/

void			parse_map(char *filename, t_map *map, int *var)
{
	int			fd;
	char		*line;
	int			tmp_sprite_num;

	line = NULL;
	var[COUNTER] = 0;
	tmp_sprite_num = map->sprite_counter;
	map->sprite_counter--;
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (var[COUNTER] < var[NUMBER_LINE_MAP_FROM] && ft_strlen(line) > 1)
				parse_line(line, map);
		else if (var[COUNTER] >= var[NUMBER_LINE_MAP_FROM]
		&& (ft_strlen(line) > 1 || (map->invalid |= ERR_MAP)))
			fill_map(map, line);
		free(line);
		var[COUNTER]++;
	}
	free(line);
	close(fd);
	map->sprite_counter = tmp_sprite_num;
}
