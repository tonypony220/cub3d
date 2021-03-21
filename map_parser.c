#include "cub3d.h"

int		map_size_parser(char *filename, t_map *map, int *data)
{
	int res;
	int fd;
	char *line;

	fd = open(filename, O_RDONLY);
	while ((res = get_next_line(fd, &line)) > 0)
	{
		if (res && !data[NUMBER_LINE_MAP_FROM]
			&& only_symbols("\t 012N", line)
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
		if ((unsigned int) color[k] > 255)
			map->invalid = 1;
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
			map->respawns++;
		}
		else if (symbol_to_put == '2')
		{
			map->sprites[map->sprite_counter].cord[X] = i + 0.5;
			map->sprites[map->sprite_counter].cord[Y] = line_number + 0.5;
			map->sprite_counter--;
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
	int	tmp_sprite_num;

	write(1, "size\n", 5);
	line = NULL;
	var[COUNTER] = 0;
	res = 1;
	tmp_sprite_num = map->sprite_counter;
	map->sprite_counter--; /* for correct index filling*/
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
	map->sprite_counter = tmp_sprite_num;
}


int			validate_map_params(t_map *map)
{
	int 	i;

	i = -1;
	while (++i < NUM_PARAMS)
	{
		if (i > S)
		{
			if (!(map->path_provided & (1 << i)) && BEHAVE_HARD)
				return (0);
			continue;
		}
		//printf("path tex %d -> %s\n", i, map->texture_path[i]);
		if (!(map->path_provided & (1 << i)) && BEHAVE_HARD)
			return (0);
		if (map->path_provided & (1 << i) && !map->texture_path[i])
		{
			if (BEHAVE_HARD)
				return (0);
			map->path_provided &= (0 << i);
		}
	}
	/* 		map enclosed ? algorithm 	*/
	return (1);
}

/// delete
///void		print_map(t_map *map, int k) // k which map
///{
///	int j = -1;
///	int i;
///	while (++j < map->hight)
///	{
///		i = -1;
///		while (++i < map->width)
///		{
///			if (k == 0)
///				write(1, map->map + i + (map->width * j), 1);
///			else
///				if (*(map->visited + i + (map->width * j)))
///					write(1, "1", 1);
///				else
///					write(1, " ", 1);
///		}
///		write(1, "\n", 1);
///	}
///}

int			check_map_parametrs(t_map *map)
{
	printf("ceiling clr = %X\n", map->ceiling_color);
	printf("floor clr = %X\n", map->floor_color);
	printf("before resolution %d %d\n", map->resolution_hight, map->resolution_width);

	if (map->resolution_width < 1 || map->resolution_hight < 1)
	{
		if (BEHAVE_HARD)
			return (0);
		map->resolution_width = SCREEN_WIDTH;
		map->resolution_hight = SCREEN_HEIGHT;
	}
	printf("map %d %d\n", map->hight, map->width);
	printf("resolution %d %d\n", map->resolution_hight, map->resolution_width);
	return (1);
}

int			validate_map(t_map *map)
{
	char mv[8];

	if (map->respawns != 1)
		return (0);
	combinate_all_moves(mv);
	dfs(map, mv, map->respawn[X], map->respawn[Y]);
	if (!validate_map_params(map)
	|| !check_map_parametrs(map)
	|| map->invalid)
		return (0);
//	print_map(map, 1);
	printf("map->invalid = %d", map->invalid);
	return (1);
}

t_map		*map_parser(char *filename)
{
	int var[LEN_VAR_ARRAY];
	t_map *map;

	if (!(map = ft_calloc(1, sizeof(t_map))))
		return (0);
	ft_memset(var, 0, sizeof(var));
	if (map_size_parser(filename, map, var) < 0)
		return (0);
	if (!(map->map = ft_calloc(1, sizeof(char) * map->width * map->hight + 1))
	|| !(map->visited = ft_calloc(1, sizeof(char) * map->width * map->hight + 1))
	|| !(map->sprites = ft_calloc(sizeof(t_sprite), map->sprite_counter))
	|| !(map->sprites_order = ft_calloc(sizeof(int), map->sprite_counter))
	|| !(map->sprites_dist = ft_calloc(sizeof(double), map->sprite_counter)))
		return (free_map(map));
	var[CURRENT_LEN] = var[COUNTER];
	parse_map(filename, map, var);
	print_map(map, 0);
	if (!validate_map(map)
	|| !(map->zbuf = ft_calloc(sizeof(double), map->resolution_width)))
		return (free_map(map));  /* free wiil inside */
	if (RESIZE > 1)
		resize_map(map, RESIZE);
	write(1, "\t\t\tPARSER\n", 10);
	return (map);
}