#include "cub3d.h"

void		put_circle_new(t_data img, int radius, int cord_x, int cord_y,
						   int color);

void		fill_half_screen(t_vars *vars, int which_half, int color)
{
	int 	x;
	int 	y;
	int		fill_to;

	x = 0;
	y = 0;
	fill_to = vars->map->resolution_hight / 2;

	if (which_half)
	{
		y = fill_to;
		fill_to = vars->map->resolution_hight;
	}

	while (y++ < fill_to)
	{
		while (x++ < vars->map->resolution_width)
			pixel_put(vars->data, x, y, color);
		x = 0;
		//color += 1 * (- 1 * which_half);
	}
}

void		fill_screen(t_vars *vars, int color)
{
	int x;
	int y;
	x = 0;
	y = 0;

	while (y++ < vars->map->resolution_hight)
	{
		while (x++ < vars->map->resolution_width)
			pixel_put(vars->data, x, y, color);
		x = 0;
	}
}

/*
 * 1111
 * 1111
 * 1111
 * 1111
 */

void		put_square(t_vars *vars, int x, int y, int side, int clr)
{
	int j;
	int jj;

	jj = y;
	while (jj < (y + side))
	{
		j = x - 1;
		while (++j < (x + side))
			pixel_put(vars->data, j, jj, clr);
		jj++;
	}
}

void		put_vertical_line(t_vars *vars, int x, int y_up,
						int y_down, int color)
{
	if (y_up < 0)
		y_up = 0;
	if (y_down >= vars->map->resolution_hight)
		y_down = vars->map->resolution_hight - 1;
	while (y_down > y_up)
	{
		pixel_put(vars->data, x, y_up, color);
		y_up++;
	}
}

typedef struct  s_ray
{
	double		dir[2];
	int			move[2];
	double		plane[2];

	double 		on_map[2];
	double		ray_dir[2];
	double 		ray_len[2];
	double 		delta_len[2];
	double 		perpWallDist;
	double		on_wall;
	int			tex[2];
	int			wall_reached;
	int			side; //
}               t_ray;
void			put_textured_line(t_vars *vars, int line_len, t_ray *cords,
								  int x);

