#include "cub3d.h"

void generate_textures(t_vars *vars)
{
	int x;
	int y;
	int i;
	int xorcolor;

	i = 0;
	y = -1;
	/// if (!vars->textures[i])
	printf("tex width = %d tex_height = %d\n", TEX_WIDTH, TEX_HEGHT);
	if (!(vars->textures[i] = ft_calloc(sizeof(int) * TEX_HEGHT * TEX_WIDTH, 1)))
		return ;
	while (++y < TEX_HEGHT)
	{
		x = -1;
		while (++x < TEX_WIDTH)
		{
			int xycolor = y * 128 / TEX_HEGHT + x * 128 / TEX_WIDTH;
			xorcolor = (x * 256 / TEX_WIDTH) ^ (y * 256 / TEX_HEGHT);
			*(vars->textures[i] + TEX_WIDTH * y + x) = xorcolor + 256
					  	                   * xorcolor + 65536 * xorcolor;
		//	*(vars->textures[i] + TEX_WIDTH * y + x) = 256 * xorcolor;


		}
	}
}

void load_texture(t_vars *vars, char tex_num)

{
	//void    *mlx_png_file_to_image(void *mlx_ptr, char *file, int *width, int *height);
	int w;
	int h;
	w = TEX_WIDTH;
	h = TEX_HEGHT;
	void *img;

	vars->texs[tex_num] = ft_calloc(sizeof(t_data), 1);
	printf("tex path [%d] '%s'\n", tex_num, vars->map->texture_path[tex_num]);
	int fd = open(vars->map->texture_path[tex_num], O_RDONLY);
	printf("fd %d\n", fd);
	vars->texs[tex_num]->img = mlx_png_file_to_image(vars->mlx, vars->map->texture_path[tex_num], &w, &h);
	printf("ret %p\n", vars->texs[tex_num]->img);
	//vars->textures[tex_num] = mlx_get_data_addr(vars->texs[tex_num]->img,
	//							 &vars->texs[tex_num]->bits_per_pixel,
	//							 &vars->texs[tex_num]->line_length,
	//							 &vars->texs[tex_num]->endian);
}
