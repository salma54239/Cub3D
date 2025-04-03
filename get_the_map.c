/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_the_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 05:53:10 by shadria-          #+#    #+#             */
/*   Updated: 2024/01/30 05:53:10 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

int	is_map_elements(char *map)
{
	int	i;

	i = 0;
	while (map[i] && map[i] == ' ')
		i++;
	if (map[i] == '1' || map[i] == '0')
		return (1);
	return (0);
}

void	fill_space(char *map, int len)
{
	int	i;

	i = 0;
	while (i < len)
		map[i++] = ' ';
	map[i] = '\0';
}

char	**fill_map(t_parameters parm, t_list *token)
{
	char	**map;
	int		i;
	int		j;
	t_list	*head;

	i = 0;
	head = token;
	map = malloc((parm.num_row + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	while (map && parm.num_row > i)
	{
		map[i] = malloc((parm.max_len_line + 1) * sizeof(char));
		if (!map[i])
			return (NULL);
		fill_space(map[i], parm.max_len_line + 1);
		j = -1;
		while (head->data[++j] && j <= parm.max_len_line)
			map[i][j] = head->data[j];
		head = head->next;
		i++;
	}
	return (map[parm.num_row] = NULL, map);
}
