/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:08:11 by shadria-          #+#    #+#             */
/*   Updated: 2024/01/29 19:45:54 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	horz_aux(t_ray *ray, double cx, double cy, t_data *img)
{
	ray[img->i].foundhorzhit = false;
	ray[img->i].rayfacedown = ray[img->i].ray_angle > 0 && \
	ray[img->i].ray_angle < M_PI;
	ray[img->i].rayfaceup = !ray[img->i].rayfacedown;
	ray[img->i].rayfaceright = ray[img->i].ray_angle < (M_PI / 2) || \
	ray[img->i].ray_angle > (3 * M_PI / 2);
	ray[img->i].rayfaceleft = !ray[img->i].rayfaceright;
	ray[img->i].y_intercept = floor(cy / TILE_SIZE) * TILE_SIZE;
	if (ray[img->i].rayfacedown)
		ray[img->i].y_intercept += TILE_SIZE;
	ray[img->i].x_intercept = cx + ((ray[img->i].y_intercept - cy) / \
	tan(ray[img->i].ray_angle));
	ray[img->i].y_step = TILE_SIZE;
	if (ray[img->i].rayfaceup)
		ray[img->i].y_step *= -1;
	ray[img->i].x_step = TILE_SIZE / tan(ray[img->i].ray_angle);
	if (ray[img->i].rayfaceleft && ray[img->i].x_step > 0)
		ray[img->i].x_step *= -1;
	else if (ray[img->i].rayfaceright && ray[img->i].x_step < 0)
		ray[img->i].x_step *= -1;
}

void	horiz_intersection(t_ray *ray, t_data *img, double cx, double cy)
{
	horz_aux(ray, cx, cy, img);
	while (ray[img->i].x_intercept >= 0 && \
	ray[img->i].x_intercept <= img->parm->max_len_line * TILE_SIZE && \
	ray[img->i].y_intercept >= 0 && \
	ray[img->i].y_intercept <= img->parm->num_row * TILE_SIZE)
	{
		img->yt = (int)ray[img->i].y_intercept / \
		TILE_SIZE - (int)ray[img->i].rayfaceup;
		img->xt = (int)ray[img->i].x_intercept / TILE_SIZE;
		if (img->yt >= 0 && img->xt >= 0 && img->yt < (img->parm->num_row) && \
		img->xt < (img->parm->max_len_line) && \
		img->tab[((int)ray[img->i].y_intercept / TILE_SIZE) - \
		(int)ray[img->i].rayfaceup][(int)ray[img->i].x_intercept \
		/ TILE_SIZE] == '1')
		{
			ray[img->i].foundhorzhit = true;
			ray[img->i].horz_hit_x = ray[img->i].x_intercept;
			ray[img->i].horz_hit_y = ray[img->i].y_intercept;
			break ;
		}
		ray[img->i].x_intercept += ray[img->i].x_step;
		ray[img->i].y_intercept += ray[img->i].y_step;
	}
}

void	vert_aux(t_ray *ray, double cx, double cy, t_data *img)
{
	ray[img->i].foundvertwallhit = false;
	ray[img->i].x_intercept = floor(cx / TILE_SIZE) * TILE_SIZE;
	if (ray[img->i].rayfaceright)
		ray[img->i].x_intercept += TILE_SIZE;
	ray[img->i].y_intercept = cy + \
	((ray[img->i].x_intercept - cx) * tan(ray[img->i].ray_angle));
	ray[img->i].y_step = TILE_SIZE * tan(ray[img->i].ray_angle);
	if (ray[img->i].rayfaceup && ray[img->i].y_step > 0)
		ray[img->i].y_step *= -1;
	else if (ray[img->i].rayfacedown && ray[img->i].y_step < 0)
		ray[img->i].y_step *= -1;
	ray[img->i].x_step = TILE_SIZE;
	if (ray[img->i].rayfaceleft)
		ray[img->i].x_step *= -1;
}

void	vert_intersection(t_ray *ray, t_data *img, double cx, double cy)
{
	vert_aux(ray, cx, cy, img);
	while (ray[img->i].x_intercept >= 0 && \
	ray[img->i].x_intercept <= img->parm->max_len_line * TILE_SIZE && \
	ray[img->i].y_intercept >= 0 && \
	ray[img->i].y_intercept <= img->parm->num_row * TILE_SIZE)
	{
		if (img->tab[((int)ray[img->i].y_intercept / \
		TILE_SIZE)][(int)ray[img->i].x_intercept / TILE_SIZE - \
		(int)ray[img->i].rayfaceleft] == '1')
		{
			ray[img->i].foundvertwallhit = true;
			ray[img->i].vert_hit_x = ray[img->i].x_intercept;
			ray[img->i].vert_hit_y = ray[img->i].y_intercept;
			break ;
		}
		ray[img->i].x_intercept += ray[img->i].x_step;
		ray[img->i].y_intercept += ray[img->i].y_step;
	}
}

void	horz_vert_hit_distance(t_ray *ray, double cx, double cy, t_data *img)
{
	ray[img->i].horz_distance = MAX;
	ray[img->i].vert_distance = MAX;
	if (ray[img->i].foundhorzhit)
		ray[img->i].horz_distance = sqrt(((ray[img->i].horz_hit_x - cx) * \
		(ray[img->i].horz_hit_x - cx)) + ((ray[img->i].horz_hit_y - cy) \
		* (ray[img->i].horz_hit_y - cy)));
	if (ray[img->i].foundvertwallhit)
		ray[img->i].vert_distance = sqrt(((ray[img->i].vert_hit_x - cx) * \
		(ray[img->i].vert_hit_x - cx)) \
		+ ((ray[img->i].vert_hit_y - cy) * (ray[img->i].vert_hit_y - cy)));
	if (ray[img->i].vert_distance < ray[img->i].horz_distance)
		ray[img->i].washitvertical = true;
	else
		ray[img->i].washitvertical = false;
}
