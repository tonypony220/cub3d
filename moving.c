#include "cub3d.h"

int			wall_crossed(t_vars *vars, double x, double y)
{
	char 	val;

	val = *(vars->map->map + (int)x + ((int)y * vars->map->width));
	if (!ft_strchr("0N2", val))
		return (1);
	return (0);
}

double 	map_move_with_buttons(int button, int axis)
{
	double move_val;

	move_val = 1.0;

	if (button == W_BUTTON && axis == Y)
		return (move_val);
	if (button == A_BUTTON && axis == X)
		return (-move_val);
	if (button == S_BUTTON && axis == Y)
		return (-move_val);
	if (button == D_BUTTON && axis == X)
		return (move_val);
	return (0);

}

void move_player(t_vars *vars, int button)
{
	double move_val = 0.08; //RESIZE / 12;
	double move[2];
	move[X] = move_val // * RESIZE / 12
			  * map_move_with_buttons(button, Y) * sin(vars->player[RAD])
			  + move_val
				* map_move_with_buttons(button, X) * cos(vars->player[RAD]);
	move[Y] = move_val // * RESIZE / 12
			  * map_move_with_buttons(button, Y) * cos(vars->player[RAD])
			  + move_val
				* map_move_with_buttons(button, X) * -sin(vars->player[RAD]);
	vars->player[X] += move[X]
					   * !wall_crossed(vars,
									   vars->player[X] + move[X] * 2,
									   vars->player[Y]);
	vars->player[Y] += move[Y]
					   * !wall_crossed(vars,
									   vars->player[X],
									   vars->player[Y] + move[Y] * 2);
}

void moving(t_vars *vars)
{
	if (vars->btns[LEFT_BUTTON])
		vars->player[RAD] += 0.04;
	if (vars->btns[RIGHT_BUTTON])
		vars->player[RAD] -= 0.04;
	if (vars->btns[W_BUTTON])
		move_player(vars, W_BUTTON);
	if (vars->btns[A_BUTTON])
		move_player(vars, A_BUTTON);
	if (vars->btns[S_BUTTON])
		move_player(vars, S_BUTTON);
	if (vars->btns[D_BUTTON])
		move_player(vars, D_BUTTON);
}