void		put_player(t_vars *vars)
{
	//put_circle(*vars->data,
	//		   vars->player[SIZE],
	//		   vars->player[X],
	//		   vars->player[Y],
	//		   0x00FF0000 | vars->move << 8);
	//put_circle_new(*vars->data,
	//		   30,
	//		   vars->player[X],
	//		   vars->player[Y],
	//		   0x00FF0000 | vars->move << 8);

	t_ray	cords;
	cords.dir[X] = sin(vars->player[RAD]); //-1;
	cords.dir[Y] = cos(vars->player[RAD]); //0;
	cords.plane[X] = 0.66 * cos(vars->player[RAD]); //  * cos
	cords.plane[Y] = -0.66 * sin(vars->player[RAD]); // * cos
	double cameraX;

	int x;
	x = -1;
	int color = 0x00ff44;
	int color2;
	//int i;
	//double rad;
	//rad = 0.00;
	int counter = 0;  /// del
	int rays = vars->map->resolution_width;

	//double tmpX = vars->player[X], tmpY = vars->player[Y];
	//vars->player[X] = (int)vars->player[X];
	//vars->player[Y] = (int)vars->player[Y];

	while (++x < rays) //vars->map->resolution_width)
	{
		cameraX = 2 * x / (double)rays - 1;// (double)
		// vars->map->resolution_width - 1;
		cords.ray_dir[X] = cords.dir[X] + cords.plane[X] * cameraX;
		cords.ray_dir[Y] = cords.dir[Y] + cords.plane[Y] * cameraX;
		//printf("camX= %g x=%d ray %g %g\n",cameraX, x, cords.ray_dir[X], cords.ray_dir[Y]);
		cords.on_map[X] = (int)(vars->player[X]);
		cords.on_map[Y] = (int)(vars->player[Y]);

		cords.delta_len[X] = fabs(1 / cords.ray_dir[X]);
		cords.delta_len[Y] = fabs(1 / cords.ray_dir[Y]);

	//	if (cords.ray_dir[Y] == 0)
	//		cords.delta_len[X] = 0;
	//	else
	//		cords.delta_len[X] = cords.ray_dir[X] == 0 ?1 : fabs(1 / cords.ray_dir[X]);

	//	if (cords.ray_dir[X] == 0)
	//		cords.delta_len[Y] = 0;
	//	else
	//		cords.delta_len[Y] = cords.ray_dir[Y] == 0 ?1 : fabs(1 / cords.ray_dir[Y]);
		//printf("delta = %g, %g\n", cords.delta_len[X], cords.delta_len[Y]);


		if (cords.ray_dir[X] < 0)
		{
			cords.move[X] = -1;
			cords.ray_len[X] = (vars->player[X] - cords.on_map[X])
								* cords.delta_len[X];
		}
		else
		{
			cords.move[X] = 1;
			cords.ray_len[X] = (cords.on_map[X] + 1.0 - vars->player[X])
								* cords.delta_len[X];
		}
		if (cords.ray_dir[Y] < 0)
		{
			cords.move[Y] = -1;
			cords.ray_len[Y] = (vars->player[Y] - cords.on_map[Y])
							   * cords.delta_len[Y];
		}
		else
		{
			cords.move[Y] = 1;
			cords.ray_len[Y] = (cords.on_map[Y] + 1.0 - vars->player[Y])
								* cords.delta_len[Y];
		}

		cords.wall_reached = 0;
		while (cords.wall_reached == 0)
		{
			if (cords.ray_len[X] < cords.ray_len[Y])
			{
				cords.ray_len[X] += cords.delta_len[X];
				cords.on_map[X] += cords.move[X];
				cords.side = X;
			}
			else
			{
				cords.ray_len[Y] += cords.delta_len[Y];
				cords.on_map[Y] += cords.move[Y];
				cords.side = Y;
			}
			char block = *(vars->map->map
						   + (int)(cords.on_map[X])
						   + vars->map->width * (int)(cords.on_map[Y]));
			//char block2 = *(vars->map->map
			//			   + (int)(cords.on_map[X])
			//			   + vars->map->width * (int)(cords.on_map[Y]));
			if (block != '0' && block != 'N')// && block2 != '0')
			{
				cords.wall_reached = 1;
				pixel_put(vars->data, (int) cords.on_map[X],
						  (int) cords.on_map[Y],
						  color);
			}
			pixel_put(vars->data, (int) cords.on_map[X],
					  (int) cords.on_map[Y],
					  color + 100);
			//printf("move %d %d\n", cords.move[X], cords.move[Y]);
			//count++;

		}
			/* cords.sides is X or Y which is 0 or 1 */
			cords.perpWallDist = (cords.on_map[cords.side]
								   - vars->player[cords.side]
								   + (1 - cords.move[cords.side]) / 2)
							    	/ cords.ray_dir[cords.side];
			int line_len;

			line_len = (vars->map->resolution_hight * RESIZE / cords.perpWallDist);

			if (cords.perpWallDist == 0)
				line_len = vars->map->resolution_hight;

			color2 = 0xBBbfbbbb;
			if (cords.side == 1)
				color2 = 0xBBa19d9d;
			color2 -= x / 10;

			//printf("%d(%d) ", line_len, x);
		//	put_vertical_line(vars, x,
		//					 0,
		//					 cords.perpWallDist,
		//					 color2);

		//	put_vertical_line(vars, x,
		//					  0,
		//					  line_len,
		//					  color2);
		//	put_vertical_line(vars, x,
		//			 		  vars->map->resolution_hight - line_len,
		//					  vars->map->resolution_hight - 1,
		//					  color2);

			//put_vertical_line(vars, x,
			//		 (vars->map->resolution_hight >> 1) - (line_len >> 1),
			//		 vars->map->resolution_hight / 2 + line_len / 2 ,
			//		 color2);
			/////


			////cords.on_wall = vars->player[cords.side]
			////		+ cords.perpWallDist * cords.ray_dir[cords.side];
			////cords.on_wall -= floor(cords.on_wall);

			////cords.tex[X] = (int)(cords.on_wall * (double)TEX_WIDTH);
			////if ((cords.side == X && cords.ray_dir[X] > 0)  // EAST
			////	||
			////	(cords.side == Y && cords.ray_dir[Y] < 0)) // NORTH
			////		cords.tex[X] = TEX_WIDTH - cords.tex[X] - 1;





	}

//	vars->player[X] = tmpX;
//	vars->player[Y] = tmpY;

	//put_square(vars,
	//		vars->player[X],
	//		vars->player[Y],
	//		vars->player[SIZE],
	//		0x00FF0000 | vars->move << 8);
}

