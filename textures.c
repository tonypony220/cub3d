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
	vars->textures[tex_num] = mlx_xpm_file_to_image(vars->mlx, vars->map->texture_path[tex_num], &w, &h);
}
