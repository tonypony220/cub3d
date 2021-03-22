#include "cub3d.h"

void		put_player(t_vars *vars)
{
	t_ray	cords;
	int x;
	int line_len;

	init_player_screen(vars, &cords);
	x = -1;
	while (++x < vars->map->resolution_width)
	{
		init_ray(vars, &cords, x);
		find_ray_dir_and_initial_len(vars, &cords);
		cast_ray(vars, &cords);
		calculate_perp_dist(vars, &cords);
		//write(1, "HERE!\n", 6);
		line_len = (vars->map->resolution_hight * RESIZE  / cords.perpWallDist);
		if (cords.perpWallDist == 0)
			line_len = vars->map->resolution_hight;
		line_len = (int)(line_len * vars->win_k);
		vars->map->zbuf[x] = cords.perpWallDist;
		find_x_texture_cord(&cords, vars);
		put_textured_line(vars, line_len, &cords, x);
	}
	find_distanse_to_sprites(vars);
	selection_sorting_sprite(vars->map->sprites_dist,
							 vars->map->sprites_order,
							 vars->map->sprite_counter);
	project_sprites(vars, &cords);
}

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

	start_of_line = (vars->map->resolution_hight >> 1) - (line_len >> 1);
	//start_of_line = (int)(start_of_line * k);
	start_of_line *= start_of_line > 0;
	end_of_line = (vars->map->resolution_hight >> 1) + (line_len >> 1);
	if (end_of_line > vars->map->resolution_hight)
		end_of_line = (vars->map->resolution_hight - 1);
	shift = 1.0 * vars->texs[cords->cur_tex]->size[Y] / line_len;
	tex_pos = ((start_of_line - (vars->map->resolution_hight >> 1)
				+ (line_len >> 1)) * shift);
	while (start_of_line < end_of_line)
	{
		cords->tex[Y] = (int)tex_pos
						& (vars->texs[cords->cur_tex]->size[Y] - 1);
		tex_pos += shift;
		pixel_put(vars, x, start_of_line,
			*(int*)(vars->texs[cords->cur_tex]->addr
			+ vars->texs[cords->cur_tex]->line_length * cords->tex[Y]
			+ cords->tex[X] * vars->texs[cords->cur_tex]->bits_per_pixel / 8)
			+ vars->move);
		start_of_line++;
	}
}

