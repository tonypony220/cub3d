/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 19:07:45 by mehtel            #+#    #+#             */
/*   Updated: 2021/03/23 19:08:39 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	release_hook(int button, t_vars *vars)
{
	vars->btns[button] = 0;
	return (button);
}

int	press_hook(int button, t_vars *vars)
{
	if (button == ESC_BUTTON)
		vars->exit = 1;
	else
		vars->btns[button] = 1;
	return (button);
}

int	mouse_hook(t_vars *vars)
{
	vars->exit = 1;
	return (1);
}
