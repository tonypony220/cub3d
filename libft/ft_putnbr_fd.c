/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 23:58:32 by mehtel            #+#    #+#             */
/*   Updated: 2020/11/14 23:58:42 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int sign;

	sign = n >= 0 ? 1 : -1;
	(sign < 0) ? ft_putchar_fd('-', fd) : sign;
	if (n > 10 || n < 0)
		ft_putnbr_fd((n / 10) * sign, fd);
	ft_putchar_fd(((n % 10) * sign) + '0', fd);
}
