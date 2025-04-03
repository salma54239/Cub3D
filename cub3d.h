/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 04:09:59 by ssaadaou          #+#    #+#             */
/*   Updated: 2024/01/30 05:51:12 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define MAX 9999999
# define TILE_SIZE 64
# define MINI_MAP_SCALE_FACTOR 0.2
# define WIN_WIDTH 1260
# define WIN_HEIGHT 860
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <string.h>

typedef struct t_parameters
{
	int		num_row;
	int		max_len_line;
	char	player;
	int		player_x;
	int		player_y;
}	t_parameters;

typedef struct s_texture
{
	void	*pic;
	char	*addr;
	int		bits_per_pixel;
	int		endian;
	int		width;
	int		height;
	int		line_len;
	double	offset_x;
	double	offset_y;
}				t_texture;

typedef struct s_elements
{
	int					flag_c;
	int					flag_f;
	int					flag_texture;
	int					fl_floor;
	int					fl_ceil;
	char				*key;
	char				*north_path;
	char				*south_path;
	char				*east_path;
	char				*west_path;
	t_parameters		*parm;
}	t_elements;

typedef struct s_vars
{
	int				top_pixel;
	int				bottom_pixel;
	unsigned int	color;
	int				y;
	int				i;
	int				j;
	char			c;
}	t_vars;

typedef struct s_ray
{
	double		ray_angle;
	double		horz_hit_x;
	double		horz_hit_y;
	double		vert_hit_x;
	double		vert_hit_y;
	double		horz_distance;
	double		vert_distance;
	double		true_distance;
	double		wallhit_x;
	double		wallhit_y;
	bool		washitvertical;
	bool		foundhorzhit;
	bool		rayfacedown;
	bool		rayfaceup;
	bool		rayfaceright;
	bool		rayfaceleft;
	double		y_intercept;
	double		x_intercept;
	double		y_step;
	double		x_step;
	bool		foundvertwallhit;
	int			index_plan;
}	t_ray;

typedef struct s_list
{
	char			*data;
	struct s_list	*next;
}	t_list;

typedef struct s_data
{
	void			*img;//
	void			*kk;
	int				i;
	char			*addr;
	int				bits_per_pixel;//
	int				line_length;//
	int				endian;//
	void			*mlx;
	void			*mlx_win;
	double			x;//
	double			y;//
	double			rotation_angle;//
	double			rotation_speed;
	double			move_speed;
	int				radius;
	char			**tab;
	char			*str;
	int				wall_thickness;
	int				num_rays;
	double			rayangle;
	double			fov_angle;
	double			wallstripheight;
	int				walk_direction;
	int				walk_direction_side;
	int				turn_direction;
	double			xt;
	double			yt;
	t_texture		txt[4];
	t_texture		*no_texture;
	t_texture		*so_texture;
	t_texture		*we_texture;
	t_texture		*ea_texture;
	t_elements		*path;
	t_parameters	*parm;
	t_ray			*ray;
	t_list			*token;
}				t_data;

typedef struct s_dda
{
	double	x;
	double	y;
	double	xinc;
	double	yinc;
	double	steps;
}				t_dda;

/////////////
int		skip_space(char *str);
void	rotate(t_data *img);
void	go_side(t_data *img);
void	go_straight(t_data *img);
int		key_release(int key, t_data *img);
int		key_press(int key, t_data *img);
int		get_dimension(t_list *token, t_parameters *parm);
char	**fill_map(t_parameters parm, t_list *token);
int		check_duplicate(char **map, t_parameters *parm);
int		is_map_elements(char *map);
int		validate_map(char **map, t_parameters parm);
int		start_position_or_zero(char c);
char	is_color_sign(char *line);
int		text_color_sign(char *line, t_elements *ptr);
int		parse_texture(char *line, t_elements *ptr);
// int		parse_colors(char *line, t_elements *ptr, char );
char	*ft_substr(char *str, int start, int len);
void	print_list(t_list *head);
char	**parse_rest(t_list **token, t_elements *ptr);
////////////

void	draw_textured_wall(int i, t_data *img, t_texture *texture, t_ray ray);
double	calcul_text_offset_x(t_ray ray, t_texture *text, int i);
void	draw_ceiling_floor(t_data *ptr, int i, int y, double top_pixel);
int		get_pixel_color(t_texture *texture, int x, int y);
int		ft_atoi(char *s);
void	free_split(char **split);
int		rgb_to_int(int r, int g, int b);
int		count_commas(const char *str);
int		is_digit_string( char *str);
int		parse_color(char *line, t_elements *ptr, char type);
int		error_msg(int error);

/////
int		ft_isdigit(char c);
int		_error(int ac, char **av);
void	ft_putstr_fd(char *s, int fd);
int		ft_strlen(char *s);
t_list	*new_node(char *str);
t_list	*last_n(t_list	*stack);
void	add_node_end(t_list **head, t_list *newnode);
void	free_stack(t_list *stack);
int		fill_list(int fd, t_list **token);
int		is_wspace(char c);
int		is_space_str(char *str);
int		check_map_elements(t_list *token, t_parameters *parm);
int		parse_text_colors(t_list **token, t_elements *ptr);
void	init_args(t_elements *ptr);
int		load_textures(t_data *img);
void	addr_texture(t_data *img);
int		image_texture(t_data *img);
void	delete_nline(char *line);
int		skip_ws(char *str);

char	**ft_split(char const	*s, char c);
void	update(t_data *img);
int		destroy(t_data *img);
void	fct_line_rotate(t_data *img, double cx, double cy);
int		keyss(int key, t_data *img);
void	key13(t_data *img);
void	key1(t_data *img);
void	key0(t_data *img);
void	key2(t_data *img);
int		keys(int key, t_data *img);
void	player(t_data *img, double cx, double cy);
int		my_map(t_data *img);
double	fct_norm_radian(double angle);
t_ray	*define_fov(t_data *img, double cx, double cy);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
double	fct_norm_radian(double angle);
void	map_visualizer(t_data *img);
void	store_smallest_distance(t_ray *ray, t_data *img);
void	horz_vert_hit_distance(t_ray *ray, double cx, double cy, t_data *img);
void	vert_intersection(t_ray *ray, t_data *img, double cx, double cy);
void	horiz_intersection(t_ray *ray, t_data *img, double cx, double cy);
void	renderprojectedwalls(int num_rays, t_ray *rayy, t_data *img);
void	end_game(t_data *img);
void	dana_firit(t_data *img);
void	initialize_player(t_data *img, char c, int x, int y);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		my_map(t_data *img);
int		take_player_postion(t_data *img);
int		get_dimension(t_list *token, t_parameters *parm);
#endif