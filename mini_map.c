/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:17:00 by shadria-          #+#    #+#             */
/*   Updated: 2024/01/30 05:50:05 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	data_init(t_data *img, t_parameters *parm, t_elements *ptr)
{
	dana_firit(img);
	img->path = ptr;
	img->parm = parm;
	img->path->parm = parm;
	img->parm->max_len_line = 0;
	img->no_texture = &img->txt[0];
	img->so_texture = &img->txt[1];
	img->we_texture = &img->txt[2];
	img->ea_texture = &img->txt[3];
	img->path->north_path = NULL;
	img->path->west_path = NULL;
	img->path->east_path = NULL;
	img->path->south_path = NULL;
	img->ea_texture->pic = NULL;
	img->so_texture->pic = NULL;
	img->we_texture->pic = NULL;
	img->no_texture->pic = NULL;
	img->token = NULL;
}

void	end_game(t_data *img)
{
	free_split(img->tab);
	mlx_destroy_window(img->mlx, img->mlx_win);
	exit(1);
}

void	mlxa_fct(t_data *img)
{
	take_player_postion(img);
	if (!mlx_hook(img->mlx_win, 2, 0, key_press, img))
		end_game(img);
	if (!mlx_hook(img->mlx_win, 3, 0, key_release, img))
		end_game(img);
	if (!mlx_hook(img->mlx_win, 17, 0, destroy, img))
		end_game(img);
	if (mlx_loop_hook(img->mlx, my_map, img))
		end_game(img);
	mlx_loop(img->mlx);
}

void	hook_player_and_texture(t_data *img)
{
	img->mlx = mlx_init();
	img->mlx_win = mlx_new_window(img->mlx, WIN_WIDTH, \
	WIN_HEIGHT, "Hello world!");
	if (!img->mlx)
	{
		free_stack(img->token);
		end_game(img);
	}
	if (load_textures(img))
	{
		free_stack(img->token);
		end_game(img);
	}
	free_stack(img->token);
	if (!img->mlx_win)
		exit(1);
	mlxa_fct(img);
}

int	main(int ac, char **av)
{
	t_data			img;
	t_elements		ptr;
	t_parameters	parm;
	t_list			*tmp;

	tmp = NULL;
	data_init(&img, &parm, &ptr);
	img.no_texture->height = 0;
	if (fill_list(_error(ac, av), &(img.token)))
		return (1);
	tmp = img.token;
	img.tab = parse_rest(&tmp, &ptr);
	if (!img.tab)
		return (free_stack(img.token), 1);
	hook_player_and_texture(&img);
	return (0);
}
