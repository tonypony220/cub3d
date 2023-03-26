/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 20:10:10 by mehtel            #+#    #+#             */
/*   Updated: 2021/03/23 20:11:08 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				write_bytes_to_fd(int fd, int num, int len)
{
	unsigned char	byte;
	int				i;

	i = -1;
	while (++i < len)
	{
		byte = (unsigned char)(num >> (i * 8));
		ft_putchar_fd(byte, fd);
	}
}

void				put_header(int fd, t_params params)
{
	int				filesize;

	filesize = 54 + params.width * params.height * (params.bpp >> 3);
	write(fd, "BM", 2);
	write_bytes_to_fd(fd, filesize, 4);
	write_bytes_to_fd(fd, 0, 4);
	write_bytes_to_fd(fd, 54, 4);
	write_bytes_to_fd(fd, 40, 4);
	write_bytes_to_fd(fd, params.width, 4);
	write_bytes_to_fd(fd, params.height, 4);
	write_bytes_to_fd(fd, 1, 2);
	write_bytes_to_fd(fd, params.bpp, 2);
	write_bytes_to_fd(fd, 0, 4);
	write_bytes_to_fd(fd, 0, 4);
	write_bytes_to_fd(fd, 0, 4);
	write_bytes_to_fd(fd, 0, 4);
	write_bytes_to_fd(fd, 0, 4);
	write_bytes_to_fd(fd, 0, 4);
}

void				invert_img(char *img, char *inverted, t_params params)
{
	int				y;
	int				x;
	int				line_len;

	line_len = params.width * (params.bpp >> 3);
	y = -1;
	while (++y < params.height)
	{
		x = -1;
		while (++x < line_len)
			*(inverted + (params.height - 1 - y) * line_len + x) =
					*(img + y * line_len + x);
	}
}

void				create_bmp_file(char *img, char *filename,
									int *size, int bpp)
{
	int				fd;
	char			*inverted;
	t_params		params;

	if (!(inverted = ft_calloc(sizeof(char), size[X] * size[Y] * (bpp >> 3))))
		return ;
	params.bpp = bpp;
	params.height = size[X];
	params.width = size[Y];
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	put_header(fd, params);
	invert_img(img, inverted, params);
	write(fd, inverted, params.height * params.width * (bpp >> 3));
	free(inverted);
	close(fd);
}
