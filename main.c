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
	if (button == 124)
		vars->player[RAD] += 0.05;
	if (button == 123)
		vars->player[RAD] -= 0.05;

	if (button == 53)
		exit(1);
	if (counter >= 10)
		printf("Holded!\n");

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
	/* printf("Pressed: %d\n", button); */
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
			pixel_put(vars, x, y,*(vars->textures[0] + TEX_HEGHT * y + tex_x));
			tex_x++;
		}

	}

}

int     render_next_frame(t_vars *vars)
{
	t_data  img = *(*vars).data;
	int radius = 1;
//	if (!vars->move)
//		return(1);
	//fill_screen(vars, 0x0F010101);

	fill_half_screen(vars, 0, vars->map->ceiling_color);
	fill_half_screen(vars, 1, vars->map->floor_color);
//	rotate_camera(vars);
	if (RESIZE < 30)
		put_map(vars);
	put_player(vars);
	put_tex(vars); //del

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
	vars->move *= (vars->move < ((1 << 31) + 1) * -1);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	return (1);
}

int     		main(int argc, char **argv)
{
	void    	*mlx;
	void		*win;
	t_data  	img;
	t_vars 		vars;


	printf("args: %s %s\n", argv[0], argv[1]);
	if (argc != 2)
	{
		write(1, "No input\n", 9);
		return (1);
	}
	vars.map = map_parser(argv[1]); // if no map
//	write(1, "Parsed\n", 7);
	generate_textures(&vars);
	printf("path NO %s\n", vars.map->texture_path[NO]);
	mlx = mlx_init();
	vars.mlx = mlx;
	load_texture(&vars, 0);
	img.img = mlx_new_image(mlx, vars.map->resolution_width, vars.map->resolution_hight);
	win = mlx_new_window(mlx,
					  	 vars.map->resolution_width,
					  	 vars.map->resolution_hight, "Hoba!");
	img.addr = mlx_get_data_addr(img.img,
							     &img.bits_per_pixel,
							     &img.line_length,
								 &img.endian);
	img.buffer = ft_calloc(sizeof(int)
			* vars.map->resolution_hight * vars.map->resolution_width, 1);
//	printf("bits per pix = %d, line_lenght = %d\n",
//		img.bits_per_pixel, img.line_length);
	vars.move = 0;
	vars.player[SIZE] = RESIZE / 6;
	vars.player[ROTATE] = 0;
	vars.player[X] = (double)vars.map->respawn[X];
	vars.player[Y] = (double)vars.map->respawn[Y];
	vars.mlx = mlx;
	vars.win = win;
	vars.data = &img;
	printf("ERROR -> %s\n", strerror(errno));

	mlx_hook(win, keyPress, 0, exit_hook, &vars);
	mlx_hook(win, buttonPress, ButtonPressMask, mouse_hook, &vars);
	mlx_hook(win, keyRelease, 0, key_hook, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);

	mlx_loop(mlx);	//mlx_loop(mlx);
	return (1);
}












