#include "cub3d.h"

int		only_symbols(char *symbols, char *line)
{
	while (*line)
	{
		if (!ft_strchr(symbols, *line++))
			return (0);
	}
	return (1);
}

int		map_size_parser(char *filename, t_map *map, int *data)
{
	int res;
	int fd;
	char *line;

	//ft_memset(data, 0, sizeof(data));
	write(1, "size\n", 5);
	res = 1;
	fd = open(filename, O_RDONLY);
	while (res > 0)
	{
		res = get_next_line(fd, &line);
		if (res < 0)
		{
			printf("ERROR >> %s\n", strerror(errno));
			return (-1);
			// TODO
		}
		if (res
			&& !data[NUMBER_LINE_MAP_FROM]
			&& only_symbols("\t 012N", line)
			&& ft_strlen(line) > 2)
				data[NUMBER_LINE_MAP_FROM] = data[COUNTER];
		if (res
			&& data[NUMBER_LINE_MAP_FROM]
			&& map->width < (data[CURRENT_LEN] = ft_strlen(line)))
				map->width = data[CURRENT_LEN];
		free(line);
		data[COUNTER]++;
	}
	close(fd);
	map->hight = data[COUNTER] - data[NUMBER_LINE_MAP_FROM];
	return (data[NUMBER_LINE_MAP_FROM]);
}


int		parse_color(char* line, int i, t_map *map)
{
	int color[3];
	int k;

	k = -1;
	while (*line && ++k < 3)
	{
		while(!(*line <= '9' && *line >= '0') && *line)
			line++;
		color[k] = ft_atoi(line);
		while((*line <= '9' && *line >= '0') && *line)
			line++;
	}
	if (i == F)
		map->floor_color = create_trgb(0, color[0], color[1], color[2]);
	else if (i == C)
		map->ceiling_color = create_trgb(0, color[0], color[1], color[2]);
	return (0);
}

void	parse_line(char *line,  t_map *map)
{
	char 	*p;
	int 	i;
	char 	*texture_identifiers[] = {"NO", "SO", "WE", "EA", "S", "F", "C"};

	//printf("line: %s\n", line);
	//write(1, "parsing line", 13);
	//write(1, line, ft_strlen(line));
	if ((p = ft_strnstr(line, "R", 3)))
	{
			//write(1, "Res\n", 4);
		while(*p > '9' || *p < '0')
			p++;
		map->resolution_width = ft_atoi(p);
			//printf("return strntst = %d \n", ft_atoi(p));
		while(*p <= '9' && *p >= '0')
			p++;
		map->resolution_hight = ft_atoi(p);
	}
	i = -1;
	while (++i < 5)
	{
		if ((p = ft_strnstr(line, texture_identifiers[i], 4))
			&& (map->path_provided |= (1 << i)))
		{
			printf("tex %d %s found\n", i, p);
			map->texture_path[i] = ft_strtrim(p + 2, " ");
			break;
		}
	}
	while (i < 7)
	{
		if ((p = ft_strnstr(line, texture_identifiers[i],3)))
		{
			map->path_provided |= (1 << i);
			parse_color(p + 1, i, map);
			break;
		}
		i++;
	}
}

void 	fill_map(t_map *map, char *line)
{
	static int line_number;
	char symbol_to_put;
	int i;

	i = 0;
	while (line[i])
	{
		symbol_to_put = ft_strchr("\t ", line[i]) ? CHAR_OF_EMPTY_SPACE :
				line[i];
		if (symbol_to_put == 'N')
		{
			map->respawn[X] = i;
			map->respawn[Y] = line_number;
		}
		*(map->map + i++ + line_number * map->width) = symbol_to_put;
	}
	//write(1, "fill\n", 5);
	while (i < map->width)
		*(map->map + i++ + line_number * map->width) = CHAR_OF_EMPTY_SPACE;
	line_number++;
	//printf("%s\n", map->map);
}

int		parse_map(char *filename, t_map *map, int *var)
{
	int res;
	int fd;
	char *line;

	write(1, "size\n", 5);
	line = NULL;
	var[COUNTER] = 0;
	res = 1;
	fd = open(filename, O_RDONLY);
	while (res > 0)
	{
		if ((res = get_next_line(fd, &line)))
		{
			if (var[COUNTER] < var[NUMBER_LINE_MAP_FROM])
				parse_line(line, map);
			else
				fill_map(map, line);
		}
		free(line);
		var[COUNTER]++;
	}
	close(fd);
}


int			validate_map(t_map *map)
{
	/* rename to validating params of map */
	int 	i;

	i = -1;
	while (++i < NUM_PARAMS)
	{
		printf("path tex %d -> %s\n", i, map->texture_path[i]);

		if (i > S)
		{
			if (!(map->path_provided & (1 << i)) && BEHAVE_HARD)
				return (1);
			continue;
		}
		if (!(map->path_provided & (1 << i)) && BEHAVE_HARD)
			return (1);
		if (map->path_provided & (1 << i) && !map->texture_path[i])
		{
			if (BEHAVE_HARD)
				return (1);
			map->path_provided &= (0 << i);
		}
	}
	/* 		map enclosed ? algorithm 	*/
	return (0);
}


void		print_map(t_map *map)
{
	int j = -1;
	int i;
	while (++j < map->hight)
	{
		i = -1;
		while (++i < map->width)
			write(1, map->map + i + (map->width * j), 1);
		write(1, "\n", 1);
	}
}

int			check_map_parametrs(t_map *map)
{
	printf("ceiling clr = %X\n", map->ceiling_color);
	printf("flooe clr = %X\n", map->floor_color);
	printf("resolution %d %d\n", map->resolution_hight, map->resolution_width);

	if (!map->resolution_width || !map->resolution_hight)
	{
		if (BEHAVE_HARD)
			return (1);
		map->resolution_width = SCREEN_WIDTH;
		map->resolution_hight = SCREEN_HEIGHT;
	}
	printf("map %d %d\n", map->hight, map->width);
	printf("resolution %d %d\n", map->resolution_hight, map->resolution_width);
	return (0);
}

t_map		*map_parser(char *filename)
{
	int var[LEN_VAR_ARRAY];
	t_map *map;

	//write(1, "parser\n", 7);
	if (!(map = ft_calloc(1, sizeof(t_map))))
		return (0);
	ft_memset(var, 0, sizeof(var));
	map_size_parser(filename, map, var);
	//printf("number line from: %d\n width: %d hight: %d",
	//	var[NUMBER_LINE_MAP_FROM], map->width, map->hight);
	if (!(map->map = ft_calloc(1, sizeof(char) * map->width * map->hight + 1)))
		return (0);
	var[CURRENT_LEN] = var[COUNTER];
	parse_map(filename, map, var);
	check_map_parametrs(map);
	print_map(map);
	if (!validate_map(map))
		return (0);  /* free wiil inside */
	if (RESIZE > 1)
		resize_map(map, RESIZE);
	return (map);
}