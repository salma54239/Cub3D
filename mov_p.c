/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_p.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 05:05:41 by shadria-          #+#    #+#             */
/*   Updated: 2024/01/29 19:38:17 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_data *img)
{
	if (key == 53)
		exit(0);
	if (key == 13)
		img->walk_direction = 1;
	if (key == 1)
		img->walk_direction = -1;
	if (key == 0)
		img->walk_direction_side = -1;
	if (key == 2)
		img->walk_direction_side = 1;
	if (key == 123)
		img->turn_direction = -1;
	if (key == 124)
		img->turn_direction = 1;
	return (0);
}

int	key_release(int key, t_data *img)
{
	if (key == 13)
		img->walk_direction = 0;
	if (key == 1)
		img->walk_direction = 0;
	if (key == 0)
		img->walk_direction_side = 0;
	if (key == 2)
		img->walk_direction_side = 0;
	if (key == 123)
		img->turn_direction = 0;
	if (key == 124)
		img->turn_direction = 0;
	return (0);
}

void	go_straight(t_data *img)
{
	if (img->tab[((int)(img->y + img->move_speed * \
	sin(img->rotation_angle) * img->walk_direction) / \
	TILE_SIZE)][((int)(img->x + img->move_speed * \
	cos(img->rotation_angle) * img->walk_direction) / TILE_SIZE)] != '1' &&
	img->tab[((int)(img->y + img->move_speed * \
	sin(img->rotation_angle) * img->walk_direction) / \
	TILE_SIZE)][((int)(img->x + img->move_speed * \
	cos(img->rotation_angle) * img->walk_direction) / TILE_SIZE)] != ' ')
	{
		img->x += img->move_speed * \
		cos(img->rotation_angle) * img->walk_direction;
		img->y += img->move_speed * \
		sin(img->rotation_angle) * img->walk_direction;
	}
}

void	go_side(t_data *img)
{
	if (img->tab[((int)(img->y + img->move_speed * \
	sin(img->rotation_angle + M_PI / 2) * img->walk_direction_side) \
	/ TILE_SIZE)][((int)(img->x + img->move_speed * \
	cos(img->rotation_angle + M_PI / 2) * \
	img->walk_direction_side) / TILE_SIZE)] != '1' && \
	img->tab[((int)(img->y + img->move_speed * \
	sin(img->rotation_angle + M_PI / 2) * img->walk_direction_side) \
	/ TILE_SIZE)][((int)(img->x + img->move_speed * \
	cos(img->rotation_angle + M_PI / 2) * \
	img->walk_direction_side) / TILE_SIZE)] != ' ')
	{
		img->x += img->move_speed * cos(img->rotation_angle + M_PI / 2) \
		* img->walk_direction_side;
		img->y += img->move_speed * sin(img->rotation_angle + M_PI / 2) \
		* img->walk_direction_side;
	}
}

void	rotate(t_data *img)
{
	img->rotation_angle += (img->turn_direction * img->rotation_speed);
}
