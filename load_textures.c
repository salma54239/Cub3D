/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 00:21:39 by ssaadaou          #+#    #+#             */
/*   Updated: 2024/01/30 05:49:46 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_size(t_data *img)
{
	if (!img->no_texture->pic || !img->we_texture->pic || \
	!img->so_texture->pic || !img->ea_texture->pic)
	{
		printf("Error: Texture not found\n");
		return (1);
	}
	if (img->no_texture->width != TILE_SIZE || \
	img->no_texture->height != TILE_SIZE || \
	img->we_texture->width != TILE_SIZE || \
	img->we_texture->height != TILE_SIZE || \
	img->so_texture->width != TILE_SIZE || \
	img->so_texture->height != TILE_SIZE || \
	img->ea_texture->width != TILE_SIZE || img->ea_texture->height != TILE_SIZE)
	{
		printf("Error: Texture size not valid  \n");
		return (1);
	}
	return (0);
}

int	image_texture(t_data *img)
{
	void	**tmp;

	img->we_texture->pic = mlx_xpm_file_to_image(img->mlx, \
	img->path->west_path, &img->we_texture->width, &img->we_texture->height);
	print_list(img->token);
	if (!img->we_texture->pic)
		return (printf("Error: Texture not found we_texture\n"), 1);
	img->no_texture->pic = mlx_xpm_file_to_image(img->mlx, \
	img->path->north_path, &img->no_texture->width, &img->no_texture->height);
	if (!img->no_texture->pic)
		return (printf("Error: Texture not found no_texture 1\n"), 1);
	img->ea_texture->pic = mlx_xpm_file_to_image(img->mlx, \
	img->path->east_path, &img->ea_texture->width, &img->ea_texture->height);
	if (!img->ea_texture->pic)
		return (printf("Error: Texture not found ea_texture\n"), 1);
	img->so_texture->pic = mlx_xpm_file_to_image(img->mlx, \
	img->path->south_path, &img->so_texture->width, &img->so_texture->height);
	if (!img->so_texture->pic)
		return (printf("Error: Texture not found so_texture\n"), 1);
	if (check_size(img))
		return (printf("Error: Texture size not valid  \n"), 1);
	return (0);
}

void	addr_texture(t_data *img)
{
	img->no_texture->addr = mlx_get_data_addr(img->no_texture->pic, \
	&img->no_texture->bits_per_pixel, \
	&img->no_texture->line_len, &img->no_texture->endian);
	img->so_texture->addr = mlx_get_data_addr(img->so_texture->pic, \
	&img->so_texture->bits_per_pixel, &img->so_texture->line_len, \
	&img->so_texture->endian);
	img->we_texture->addr = mlx_get_data_addr(img->we_texture->pic, \
	&img->we_texture->bits_per_pixel, &img->we_texture->line_len, \
	&img->we_texture->endian);
	img->ea_texture->addr = mlx_get_data_addr(img->ea_texture->pic, \
	&img->ea_texture->bits_per_pixel, &img->ea_texture->line_len, \
	&img->ea_texture->endian);
	if (!img->no_texture->addr || !img->we_texture->addr || \
	!img->so_texture->addr || !img->ea_texture->addr)
	{
		printf("Error: Texture not found\n");
		exit(1);
	}
}

int	load_textures(t_data *img)
{
	if (image_texture(img))
		end_game(img);
	addr_texture(img);
	return (0);
}
