/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:17:21 by shadria-          #+#    #+#             */
/*   Updated: 2023/12/13 19:54:17 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_count_words(char *str, char separator)
{
	int	i;
	int	count;
	int	tmp;

	i = 0;
	count = 0;
	tmp = 1;
	while (str[i])
	{
		if (str[i] == separator)
			tmp = 1;
		if (str[i] != separator && tmp)
		{
			tmp = 0;
			count++;
		}
		i++;
	}
	return (count);
}

static int	ft_get_word_lenght(char *str, char separator, int i)
{
	int	j;

	j = 0;
	while (str[i] && str[i] != separator)
	{
		i++;
		j++;
	}
	return (j);
}

static char	**free_all(char **tab, int i)
{
	while (i--)
	{
		free(tab[i]);
	}
	free(tab);
	return (NULL);
}

char	*ft_get_next_word(char *str, char separator, int *i)
{
	int		index;
	char	*src;
	int		j;

	j = 0;
	index = *i;
	while (str[index] == separator)
		index++;
	src = malloc ((ft_get_word_lenght(str, separator, index) + 1)
			* sizeof(char));
	if (!src)
		return (NULL);
	while (str[index] && str[index] != separator)
	{
		src[j] = str[index];
		j++;
		index++;
	}
	src[j] = '\0';
	*i = index;
	return (src);
}

char	**ft_split(char const	*s, char c)
{
	int		i;
	char	**src;
	int		ma;
	int		sh;

	if (!s)
		return (NULL);
	i = 0;
	sh = 0;
	ma = ft_count_words((char *)s, c);
	src = malloc(sizeof(char *) * (ma + 1));
	if (!src)
		return (NULL);
	while (sh < ma)
	{
		src[sh] = ft_get_next_word((char *) s, c, &i);
		if (!src[sh])
			return (free_all(src, sh));
		sh++;
	}
	src[sh] = NULL;
	return (src);
}
