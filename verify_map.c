/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:05:55 by ssaadaou          #+#    #+#             */
/*   Updated: 2024/01/30 05:52:43 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

int	start_position_or_zero(char c)
{
	if ((c == 'W' || c == 'S' || c == 'E' || c == 'N'))
		return (1);
	else if (c == '0')
		return (2);
	return (0);
}

int	check_valid_position(char **map, int i, int j)
{
	if (!map[i] || !map[i][j])
		return (1);
	if (map[i][j] != '1' && !start_position_or_zero(map[i][j]))
		return (1);
	return (0);
}

int	check_aux(t_vars *vars, char **map, t_parameters parm)
{
	while (map[vars->i][++vars->j])
	{
		vars->c = map[vars->i][vars->j];
		if (start_position_or_zero(vars->c))
		{
			if ((vars->i == 0 && \
			start_position_or_zero(map[vars->i][vars->j])) || (vars->i == \
			parm.num_row - 1 && start_position_or_zero(map[vars->i][vars->j])))
				return (error_msg(4), 1);
			else if ((vars->j == 0 && \
			start_position_or_zero(map[vars->i][vars->j])))
				return (error_msg(4), 1);
			else if (check_valid_position(map, vars->i, vars->j + 1) || \
			check_valid_position(map, vars->i, vars->j - 1) || \
			check_valid_position(map, vars->i + 1, vars->j) || \
			check_valid_position(map, vars->i - 1, vars->j))
				return (error_msg(0), 1);
		}
	}
	return (0);
}

int	validate_map(char **map, t_parameters parm)
{
	t_vars	vars;

	vars.i = -1;
	if (!map || !*map)
		return (1);
	while (map[++vars.i])
	{
		vars.j = -1;
		if (check_aux(&vars, map, parm))
			return (1);
	}
	return (0);
}
