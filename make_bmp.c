#include "cub3d.h"

typedef struct  s_params
{
	int 		height;
	int 		width;
	int 		bpp;

}               t_params;

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(c));
}

void	write_bytes_to_fd(int fd, int num, int len)
{
	unsigned char byte;
	int i;

	i = -1;
	while (++i < len)
	{
		byte = (unsigned char)(num >> (i * 8) );
		ft_putchar_fd(byte, fd);
	}
}

void	put_header( int fd, t_params params)
{
	int filesize;

	filesize = 54 + params.width * params.height * (params.bpp >> 3);
	write(fd, "BM", 2);
	write_bytes_to_fd(fd, filesize, 4);  /// FILESIZE 4
	write_bytes_to_fd(fd, 0, 4);   /// RESERVED 2 * 2
	write_bytes_to_fd(fd, 54, 4);  /// PIXEL DATA OFFSEt 2 * 2
	write_bytes_to_fd(fd, 40, 4);  /// HEADER SIZE 4
	write_bytes_to_fd(fd, params.width, 4);  /// IMG WIDTH 4
	write_bytes_to_fd(fd, params.height, 4);  /// IMG HEIGHT 4
	write_bytes_to_fd(fd, 1, 2);  /// PLANES 2
	write_bytes_to_fd(fd, params.bpp, 2); /// BITS PER PIXEL 2
	write_bytes_to_fd(fd, 0, 4);  /// Compression	4 bytes	0x00 0x00 0x00 0x00
	write_bytes_to_fd(fd, 0, 4);  /// ImageSize	4 bytes	0x00 0x00 0x00 0x00
	write_bytes_to_fd(fd, 0, 4);  /// XpixelsPerMeter	4 bytes	0x00 0x00 0x00 0x00
	write_bytes_to_fd(fd, 0, 4);  /// YpixelsPerMeter	4 bytes	0x00 0x00 0x00 0x00
	write_bytes_to_fd(fd, 0, 4);  /// TotalColors	4 bytes	0x00 0x00 0x00 0x00
	write_bytes_to_fd(fd, 0, 4);  /// ImportantColors	4 bytes	0x00 0x00 0x00 0x00
}

void	put_image(int fd, t_params params, char *img)
{
	int color;
	int x;
	int y;

	y = params.height;
	while (y--)
	{
		x = -1;
		while (++x < params.width)
		{
			color = *(int*)(img + y * params.width + x * 4);
			write_bytes_to_fd(fd, color, (params.bpp >> 3));
		}
		write_bytes_to_fd(fd, 0, (4 - (params.width * (params.bpp >> 3) % 4)));
	}
}

void	invert_img(char *img, char *inverted, t_params params)
{
	int y;
	int x;
	int line_len;

	line_len = params.width * (params.bpp >> 3);
	y = -1;
	while (++y < params.height)
	{
		x = -1;
		while (++x < line_len)
			*(inverted + (params.height - 1 - y) * line_len + x)
			= *(img + y * line_len + x);

	}
}

void	create_bmp_file(char *img, char *filename, int w, int h, int bpp)
{
	int fd;
	t_params params;
	char *inverted;

	if (!(inverted = ft_calloc(sizeof(char), h * w * (bpp >> 3))))
		return ;

	params.bpp = bpp;
	params.height = h;
	params.width = w;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	put_header(fd, params);
	invert_img(img, inverted, params);
	write(fd, inverted, h * w * (bpp >> 3));
	free(inverted);
	close(fd);
}
