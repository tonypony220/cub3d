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
	if (!(vars->textures[i] = ft_calloc(sizeof(int) * TEX_HEGHT * TEX_WIDTH, 1)))
		return ;
	while (++y < TEX_HEGHT)
	{
		x = -1;
		while (++x < TEX_WIDTH)
		{
			xorcolor = (x * 256 / TEX_WIDTH) ^ (y * 256 / TEX_HEGHT);
			*(vars->textures[i] + TEX_WIDTH * y + x) = xorcolor + 256
					  	                   * xorcolor + 65536 * xorcolor;
			//	pixel_put(vars, x, y,
			//			  *(vars->textures[0] + TEX_HEGHT * y + x));
		}
	}
	//write(1, "HELL\n", 5);
}

void load_textures(t_vars *vars)
{
	return ;
}
