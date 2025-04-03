/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:44:59 by ssaadaou          #+#    #+#             */
/*   Updated: 2024/01/30 05:49:06 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_line(char *save)
{
	char	*str;
	int		i;

	i = 0;
	if (!save || ft_strlen(save) == 0)
		return (NULL);
	str = malloc(ft_strlen(save) + 1);
	if (!str)
		return (NULL);
	while (save[i] && save[i] != '\n')
	{
		str[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*ft_save_buff(char *buffer)
{
	int		i;
	int		j;
	char	*buff;

	i = 0;
	j = 0;
	if (!buffer || ft_strlen(buffer) == 0)
		return (free(buffer), NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (i >= ft_strlen(buffer))
		return (free(buffer), NULL);
	buff = malloc(ft_strlen(buffer) - i + 1);
	if (!buff)
		return (NULL);
	if (ft_strchr(buffer))
		i++;
	while (buffer[i])
		buff[j++] = buffer[i++];
	buff[j] = '\0';
	return (free(buffer), buff);
}

char	*get_next_line(int fd)
{
	int			c;
	char		*s;
	static char	*save;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (1)
	{
		c = read(fd, buffer, BUFFER_SIZE);
		if (c < 0)
			return (free(buffer), free(save), save = NULL, NULL);
		buffer[c] = '\0';
		save = ft_strjoin(save, buffer);
		if (c == 0 || ft_strchr(save) == 1)
			break ;
	}
	free(buffer);
	s = ft_line(save);
	save = ft_save_buff(save);
	return (s);
}
