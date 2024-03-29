/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 23:48:06 by mehtel            #+#    #+#             */
/*   Updated: 2020/11/14 23:49:18 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	char			*tmp;
	unsigned int	slen;

	slen = (unsigned int)ft_strlen((char*)s);
	len = start >= slen ? 0 : len;
	len = len && slen <= start + len ? slen - start : len;
	if ((str = malloc(sizeof(char) * (len + 1))))
	{
		tmp = str;
		while (start && start-- && *s)
			s++;
		while (len-- && *s)
			*tmp++ = *s++;
		*tmp = '\0';
	}
	return (str);
}
