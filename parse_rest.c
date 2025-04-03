/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 04:16:39 by ssaadaou          #+#    #+#             */
/*   Updated: 2024/01/30 05:50:14 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(char **map, int num_row)
{
	int	i;

	i = 0;
	while (i < num_row)
		free(map[i++]);
	free(map);
}

char	**parse_rest(t_list **token, t_elements *ptr)
{
	char	**map;

	map = NULL;
	init_args(ptr);
	if (!(*token))
		return (NULL);
	if (!parse_text_colors(&(*token), ptr))
		return (NULL);
	if (!check_map_elements(*token, ptr->parm) || \
	!get_dimension(*token, ptr->parm))
		return (NULL);
	map = fill_map(*ptr->parm, *token);
	if (check_duplicate(map, ptr->parm) == 0)
		return (free_split(map), NULL);
	else if (validate_map(map, *ptr->parm) == 1)
		return (free_split(map), NULL);
	return (map);
}
