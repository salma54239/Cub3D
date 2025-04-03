/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 05:50:48 by shadria-          #+#    #+#             */
/*   Updated: 2024/01/30 05:50:48 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	compare_sign_texture(char *line, char *ID)
{
	if (!line)
		return (0);
	if (*line == ID[0] && line[1] == ID[1] && is_wspace(line[2]))
		return (1);
	return (0);
}

char	*extract_path(char *line)
{
	int	i;

	i = 3;
	if (!line)
		return (NULL);
	while (line[i] && is_wspace(line[i]))
		i++;
	if (line[i] && (line[i] == '\n' || line[i] == '\0'))
		return (NULL);
	return (&line[i]);
}

void	delete_nline(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return ;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			break ;
		}
		i++;
	}
}

int	parse_texture(char *line, t_elements *ptr)
{
	char	**tmp;

	if (compare_sign_texture(line, "NO") && ptr->north_path == NULL)
		tmp = &(ptr->north_path);
	else if (compare_sign_texture(line, "WE") && ptr->west_path == NULL)
		tmp = &(ptr->west_path);
	else if (compare_sign_texture(line, "SO") && ptr->south_path == NULL)
		tmp = &(ptr->south_path);
	else if (compare_sign_texture(line, "EA") && ptr->east_path == NULL)
		tmp = &(ptr->east_path);
	else
		return (1);
	*tmp = extract_path(line);
	if (!*tmp)
		return (1);
	delete_nline(*tmp);
	return (0);
}
