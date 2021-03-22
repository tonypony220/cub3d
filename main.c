#include "cub3d.h"

int             release_hook(int button, t_vars *vars)
{
	vars->btns[button] = 0;
	return (button);
}

int   press_hook(int button, t_vars *vars)
{
	if (button == ESC_BUTTON)
		vars->exit = 1;
	else
		vars->btns[button] = 1;
	return(button);
}

int   mouse_hook(t_vars *vars)
{
	vars->exit = 1;
	return(1);
}


int   mouse2_hook(int button, int x,int y)
{
	printf("2Pressed: %d, x: %d y: %d\n", button, x, y);
//	(void*)param;
	return(button);
}

//void	rotate_camera(t_vars *vars)
//{
//	int sing;
//
//	printf("%g\n", vars->player[ROTATE]);
//	if (fabs(vars->player[ROTATE]) > 0.01)
//	{
//		sing = vars->player >= 0 ? 1 : -1;
//		vars->player[RAD] += 0.01 * sing;
//		vars->player[ROTATE] += 0.01 * sing;
//	}
//}

void	put_tex(t_vars *vars)
{
	int  y = -1, x;
	int tex_x ;
	while (++y < TEX_HEGHT)
	{
		x = vars->map->resolution_width - TEX_WIDTH - 1;
		tex_x =0 ;
		while (++x < vars->map->resolution_width)
		{
			pixel_put(vars, x, y,*(vars->texs[0]->addr
						+ vars->texs[0]->line_length * y
						+ vars->texs[0]->bits_per_pixel / 8 *tex_x));
			tex_x++;
		}
	}
}

int     render_next_frame(t_vars *vars)
{
	t_data  img = *(*vars).data;
	if (vars->exit)
		exit(cub_exit(vars, 0));
	moving(vars);
	fill_half_screen(vars, 0, vars->map->ceiling_color);
	fill_half_screen(vars, 1, vars->map->floor_color);
	printf("%s RENDERING %s\n", GREEN, RESET);
	put_player(vars);
	if (vars->save)
	{
		create_bmp_file(vars->data->addr, "scr_shot.bmp",
						vars->map->resolution_width,
						vars->map->resolution_hight,
						vars->data->bits_per_pixel);
		exit(cub_exit(vars, 0));
	}
	vars->move++;
	vars->move *= (vars->move < ((1 << 31) + 1) * -1);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	return (1);
}

int	create_screen(t_vars *vars)
{
	int w;
	int h;

	mlx_get_screen_size( &w, &h);
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
///	if (!(vars->data->buffer = ft_calloc(sizeof(int)
///			* vars->map->resolution_hight * vars->map->resolution_width, 1)))
///		return (0);
//	printf("%d DATA %dline len ", vars->data->bits_per_pixel, vars->data->line_length);
	return (1);
}

int     		main(int argc, char **argv)
{
	t_vars 		vars;

	vars.exit = 0;
	printf("args: %s %s %s\n", argv[0], argv[1], argv[2]);

	ft_memset(&vars, 0, sizeof(vars));
	if (!(argc == 2 || argc == 3)
	|| !ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))
	|| (argc == 3 && (vars.save = 1) && ft_strncmp("--save", argv[2], 6)))
		exit(cub_exit(&vars, 1));
	if (!(vars.map = map_parser(argv[1]))
	 || !(vars.mlx = mlx_init())
	 || !(create_screen(&vars))
	 || !(load_textures(&vars))
	 || (vars.save == 0 && !(vars.win = mlx_new_window(vars.mlx,
								   vars.map->resolution_width,
								   vars.map->resolution_hight, "Hoba!"))))
		return (cub_exit(&vars, 1));
	printf("%s START %s\n", GREEN, RESET);
	vars.move = 0;
	vars.player[SIZE] = RESIZE / 6;
	vars.player[ROTATE] = 0;
	vars.player[X] = vars.map->respawn[X] + 0.5;
	vars.player[Y] = vars.map->respawn[Y] + 0.5;
	if (vars.save)
		render_next_frame(&vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_hook(vars.win, keyPress, 0, press_hook, &vars);
	mlx_hook(vars.win, destroyNotify, 0, mouse_hook, &vars);
	mlx_hook(vars.win, keyRelease, 0, release_hook, &vars);
	mlx_loop(vars.mlx);
	return (1);
}












