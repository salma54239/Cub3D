/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:57:37 by ssaadaou          #+#    #+#             */
/*   Updated: 2024/01/30 05:48:41 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error_msg(int error)
{
	if (error == 0)
		ft_putstr_fd("Error: Invalid map\n", 2);
	else if (error == 1)
		ft_putstr_fd("Error: Invalid texture/color\n", 2);
	else if (error == 2)
		ft_putstr_fd("Error: Invalid map elements\n", 2);
	else if (error == 3)
		ft_putstr_fd("Error: Duplicate/not found player\n", 2);
	else if (error == 4)
		ft_putstr_fd("Error: Player/zero placed outside\n", 2);
	else if (error == 5)
		ft_putstr_fd("Error: Texture not found no_texture\n", 2);
	else if (error == 6)
		ft_putstr_fd("Error: Texture not found we_texture\n", 2);
	else if (error == 8)
		ft_putstr_fd("Error: Texture not found so_texture\n", 2);
	else if (error == 9)
		ft_putstr_fd("Error: Texture not found ea_texture\n", 2);
	else if (error == 10)
		ft_putstr_fd("Error Empty file\n", 2);
	else if (error == 11)
		ft_putstr_fd("Error No player position", 2);
	else if (error == 12)
		ft_putstr_fd("Error Invalid structure file", 2);
	return (0);
}

int	_error(int ac, char **av)
{
	int	fd;
	int	i;

	if (ac != 2)
	{
		ft_putstr_fd("Error: Incorrect number of arguments\n", 2);
		exit(1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Failed to open the .cub file\n", 2);
		close(fd);
		exit(1);
	}
	i = ft_strlen(av[1]);
	if (i < 4 || (av[1][i - 1] != 'b' || av[1][i - 2] != 'u' \
	|| av[1][i - 3] != 'c' || av[1][i - 4] != '.'))
	{
		ft_putstr_fd("Error : Incorrect name of file", 2);
		close(fd);
		exit(1);
	}
	return (fd);
}

void	info_player(char c, int i, int j, t_parameters *parm)
{
	parm->player = c;
	parm->player_x = j;
	parm->player_y = i;
}

int	check_duplicate(char **map, t_parameters *parm)
{
	int		i;
	int		j;
	int		players;
	char	c;

	players = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			c = map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				info_player(c, i, j, parm);
				players++;
			}
			j++;
		}
		i++;
	}
	if (players == 0 || players > 1)
		return (error_msg(3), 0);
	return (1);
}
