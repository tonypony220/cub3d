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
			pixel_put(vars, x, y, color);
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
			pixel_put(vars, x, y, color);
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
			pixel_put(vars, j, jj, clr);
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
		pixel_put(vars, x, y_up, color);
		y_up++;
	}
}

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
	int counter[2];  /// del
	int rays = vars->map->resolution_width;

	counter[0] = 0;
	counter[1] = 0;
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
				pixel_put(vars, (int) cords.on_map[X],
						  (int) cords.on_map[Y],
						  color);
			}
			pixel_put(vars, (int) cords.on_map[X],
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

	//	color2 = 0xBBbfbbbb;
	//	if (cords.side == 1)
	//		color2 = 0xBBa19d9d;
	//	color2 -= x / 10;

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
		vars->map->zbuf[x] = cords.perpWallDist;
		find_x_texture_cord(&cords, vars);
		put_textured_line(vars, line_len, &cords, x);
		find_distanse_to_sprites(vars);
		selection_sorting_sprite(vars->map->sprites_dist,
								 vars->map->sprites_order,
								 vars->map->sprite_counter);
		project_sprite(vars);
	}
}


// 0000
// 0001
// 0010
// 0011
// 0100 4
// 0101 5
// 0110 6
// 0111 7
int		get_pole_by_ray_dir(t_ray *cords)
{
	int ret;

	if (cords->side == X)  // EAST
		ret = (cords->ray_dir[X] > 0) ? EA : WE;
	else
		ret = (cords->ray_dir[Y] < 0) ? NO : SO;
	return (ret);

}

void			find_x_texture_cord(t_ray *cords, t_vars *vars)
{
	cords->cur_tex = get_pole_by_ray_dir(cords);
	cords->on_wall = vars->player[!cords->side]
			+ cords->perpWallDist * cords->ray_dir[!cords->side];
	cords->on_wall -= floor((cords->on_wall));
	cords->tex[X] = (int)(cords->on_wall
						* (double)vars->texs[cords->cur_tex]->size[X]);// / RESIZE)
	if (cords->cur_tex == EA || cords->cur_tex == NO)
		cords->tex[X] = TEX_WIDTH - cords->tex[X] - 1;
}

void			put_textured_line(t_vars *vars, int line_len,
						          t_ray *cords, int x)
{
	double		shift;
	double		tex_pos;
	int			start_of_line;
	int			end_of_line; // not same as used for vertical line in tutorial
	int			tex_num;

	tex_num = cords->cur_tex;
	start_of_line = (vars->map->resolution_hight >> 1) - (line_len >> 1);
	start_of_line *= start_of_line > 0;
	end_of_line = (vars->map->resolution_hight >> 1) + (line_len >> 1);
	if (end_of_line > vars->map->resolution_hight)
		end_of_line = (vars->map->resolution_hight - 1);
	shift = 1.0 * vars->texs[tex_num]->size[Y] / line_len;
	tex_pos = ((start_of_line - (vars->map->resolution_hight >> 1)
				+ (line_len >> 1)) * shift);
	while (start_of_line < end_of_line)
	{
		cords->tex[Y] = (int)tex_pos & (vars->texs[tex_num]->size[Y] - 1);
		tex_pos += shift;
		pixel_put(vars, x, start_of_line,
			*(int*)(vars->texs[tex_num]->addr
			+ vars->texs[tex_num]->line_length * cords->tex[Y]
			+ cords->tex[X] * vars->texs[tex_num]->bits_per_pixel / 8)
			+ vars->move);
		start_of_line++;
	}
}

void			find_distanse_to_sprites(t_vars *vars)
{
	int			i;

	i = -1;
	while (++i < vars->map->sprite_counter)
	{
		vars->map->sprites_order[i] = i;
		vars->map->sprites_dist[i] =
				(pow(vars->player[X] - vars->map->sprites[i].cord[X], 2))
				+ (pow(vars->player[Y] - vars->map->sprites[i].cord[Y], 2));
	}
}

