/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 13:13:49 by ssaadaou          #+#    #+#             */
/*   Updated: 2024/01/30 05:51:28 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel_color(t_texture *texture, int x, int y)
{
	char			*rev;
	unsigned int	color;

	rev = texture->addr + (y * texture->line_len) + (x * 4);
	color = *(unsigned int *) rev;
	return (color);
}

void	draw_ceiling_floor(t_data *img, int i, int y, double top_pixel)
{
	if (y > top_pixel)
		my_mlx_pixel_put(img, i, y, img->path->fl_floor);
	else
		my_mlx_pixel_put(img, i, y, img->path->fl_ceil);
}

void	draw_textured_wall(int i, t_data *img, t_texture *texture, t_ray ray)
{
	t_vars	vars;

	vars.y = -1;
	vars.top_pixel = (WIN_HEIGHT / 2) - (img->wallstripheight / 2);
	vars.bottom_pixel = (WIN_HEIGHT / 2) + (img->wallstripheight / 2);
	while (++vars.y <= WIN_HEIGHT)
	{
		if (vars.y < vars.top_pixel || vars.y >= vars.bottom_pixel)
			draw_ceiling_floor(img, i, vars.y, vars.top_pixel);
		else if (vars.y < vars.bottom_pixel && vars.y >= vars.top_pixel)
		{
			if (ray.washitvertical == true)
				texture->offset_x = fmod((int)ray.vert_hit_y, TILE_SIZE);
			else
				texture->offset_x = fmod((int)ray.horz_hit_x, TILE_SIZE);
			texture->offset_y = ((vars.y - ((WIN_HEIGHT / 2) - \
			(img->wallstripheight / 2))) * \
			((double)(double)TILE_SIZE / (double)img->wallstripheight));
			vars.color = get_pixel_color(texture, texture->offset_x, \
			texture->offset_y);
			my_mlx_pixel_put(img, i, vars.y, vars.color);
		}
	}
}
