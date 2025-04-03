/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side_funct_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 04:28:02 by ssaadaou          #+#    #+#             */
/*   Updated: 2024/01/30 05:51:40 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

void	init_args(t_elements *ptr)
{
	ptr->east_path = NULL;
	ptr->north_path = NULL;
	ptr->south_path = NULL;
	ptr->west_path = NULL;
	ptr->flag_c = 0;
	ptr->flag_f = 0;
	ptr->flag_texture = 0;
	ptr->parm->player = 0;
	ptr->parm->player_x = 0;
	ptr->parm->player_y = 0;
	ptr->fl_ceil = 0;
	ptr->fl_floor = 0;
}

int	check_map_elements(t_list *token, t_parameters *parm)
{
	int	i;

	while (token && token->data)
	{
		i = 0;
		while (token->data[i])
		{
			if (token->data[i] == '\n' && token->data[i + 1] == '\0')
			{
				token->data[i] = '\0';
				break ;
			}
			if (token->data[i] != '1' && token->data[i] != '0' \
			&& token->data[i] != ' ' && \
			token->data[i] != 'W' \
			&& token->data[i] != 'E' && token->data[i] != 'S' && \
			token->data[i] != 'N')
				return (error_msg(2));
			if (parm->max_len_line < i && token->data[i] != ' ')
				parm->max_len_line = i;
			i++;
		}
		token = token->next;
	}
	return (1);
}
