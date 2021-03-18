#include "cub3d.h"

int             key_hook(int keycode)
{
	//printf("released key: %d\n", keycode);
	return (keycode);
}

int			valid_player_position(t_vars *vars, double cord_x, double cord_y)
{

	double 	cords[2];

	int x;
	int y;
	char val;
	x = 0;
	y = (int)vars->player[SIZE];
	while (x <= y)
	{
		while (circle_combine_cords_gen(cords, x, y))
		{
			val = *(vars->map->map + (int)cords[X] + (int)cord_x
					+ ((int)cords[Y]
					+ (int)cord_y) * vars->map->width);
			if (!ft_strchr("0N", val))
				return (0);
		}
		x++;
		y = (int)sqrt(pow(vars->player[SIZE], 2) - pow(cords[X], 2));
	}
	return (1);
}

double 	map_move_with_buttons(int button, int axis)
{
	double move_val;

	move_val = 0.1 * RESIZE;

	if (button == W_BUTTON && axis == Y)
		return (move_val);
	if (button == A_BUTTON && axis == X)
		return (-move_val);
	if (button == S_BUTTON && axis == Y)
		return (-move_val);
	if (button == D_BUTTON && axis == X)
		return (move_val);
	return (0);

}

int   exit_hook(int button, t_vars *vars)
{
	static int counter;
	static int pressed;
	double move_val;
	double x;
	double y;
	move_val = 1;//RESIZE / 12;

//	if (pressed == button)
//		counter++;
//	else
//		counter = 0;
//	pressed = button;
	if (button == 53)
		vars->exit = 1;
	if (button == 124)
		vars->player[RAD] += 0.05;
	if (button == 123)
		vars->player[RAD] -= 0.05;

	x = vars->player[X]
			+ move_val// * RESIZE / 12
			* map_move_with_buttons(button, Y) * sin(vars->player[RAD])
			+ move_val
			* map_move_with_buttons(button, X) * cos(vars->player[RAD]);
	y = vars->player[Y]
			+ move_val// * RESIZE / 12
			* map_move_with_buttons(button, Y) * cos(vars->player[RAD])
			+ move_val
			* map_move_with_buttons(button, X) * -sin(vars->player[RAD]);

	if (valid_player_position(vars, x, y))
	{
		//printf("valid move");
		vars->player[X] = x;
		vars->player[Y] = y;
	}
		//printf("bad move");
	printf("Pressed: %d\n", button);
//	printf("player x[%g] y[%g] ", vars->player[X], vars->player[Y]);
//	printf("player x[%d] y[%d]\n", (int)round(vars->player[X]),
//		   (int)round(vars->player[Y]));
	return(button);
}

int   mouse_hook(int button, int x,int y, void *vars)
{
	t_vars *var = (t_vars*)vars;
	var->move = x;
//	mlx_loop_hook(var->mlx, render_next_frame, &vars);
	printf("Pressed: %d, x: %d y: %d\n", button, x, y);
//	(void*)param;
	return(button);
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
		cub_exit(vars, 0);
	fill_half_screen(vars, 0, vars->map->ceiling_color);
	fill_half_screen(vars, 1, vars->map->floor_color);
//	rotate_camera(vars);
	//if (RESIZE < 30)
	//	put_map(vars);
	put_player(vars);
	put_tex(vars); //del
	mlx_string_put(vars->mlx, vars->win, vars->map->resolution_width /2 , 20, 0xFFFFFF,
						  "HOBA!");

	//while (radius >= 0)
	//{
	//	put_circle(img, radius,
	//		 vars->player[X], vars->player[Y], (int)
	//		0x00FF0000 | vars->move << 8);
	//	//put_circle(img, radius, 400, 400, 0xFF00FF00);
	//	radius -= 2;
	//}
	//mlx_clear_window(vars->mlx, vars->win);
	vars->move++;
	//vars->move *= vars->move < 8;
	vars->move *= (vars->move < ((1 << 31) + 1) * -1);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	return (1);
}

int	create_img_of_screen(t_vars *vars)
{
	printf("IMG\n");
	vars->data->img = NULL;
	vars->data->addr = NULL;
	if (!(vars->data->img = mlx_new_image(vars->mlx,
									   		vars->map->resolution_width,
									   		vars->map->resolution_hight)))
		return (0);
	if (!(vars->data->addr = mlx_get_data_addr(vars->data->img,
											   &vars->data->bits_per_pixel,
											   &vars->data->line_length,
											   &vars->data->endian)))
		return (0);
	if (!(vars->data->buffer = ft_calloc(sizeof(int)
			* vars->map->resolution_hight * vars->map->resolution_width, 1)))
		return (0);
	return (1);
}

int     		main(int argc, char **argv)
{
	//void    	*mlx;
	//void		*win;
	t_data  	img;
	t_vars 		vars;

	vars.exit = 0;
	printf("args: %s %s\n", argv[0], argv[1]);

	if (argc < 2)
	{
		write(1, "No input\n", 9);
		return (1);
	}
//	vars.mlx = NULL;
//	vars.win = NULL;
	ft_memset(&vars, 0, sizeof(vars));
	vars.data = &img;
	if (!(vars.map = map_parser(argv[1]))
	 || !(vars.mlx = mlx_init())
	 || !(create_img_of_screen(&vars))
	 || !(load_textures(&vars))
	 || !(vars.win = mlx_new_window(vars.mlx,
								   vars.map->resolution_width,
								   vars.map->resolution_hight, "Hoba!")))
		return (cub_exit(&vars, 1));

	//vars.mlx = mlx;
//	if (load_texture(&vars, 0))
//		return (1);
	//printf("path NO %s\n", vars.map->texture_path[NO]);
	//vars.win = mlx_new_window(vars.mlx,
	//					 vars.map->resolution_width,
	//					 vars.map->resolution_hight, "Hoba!");

	printf("vars.data-> %p, %p\n", vars.data->img, vars.data->addr);

//	printf("bits per pix = %d, line_lenght = %d\n",
//		img.bits_per_pixel, img.line_length);
	vars.move = 0;
	vars.player[SIZE] = RESIZE / 6;
	vars.player[ROTATE] = 0;
	vars.player[X] = (double)vars.map->respawn[X];
	vars.player[Y] = (double)vars.map->respawn[Y];
	//vars.mlx = mlx;
	//vars.win = win;
	//vars.data = &img;
	printf("ERROR -> %s\n", strerror(errno));

	mlx_hook(vars.win, keyPress, 0, exit_hook, &vars);
	mlx_hook(vars.win, buttonPress, ButtonPressMask, mouse_hook, &vars);
	mlx_hook(vars.win, keyRelease, 0, key_hook, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);

	mlx_loop(vars.mlx);	//mlx_loop(mlx);
	return (1);
}