void			project_sprites(t_vars *vars, t_ray *cords)
{
	int i;
	double invert;
	t_spr sprite;

	i = -1;
	while (++i < vars->map->sprite_counter)
	{
		sprite.relative_cord[X] =
				vars->map->sprites[vars->map->sprites_order[i]].cord[X]
				- vars->player[X];
		sprite.relative_cord[Y] =
				vars->map->sprites[vars->map->sprites_order[i]].cord[Y]
				- vars->player[Y];
		invert = 1.0 / (cords->plane[Y] * cords->ray_dir[Y]
					- cords->ray_dir[X] * cords->plane[Y]);
		sprite.transform[X] = invert
				* (cords->ray_dir[Y] * sprite.relative_cord[X]
					- cords->ray_dir[X] * sprite.relative_cord[Y]);
		sprite.transform[Y] = invert
				* (-cords->plane[Y] * sprite.relative_cord[X]
					+ cords->plane[X] * sprite.relative_cord[Y]);
		sprite.screen[X] = (int)(vars->map->resolution_width / 2)
				* (1 + sprite.transform[X] / sprite.transform[Y]);
		find_projection_size(vars, cords, sprite);
	}
}

void			find_projection_size(t_vars *vars, t_ray *cords, t_spr *sprite)
{
	int h;

	h = vars->map->resolution_hight;

	sprite->height = abs((int)(h / sprite->transform[Y]));
	sprite->draw[Y][0] = -(sprite->height >> 1) + (h >> 1);
	sprite->draw[Y][0] *= sprite->draw[Y][0] >= 0;
	sprite->draw[Y][1] = (sprite->height >> 1) + (h >> 1);
	if (sprite->draw[Y][1] >= h)
		sprite->draw[Y][1] = h - 1;
	sprite->width = sprite->height;//abs((int)(h / sprite->transform[Y]));
	sprite->draw[X][0] = -(sprite->width >> 1) + sprite->screen[X];
	sprite->draw[X][0] *= sprite->draw[X][0] >= 0;
	sprite->draw[X][1] = (sprite->width >> 1) + sprite->screen[X];
	if (sprite->draw[X][1] >= vars->map->resolution_width)
		sprite->draw[X][1] = vars->map->resolution_width - 1;
}

void			draw_sprite(t_vars *vars, t_ray *cords, t_spr *sprite)
{
	int tex[2];
	int color;
	int d;

	while (sprite->draw[X][0] < sprite->draw[X][1])
	{
		tex[X] = (int)(256
				* (sprite->draw[X][0]
				- ((-sprite->width >> 1) + sprite->screen[X])
				* vars->texs[S]->size[Y] / sprite->width) / 256);
		if (sprite->transform[Y] > 0
			&& sprite->draw[X][0] > 0
			&& sprite->draw[X][0] < vars->map->resolution_width
			&& sprite->transform[Y] < vars->map->zbuf[sprite->draw[X][0]])
		{
			while (sprite->draw[Y][0] < sprite->draw[Y][1])
			{
				d = sprite->draw[Y][0] * 256 - vars->map->resolution_hight
						* 128 + sprite->height * 128;
				tex[Y] = ((d * vars->texs[S]->size[Y]) / sprite->height) / 256;
				color =
				sprite->draw[Y][0]++;
			}

		}



		sprite->draw[X][0]++;
	}
}
//loop through every vertical stripe of the sprite on screen
for(int stripe = drawStartX; stripe < drawEndX; stripe++)
{
//the conditions in the if are:
//1) it's in front of camera plane so you don't see things behind you
//2) it's on the screen (left)
//3) it's on the screen (right)
//4) ZBuffer, with perpendicular distance
if(transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
{
int d = (y) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
int texY = ((d * texHeight) / spriteHeight) / 256;
Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
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
