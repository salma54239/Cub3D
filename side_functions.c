/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 05:51:53 by shadria-          #+#    #+#             */
/*   Updated: 2024/01/30 05:51:53 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

char	*ft_substr(char *str, int start, int len)
{
	char	*substr;
	int		i;

	i = 0;
	if (!str)
		return (0);
	if (len > ft_strlen(str) - start)
		len = ft_strlen(str) - start;
	if (start >= ft_strlen(str))
		len = 0;
	substr = malloc(sizeof(char) * len + 1);
	if (!substr || !str)
		return (0);
	while (len-- > 0)
	{
		substr[i] = str[i + start];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

int	skip_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	skip_ws(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_wspace(str[i]))
		i++;
	while (str[i] && !is_wspace(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}
