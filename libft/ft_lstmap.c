/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 00:03:22 by mehtel            #+#    #+#             */
/*   Updated: 2020/11/15 00:04:23 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	void	*data;

	while (lst)
	{
		if ((data = f(lst->content)))
			ft_lstadd_back(&new, ft_lstnew(data));
		else
		{
			ft_lstclear(&new, del);
			break ;
		}
		lst = lst->next;
	}
	return (new);
}
