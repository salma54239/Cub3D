/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:24:05 by ssaadaou          #+#    #+#             */
/*   Updated: 2024/01/30 05:48:57 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

void	print_list(t_list *head)
{
	t_list	*curr;

	curr = head;
	while (curr != NULL)
		curr = curr->next;
}

int	is_space_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_wspace(str[i]))
		i++;
	if (str[i] == '\0' || str[i] == '\n')
		return (1);
	return (0);
}

int	list_length(t_list *head)
{
	int		len;
	t_list	*curr;

	curr = head;
	len = 0;
	while (curr)
	{
		len++;
		curr = curr->next;
	}
	return (len);
}

int	fill_list(int fd, t_list **token)
{
	char	*line;

	line = NULL;
	line = get_next_line(fd);
	if (!line)
		return (error_msg(10), 1);
	while (line)
	{
		if (!is_space_str(line) && list_length(*token) <= 6)
			add_node_end(token, new_node(line));
		else if (list_length(*token) > 6)
			add_node_end(token, new_node(line));
		else
			free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

char	is_color_sign(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (is_wspace(line[i]))
			i++;
		if (line[i] == 'F' || line[i] == 'C')
			return (line[i]);
		else
			return (0);
	}
	return (0);
}
