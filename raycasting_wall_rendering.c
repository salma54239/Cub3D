/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_wall_rendering.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:49:20 by shadria-          #+#    #+#             */
/*   Updated: 2024/01/30 05:51:34 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fct_txt(t_ray ray, t_data *img, int *i)
{
	if (ray.washitvertical == true && ray.rayfaceright == true)
		draw_textured_wall((*i), img, img->ea_texture, ray);
	else if (ray.washitvertical == true && ray.rayfaceleft == true)
		draw_textured_wall((*i), img, img->we_texture, ray);
	else if (ray.washitvertical == false && ray.rayfaceup == true)
		draw_textured_wall((*i), img, img->no_texture, ray);
	else if (ray.washitvertical == false && ray.rayfacedown == true)
		draw_textured_wall((*i), img, \
		img->so_texture, ray);
}

void	renderprojectedwalls(int num_rays, t_ray *rayy, t_data *img)
{
	int		i;
	t_ray	ray;
	double	fov_angle;
	double	ray_distance;
	double	distance_proj_plan;

	i = -1;
	fov_angle = 60 * (M_PI / 180);
	while (++i < num_rays)
	{
		ray = rayy[i];
		ray_distance = ray.true_distance * \
		cos(ray.ray_angle - img->rotation_angle);
		distance_proj_plan = (WIN_WIDTH / 2) / tan(fov_angle / 2);
		img->wallstripheight = (TILE_SIZE / ray_distance) * distance_proj_plan;
		fct_txt(ray, img, &i);
	}
	free(rayy);
}

t_ray	*define_fov(t_data *img, double cx, double cy)
{
	t_ray	*ray;

	img->i = -1;
	img->wall_thickness = 1;
	img->fov_angle = 60 * (M_PI / 180);
	img->num_rays = WIN_WIDTH / img->wall_thickness;
	img->rayangle = img->rotation_angle - (img->fov_angle / 2);
	ray = malloc(img->num_rays * sizeof(t_ray) + 1);
	if (!ray)
		return (NULL);
	while (++img->i < img->num_rays)
	{
		img->rayangle = fct_norm_radian(img->rayangle);
		ray[img->i].index_plan = img->i;
		ray[img->i].ray_angle = img->rayangle;
		horiz_intersection(ray, img, cx, cy);
		vert_intersection(ray, img, cx, cy);
		horz_vert_hit_distance(ray, cx, cy, img);
		store_smallest_distance(ray, img);
		img->rayangle += (img->fov_angle / img->num_rays);
	}
	return (ray);
}
