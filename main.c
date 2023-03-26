/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 19:08:46 by mehtel            #+#    #+#             */
/*   Updated: 2021/03/23 19:12:18 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			render_next_frame(t_vars *vars)
{
	int screen_size[2];

	if (vars->exit)
		exit(cub_exit(vars, 0));
	moving(vars);
	fill_half_screen(vars, 0, vars->map->ceiling_color);
	fill_half_screen(vars, 1, vars->map->floor_color);
	put_player(vars);
	if (vars->save)
	{
		screen_size[X] = vars->map->resolution_width;
		screen_size[Y] = vars->map->resolution_hight;
		create_bmp_file(vars->data->addr, "scr_shot.bmp",
						screen_size,
						vars->data->bits_per_pixel);
		exit(cub_exit(vars, 0));
	}
	vars->move++;
	vars->move *= (vars->move < ((1 << 31) + 1) * -1);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
	return (1);
}

int			create_screen(t_vars *vars)
{
	int		w;
	int		h;

	mlx_get_screen_size(&w, &h);
	if (vars->map->resolution_hight > h)
		vars->map->resolution_hight = h;
	if (vars->map->resolution_width > w)
		vars->map->resolution_width = w;
	vars->win_k = ((double)vars->map->resolution_width
					/ (double)vars->map->resolution_hight)
					* (double)h / (double)w;
	if (!(vars->data = ft_calloc(sizeof(t_data), 1)))
		return (0);
	if (!(vars->data->img = mlx_new_image(vars->mlx,
											vars->map->resolution_width,
											vars->map->resolution_hight)))
		return (0);
	if (!(vars->data->addr = mlx_get_data_addr(vars->data->img,
													&vars->data->bits_per_pixel,
													&vars->data->line_length,
													&vars->data->endian)))
		return (0);
	return (1);
}

void		init_player(t_vars *vars)
{
	int spawn_dir;

	if (vars->map->respawns == 'S')
		spawn_dir = 0;
	if (vars->map->respawns == 'N')
		spawn_dir = 2;
	if (vars->map->respawns == 'E')
		spawn_dir = 1;
	if (vars->map->respawns == 'W')
		spawn_dir = 3;
	vars->move = 0;
	vars->player[SIZE] = RESIZE / 6;
	vars->player[RAD] = PI / 2 * spawn_dir;
	vars->player[X] = vars->map->respawn[X] + 0.5;
	vars->player[Y] = vars->map->respawn[Y] + 0.5;
}

int			main(int argc, char **argv)
{
	t_vars	vars;

	vars.exit = 0;
	ft_memset(&vars, 0, sizeof(vars));
	if (!(argc == 2 || argc == 3)
	|| !ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))
	|| (argc == 3 && (vars.save = 1) && ft_strncmp("--save", argv[2], 6)))
		exit(cub_exit(&vars, 2));
	if (!(vars.map = map_parser(argv[1], &vars))
	|| !(vars.mlx = mlx_init())
	|| !(create_screen(&vars))
	|| !(load_textures(&vars))
	|| (vars.save == 0 && !(vars.win = mlx_new_window(vars.mlx,
								vars.map->resolution_width,
								vars.map->resolution_hight, "Hoba!"))))
		return (cub_exit(&vars, 1));
	init_player(&vars);
	if (vars.save)
		render_next_frame(&vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_hook(vars.win, KEYPRESS, 0, press_hook, &vars);
	mlx_hook(vars.win, DESTROY_NOTIF, 0, mouse_hook, &vars);
	mlx_hook(vars.win, KEYRELEASE, 0, release_hook, &vars);
	mlx_loop(vars.mlx);
	return (1);
}
