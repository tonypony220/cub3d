#include "cub3d.h"

void			find_distanse_to_sprites(t_vars *vars)
{
	int			i;

	i = -1;
	while (++i < vars->map->sprite_counter)
	{
		vars->map->sprites_order[i] = i;
		vars->map->sprites_dist[i] =
				(float)(pow(vars->player[X] - vars->map->sprites[i].cord[X], 2))
				+ (float)(pow(vars->player[Y] - vars->map->sprites[i].cord[Y], 2));
	}
}

void			project_sprites(t_vars *vars, t_ray *cd)
{
	int i;
	double invert;
	int *ord;
	t_spr spr;

	i = -1;
	ord = vars->map->sprites_order;
	while (++i < vars->map->sprite_counter)
	{
		spr.cr[X] = vars->map->sprites[ord[i]].cord[X] - vars->player[X];
		spr.cr[Y] = vars->map->sprites[ord[i]].cord[Y] - vars->player[Y];
		invert = 1.0 /
				 (cd->plane[X] * cd->dir[Y] - cd->dir[X] * cd->plane[Y]);
		spr.transform[X] = invert
						   * (cd->dir[Y] * spr.cr[X] - cd->dir[X] * spr.cr[Y]);
		spr.transform[Y] = invert
						   * (-cd->plane[Y] * spr.cr[X]
						   + cd->plane[X] * spr.cr[Y]);
		if (spr.transform[Y] < 0)
			continue;
		spr.screen[X] = (int)((vars->map->resolution_width >> 1)
							  * (1 + spr.transform[X] / spr.transform[Y]));
		find_projection_size(vars, cd, &spr);
		draw_sprite(vars, cd, &spr);
	}
}

void			find_projection_size(t_vars *vars, t_ray *cords, t_spr *spr)
{
	int h;

	h = vars->map->resolution_hight;
	spr->height = abs((int)(h / spr->transform[Y] * (double)vars->win_k));
	spr->draw[Y][0] = -(spr->height >> 1) + (h >> 1);
	spr->draw[Y][0] *= spr->draw[Y][0] >= 0;
	spr->draw[Y][1] = (spr->height >> 1) + (h >> 1);
	if (spr->draw[Y][1] >= h)
		spr->draw[Y][1] = h - 1;
	spr->width = abs((int)(h / spr->transform[Y] * (double)vars->win_k));
	spr->draw[X][0] = -(spr->width >> 1) + spr->screen[X];
	spr->draw[X][0] *= spr->draw[X][0] >= 0;
	spr->draw[X][1] = (spr->width >> 1) + spr->screen[X];
	if (spr->draw[X][1] >= vars->map->resolution_width)
		spr->draw[X][1] = vars->map->resolution_width - 1;
}

void 			draw_vertical_of_sprite(t_vars *vars, t_spr *spr, int *tex,
										int startY)
{
	int color;
	int d;

	spr->draw[Y][0] = startY;
	while (spr->draw[Y][0]++ < spr->draw[Y][1] - 1)
	{
		d = (spr->draw[Y][0]) * 256 - vars->map->resolution_hight
									  * 128 + spr->height * 128;
		tex[Y] = ((d * vars->texs[S]->size[Y]) / spr->height) / 256;
		color = *(int*)(vars->texs[S]->addr +
						+ vars->texs[S]->line_length * tex[Y]
						+ tex[X] * vars->texs[S]->bits_per_pixel / 8);
		if ((color & 0x00FFFFFF) != 0)
			pixel_put(vars, spr->draw[X][0], spr->draw[Y][0], color);
	}
}

void			draw_sprite(t_vars *vars, t_ray *cords, t_spr *spr)
{
	int tex[2];
	int tmpstartY;

	tmpstartY = spr->draw[Y][0];
	while (spr->draw[X][0] < spr->draw[X][1])
	{
		tex[X] = (int)(256 * (spr->draw[X][0]
							  - (-spr->width / 2 + spr->screen[X]))
					   * vars->texs[S]->size[Y] / spr->width) / 256;
		if (spr->draw[X][0] > -1
			&& spr->draw[X][0] < vars->map->resolution_width
			&& spr->transform[Y] < vars->map->zbuf[spr->draw[X][0]])
		{
			draw_vertical_of_sprite(vars, spr, tex, tmpstartY);
		}
		spr->draw[X][0]++;
	}
}
