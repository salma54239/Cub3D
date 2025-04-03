/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_text_colors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 04:12:19 by ssaadaou          #+#    #+#             */
/*   Updated: 2024/01/30 05:50:19 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

int	extract_color(int *color, char **c_value)
{
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	color[0] = ft_atoi(c_value[0]);
	color[1] = ft_atoi(c_value[1]);
	color[2] = ft_atoi(c_value[2]);
	if ((color[0] < 0 || color[0] > 255) || (color[1] < 0 || \
	color[1] > 255) || (color[2] < 0 || color[2] > 255))
		return (free_split(c_value), 1);
	return (0);
}

int	parse_color(char *line, t_elements *ptr, char type)
{
	int		color[3];
	char	**c_value;
	int		i;

	c_value = NULL;
	if (count_commas(line) != 2)
		return (1);
	delete_nline(line);
	i = -1;
	while (line[++i])
		if ((line[i] > '9' || line[i] < '0') && line[i] != ',')
			return (1);
	c_value = ft_split(line, ',');
	if (!c_value || !c_value[0] || !c_value[1] || !c_value[2] || c_value[3])
		return (free_split(c_value), 1);
	if (!is_digit_string(c_value[0]) || \
	!is_digit_string(c_value[1]) || !is_digit_string(c_value[2]))
		return (free_split(c_value), 1);
	if (extract_color(color, c_value))
		return (1);
	if (type == 'F')
		ptr->fl_floor = rgb_to_int(color[0], color[1], color[2]);
	else
		ptr->fl_ceil = rgb_to_int(color[0], color[1], color[2]);
	return (free_split(c_value), 0);
}

int	parse_text_colors(t_list **token, t_elements *ptr)
{
	while ((*token) && (*token)->data && !is_map_elements((*token)->data))
	{
		if (text_color_sign((*token)->data, ptr))
			return (error_msg(12), 0);
		(*token) = (*token)->next;
	}
	if (ptr->flag_c != 1 || ptr->flag_f != 1 || (ptr->flag_texture != 4))
		return (error_msg(12), 0);
	return (1);
}
