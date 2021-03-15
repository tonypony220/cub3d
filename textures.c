#include "cub3d.h"

int generate_texture(t_vars *vars, char tex_num)
{
	int x;
	int y;
	int xorcolor;

	y = -1;
	if (!(vars->texs[tex_num] = ft_calloc(sizeof(t_data), 1))
	 || !(vars->texs[tex_num]->addr = (char *)ft_calloc(
			sizeof(int) * TEX_HEGHT * TEX_WIDTH, 1)))
		return (0);
	//printf("tex width = %d tex_height = %d\n", TEX_WIDTH, TEX_HEGHT);
	vars->texs[tex_num]->bits_per_pixel = 32;
	vars->texs[tex_num]->line_length = TEX_WIDTH
			* vars->texs[tex_num]->bits_per_pixel;
	vars->texs[tex_num]->size[X] = TEX_WIDTH;
	vars->texs[tex_num]->size[Y] = TEX_HEGHT;
	while (++y < TEX_HEGHT)
	{
		x = -1;
		while (++x < TEX_WIDTH)
		{
			/* */
			//int xycolor = y * 128 / TEX_HEGHT + x * 128 / TEX_WIDTH;
			xorcolor = (x * 256 / TEX_WIDTH) ^ (y * 256 / TEX_HEGHT);
			*(int*)(vars->texs[tex_num]->addr
			+ vars->texs[tex_num]->line_length * y + x * 4)
				= xorcolor + 256 * xorcolor + 65536 * xorcolor;
		//	*(vars->textures[i] + TEX_WIDTH * y + x) = 256 * xorcolor;


		}
	}
	return (1);
}

int load_textures(t_vars *vars)
{
	char i;

	i = -1;
	while (++i < NUM_MAP_PATHS)
	{
		if (!load_texture(vars, i) && BEHAVE_HARD)
			return (0);
		else
		{
			if (!generate_texture(vars, i))
				return (0);
		}
	}
	return (1);
}


int load_texture(t_vars *vars, char tex_num)

{
	//void    *mlx_png_file_to_image(void *mlx_ptr, char *file, int *width, int *height);
	int w;
	int h;
	w = 0;
	h = 0;
	void *img;

	vars->texs[tex_num] = ft_calloc(sizeof(t_data), 1);
	printf("tex path [%d] '%s'\n", tex_num, vars->map->texture_path[tex_num]);
	int fd = open(vars->map->texture_path[tex_num], O_RDONLY);
	printf("w %d\n", w);

	if (ft_strnstr(vars->map->texture_path[tex_num], ".png", 100))
		vars->texs[tex_num]->img = mlx_png_file_to_image(
				vars->mlx, vars->map->texture_path[tex_num], &w, &h);

	else
		vars->texs[tex_num]->img = mlx_xpm_file_to_image(
				vars->mlx, vars->map->texture_path[tex_num], &w, &h);

	if (!vars->texs[tex_num]->img)
		return (0);
	vars->texs[tex_num]->size[X] = w;
	vars->texs[tex_num]->size[Y] = h;

//	printf("w %d\n", w);
//	printf("ret %p\n", vars->texs[tex_num]->img);
	vars->texs[tex_num]->addr = mlx_get_data_addr(vars->texs[tex_num]->img,
								 &vars->texs[tex_num]->bits_per_pixel,
								 &vars->texs[tex_num]->line_length,
								 &vars->texs[tex_num]->endian);

	printf("TEX [%d] W=%d, H=%d, bits %d, len %d", tex_num, w, h, vars->texs[tex_num]->bits_per_pixel, vars->texs[tex_num]->line_length);
	return (1);
}
