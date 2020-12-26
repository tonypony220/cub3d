/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 22:50:05 by mehtel            #+#    #+#             */
/*   Updated: 2020/12/02 22:50:09 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					reset(t_struc *d)
{
	free(d->buff);
	d->buff = 0;
	d->been = 0;
	d->k = 0;
	d->i = 0;
	d->stop = 0;
	return (1);
}

int						get_next_line(int fd, char **line)
{
	static t_struc		dict;
	static int			r;
	int					done;

	if (!dict.buff && !(dict.buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	dict.stop = BUFFER_SIZE + 1;
	while (1)
	{
		if (!dict.i)
			r = read(fd, dict.buff, BUFFER_SIZE);
		if (r < BUFFER_SIZE)
			dict.stop = r;
		done = process_buffer(line, &dict);
		if (done < 0 || !r || r < 0 || done == 2)
		{
			reset(&dict);
			if (done < 0 || r < 0 || !BUFFER_SIZE)
				return (-1);
			return (0);
		}
		if (done > 0)
			return (1);
	}
}
