/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color_element.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 05:52:04 by shadria-          #+#    #+#             */
/*   Updated: 2024/01/30 05:52:05 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_dimension(t_list *token, t_parameters *parm)
{
	t_list	*head;
	int		flag;

	flag = 0;
	head = token;
	parm->num_row = 0;
	while (head)
	{
		if (skip_space(head->data))
			flag++;
		else
			flag = 0;
		parm->num_row++;
		head = head->next;
	}
	parm->num_row -= flag;
	return (1);
}

int	is_digit_string(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	floor_ceiling(char *line, int i, t_elements *ptr)
{
	int	j;

	j = i;
	if (ptr->flag_c + ptr->flag_f >= 2)
		return (2);
	i++;
	while (line[i] && is_wspace(line[i]))
		i++;
	if (line[j] == 'F')
		return (ptr->flag_f += 1, parse_color(line + i, ptr, 'F'));
	else if (line[j] == 'C')
		return (ptr->flag_c += 1, parse_color(line + i, ptr, 'C'));
	return (0);
}

int	text_color_sign(char *line, t_elements *ptr)
{
	int	i;

	i = 0;
	while (line[i] && is_wspace(line[i]))
		i++;
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
	{
		if (ptr->flag_texture > 4)
			return (error_msg(1), 1);
		return (ptr->flag_texture += 1, parse_texture(line + i, ptr));
	}
	else if (line[i] == 'F' || line[i] == 'C')
	{
		if (floor_ceiling(line + i, i, ptr))
			return (error_msg(1), 1);
	}
	else
		return (printf("Error: invalid texture / color\n"), 1);
	return (0);
}
