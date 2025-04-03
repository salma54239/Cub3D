/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:51:58 by shadria-          #+#    #+#             */
/*   Updated: 2024/01/29 19:36:06 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	fct_norm_radian(double angle)
{
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	else if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void	store_smallest_distance(t_ray *ray, t_data *img)
{
	if (ray[img->i].vert_distance > ray[img->i].horz_distance)
	{
		ray[img->i].wallhit_x = ray[img->i].horz_hit_x;
		ray[img->i].wallhit_y = ray[img->i].horz_hit_y;
		ray[img->i].true_distance = ray[img->i].horz_distance;
	}
	else
	{
		ray[img->i].wallhit_x = ray[img->i].vert_hit_x;
		ray[img->i].wallhit_y = ray[img->i].vert_hit_y;
		ray[img->i].true_distance = ray[img->i].vert_distance;
	}
}

void	fct_line_rotate(t_data *img, double cx, double cy)
{
	int	c;

	c = 20;
	while (c-- > 0)
		my_mlx_pixel_put(img, (cos(img->rotation_angle) * c + cx), \
		(sin(img->rotation_angle) * c + cy), 0x0022ff);
}

void	player(t_data *img, double cx, double cy)
{
	int		wall_thickness;
	t_ray	*ray;
	int		num_rays;

	wall_thickness = 1;
	num_rays = WIN_WIDTH / wall_thickness;
	ray = define_fov(img, cx, cy);
	renderprojectedwalls(num_rays, ray, img);
}