// 0000
// 0001
// 0010
// 0011
// 0100 4
// 0101 5
// 0110 6
// 0111 7

void			put_textured_line(t_vars *vars, int line_len, t_ray *cords,
						 int x)
{
	double shift;
	double tex_pos;
	int start_of_line;
	int end_of_line; // not same as used for vertical line in tutorial
	int y;

	start_of_line = (vars->map->resolution_hight >> 1) - (line_len >> 1);
	start_of_line *= start_of_line > 0;
	shift = 1.0 * TEX_HEGHT / line_len;
	tex_pos = ((start_of_line
			    - (vars->map->resolution_hight >> 1) + (line_len >> 1)));
	y = start_of_line;
	while (y < end_of_line)
	{
		cords->tex[Y] = (int)tex_pos & TEX_HEGHT - 1;
		tex_pos += 1;
		pixel_put(vars->data, x, y,
				  *(vars->textures[0] + TEX_HEGHT * cords->tex[Y] +
				  cords->tex[X]));
	}
}

int				circle_combine_cords_gen(double *cords, double x, double y)
{
	static int	call_number;

	cords[X] = x;
	cords[Y] = y;
	if (call_number & 0b0100)
	{
		cords[X] = y;
		cords[Y] = x;
	}
	if (call_number & 0b0001)
		cords[X] *= -1;
	if (call_number & 0b0010)
		cords[Y] *= -1;
	call_number++;
	call_number *= call_number < 9;
	return (call_number);


}

void		put_circle(t_data img, int radius, int cord_x, int cord_y,
				 	   int color)
{
	int tmp;
	int cords[2];
	int d;

	int x;
	int y;
	x = 0;
	//tmp = cords[X];
	y = radius;
//	d = 3 - 2 * radius;
//	y = radius;
	while (x <= y)
	{
		//printf("start cords: x=%d, y=%d\n", cords[X], cords[Y]);
		while (circle_combine_cords_gen(cords, x, y))
		{
		//	printf("cords: x=%d, y=%d\n", cords[X], cords[Y]);
			pixel_put(&img, cords[X] + cord_x, cords[Y] + cord_y, color);
			//cords[X] = tmp;
			//cords[Y] = (int)sqrt(pow(radius, 2) - pow(cords[X], 2));
		}
		//printf("next tmp%d\n", tmp);
		//cords[X] = ++tmp;
		x++;
		y = (int)sqrt(pow(radius, 2) - pow(cords[X], 2));
		//tmp = ++cords[X];
//		printf("end cords: x=%d, y=%d\n", cords[X], cords[Y]);
		//if (d > 0)
		//{
		//	y--;
		//	d = d + 4 * (x - y) + 10;
		//}
		//else
		//	d = d + 4 * x + 6;
		//int x = cords[X];
		//int y = cords[Y];
		//pixel_put(&img, x + cord_x, y + cord_y, color);
		//pixel_put(&img, y + cord_x, x + cord_y, color);
		//pixel_put(&img, -1 * x + cord_x, y + cord_y, color);
		//pixel_put(&img, -1 * y + cord_x, x + cord_y, color);
		//pixel_put(&img, x + cord_x, -1 * y + cord_y, color);
		//pixel_put(&img, y + cord_x, -1 * x + cord_y, color);
		//pixel_put(&img, -1 * x + cord_x, -1 * y + cord_y, color);
		//pixel_put(&img, -1 * y + cord_x, -1 * x + cord_y, color);
		color += (1 << 9);
	}
//	y = 0;
//	while (y <= radius)
//	{
//		x = (int) sqrt(pow(radius, 2) - pow(y, 2));
//		pixel_put(&img, x + cord_x, y + cord_y, color);
//		pixel_put(&img, -1 * x + cord_x, y + cord_y, color);
//		pixel_put(&img, x + cord_x, -1 * y + cord_y, color);
//		pixel_put(&img, -1 * x + cord_x, -1 * y + cord_y, color);
//		y++;
//		color += (1 << 18); }
}

void		put_circle_new(t_data img, int radius, int cord_x, int cord_y,
					   int color)
{
	int tmp;
	int cords[2];
	float rad;

	int x;
	int y;

	rad = 0;
	while (rad < 2 * PI)
	{

		x = sin(rad) * radius;
		y = cos(rad) * radius;
		pixel_put(&img, x + cord_x, y + cord_y, color);
		rad += 0.01;
		color += (1 << 9);
	}
}
