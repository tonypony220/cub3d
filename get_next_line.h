/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 22:50:21 by mehtel            #+#    #+#             */
/*   Updated: 2020/12/02 22:50:24 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>

typedef struct		s_struc
{
	int				been;
	long int		stop;
	char			*buff;
	long			i;
	long			k;
	int				processed;
}					t_struc;

int					process_buffer(char **line, t_struc *dict);
int					get_next_line(int fd, char **line);
void				*ft_memcpy(void *dst, const void *src, size_t n);
int					reset(t_struc *d);
void				move_to_new_line(t_struc *dict, char *new_line,
					char **line, long int add_len);
#endif
