/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils11.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 04:44:12 by ssaadaou          #+#    #+#             */
/*   Updated: 2024/01/30 05:52:18 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = NULL;
	if (x < WIN_WIDTH && x > 0 && y > 0 && y < WIN_HEIGHT)
	{
		dst = data->addr + (y * data->line_length + \
		x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	my_map(t_data *img)
{
	mlx_clear_window(img->mlx, img->mlx_win);
	img->img = mlx_new_image(img->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (img->img == NULL)
		exit(1);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
	&img->line_length, &img->endian);
	if (!(img->addr))
		exit(1);
	if (img->walk_direction)
		go_straight(img);
	if (img->walk_direction_side)
		go_side(img);
	if (img->turn_direction)
		rotate(img);
	player(img, img->x, img->y);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	mlx_destroy_image(img->mlx, img->img);
	return (0);
}

void	initialize_player(t_data *img, char c, int x, int y)
{
	img->x = x * TILE_SIZE + TILE_SIZE / 2;
	img->y = y * TILE_SIZE + TILE_SIZE / 2;
	img->move_speed = 10;
	img->rotation_speed = 0.05;
	if (c == 'N')
		img->rotation_angle = M_PI / 2;
	else if (c == 'W')
		img->rotation_angle = M_PI;
	else if (c == 'S')
		img->rotation_angle = 3 * (M_PI / 2);
	else if (c == 'E')
		img->rotation_angle = 0;
}

int	take_player_postion(t_data *img)
{
	if (img->parm->player == 'N' || img->parm->player == 'S' || \
	img->parm->player == 'E' || img->parm->player == 'W')
	{
		initialize_player(img, img->parm->player, img->parm->player_x, \
		img->parm->player_y);
		return (1);
	}
	return (0);
}

void	dana_firit(t_data *img)
{
	img->mlx = NULL;
	img->mlx_win = NULL;
	img->img = NULL;
	img->addr = NULL;
	img->bits_per_pixel = 0;
	img->line_length = 0;
	img->endian = 0;
	img->x = 0;
	img->y = 0;
	img->rotation_angle = 0;
	img->rotation_speed = 0;
	img->move_speed = 0;
	img->i = 0;
	img->tab = NULL;
	img->walk_direction = 0;
	img->turn_direction = 0;
	img->walk_direction_side = 0;
}
