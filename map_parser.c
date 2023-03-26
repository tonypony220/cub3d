/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 20:35:29 by mehtel            #+#    #+#             */
/*   Updated: 2021/03/23 21:18:55 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			map_size_parser(char *filename, t_map *map, int *data)
{
	int		res;
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	while ((res = get_next_line(fd, &line)) > 0)
	{
		if (res && !data[NUMBER_LINE_MAP_FROM]
			&& only_symbols("\t 012NSWE", line)
			&& ft_strlen(line) > 2)
			data[NUMBER_LINE_MAP_FROM] = data[COUNTER];
		if (res && data[NUMBER_LINE_MAP_FROM]
			&& map->width < (data[CURRENT_LEN] = ft_strlen(line)))
			map->width = data[CURRENT_LEN];
		if (res && data[NUMBER_LINE_MAP_FROM])
			map->sprite_counter += strchrs(line, '2');
		free(line);
		data[COUNTER]++;
	}
	free(line);
	if (res < 0)
		return (-1);
	close(fd);
	map->hight = data[COUNTER] - data[NUMBER_LINE_MAP_FROM];
	return (data[NUMBER_LINE_MAP_FROM]);
}

int			validate_map_params(t_map *map)
{
	int		i;

	i = -1;
	while (++i < NUM_PARAMS)
	{
		if (!(map->path_provided & (1 << i)) && BEHAVE_HARD
		&& (map->invalid |= ERR_NONE))
			return (0);
		if (i > S)
			continue;
		if (map->path_provided & (1 << i)
		&& (!map->texture_path[i] || ft_strlen(map->texture_path[i]) < 2)
		&& (map->invalid |= ERR_PATH))
		{
			if (BEHAVE_HARD)
				return (0);
			map->path_provided &= (0 << i);
		}
	}
	return (1);
}

int			check_map_parametrs(t_map *map)
{
	if ((map->resolution_width < 1 || map->resolution_hight < 1)
	&& (map->invalid |= ERR_RES))
	{
		if (BEHAVE_HARD)
			return (0);
		map->resolution_width = SCREEN_WIDTH;
		map->resolution_hight = SCREEN_HEIGHT;
	}
	return (1);
}

int			validate_map(t_map *map)
{
	char	mv[8];

	combinate_all_moves(mv);
	dfs(map, mv, map->respawn[X], map->respawn[Y]);
	if (!validate_map_params(map)
	|| !check_map_parametrs(map)
	|| map->invalid)
	{
		return (0);
	}
	return (1);
}

t_map		*map_parser(char *filename, t_vars *vars)
{
	int		var[LEN_VAR_ARRAY];
	t_map	*map;

	if (!(map = ft_calloc(1, sizeof(t_map))))
		exit(cub_exit(vars, 1));
	vars->map = map;
	ft_memset(var, 0, sizeof(var));
	if ((map_size_parser(filename, map, var) < 0 && (map->invalid |= ERR_FILE))
	|| (!var[NUMBER_LINE_MAP_FROM] && (map->invalid |= ERR_MAP)))
		exit(cub_exit(vars, 1));
	if ((!(map->map = ft_calloc(1, map->width * map->hight + 1))
	|| !(map->visited = ft_calloc(1, map->width * map->hight + 1))
	|| !(map->sprites = ft_calloc(sizeof(t_sprite), map->sprite_counter))
	|| !(map->sprites_order = ft_calloc(sizeof(int), map->sprite_counter))
	|| !(map->sprites_dist = ft_calloc(sizeof(double), map->sprite_counter)))
	&& (map->invalid |= ERR_MALLOC))
		exit(cub_exit(vars, 1));
	var[CURRENT_LEN] = var[COUNTER];
	parse_map(filename, map, var);
	if (!validate_map(map)
	|| !(map->zbuf = ft_calloc(sizeof(double), map->resolution_width)))
		exit(cub_exit(vars, 1));
	return (map);
}
