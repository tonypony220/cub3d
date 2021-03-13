/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 22:49:53 by mehtel            #+#    #+#             */
/*   Updated: 2020/12/02 22:49:57 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void				*ft_memcpy(void *dst, const void *src, size_t n)
{
	if (dst || src)
	{
		while (n--)
			((unsigned char*)dst)[n] = ((unsigned char*)src)[n];
	}
	return (dst);
}

void				move_to_new_line(t_struc *dict, char *new_line,
					char **line, long int add_len)
{
	ft_memcpy(new_line, *line, dict->k);
	if ((*dict).been && (*dict).k)
		free(*line);
	while (add_len--)
		new_line[dict->k++] = dict->buff[dict->i++];
	new_line[dict->k] = '\0';
	*line = new_line;
	dict->been = 1;
}

int					process_buffer(char **line, t_struc *dict)
{
	long int		add_len;
	char			*new_line;

	add_len = 0;
	while ((dict->i + add_len) < BUFFER_SIZE
			&& dict->i + add_len < dict->stop
			&& dict->buff[dict->i + add_len] != '\n')
		add_len++;
	if (!(new_line = malloc(sizeof(char) * (dict->k + add_len + 1))) ||
			(!line && !(new_line[dict->k] = '\0')))
		return (-1);
	move_to_new_line(dict, new_line, line, add_len);
	if (dict->i < dict->stop && dict->buff[dict->i] == '\n' && !(dict->k = 0))
		(dict->i)++;
	if (dict->i >= BUFFER_SIZE || dict->i >= dict->stop)
	{
		if (dict->i >= dict->stop && dict->k)
			return (2);
		(*dict).i = 0;
	}
	if (dict->k)
		return (0);
	return (1);
}
