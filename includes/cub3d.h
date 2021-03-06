/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:53:05 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/12 14:28:29 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define KEYPRESSMASK	1
# define KEYRELEASEMASK 9
# define STRUCTURENOTIFYMASK	131072
# define KEYPRESS	2
# define KEYRELEASE	3
# define DESTROYNOTIFY	17

# include "mlx.h"
# include "get_next_line.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# define ROT .1

typedef	struct		s_player
{
	int				hp;
	int				protected;
	int				shot;
}					t_player;

typedef union		u_color
{
	unsigned int	v;

	struct			s_color
	{
		unsigned int	b : 8;
		unsigned int	g : 8;
		unsigned int	r : 8;
		unsigned int	a : 8;
	}				color;
}					t_color;

typedef struct		s_saver
{
	unsigned char	*buf;
	size_t			index;
	size_t			size;
}					t_saver;

typedef struct		s_img
{
	int				*img_data;
	int				size_line;
	int				bits_per_pixel;
	int				endian;
	int				height;
	int				width;
}					t_img;

typedef	struct		s_sprite_put
{
	int		start_y;
	int		end_y;
	int		start_x;
	int		end_x;
	int		y;
	int		d;
	int		stripe;
}					t_sprite_put;

typedef	struct		s_sprite
{
	double			x;
	double			y;
	struct s_sprite	*next;
}					t_sprite;

typedef	struct		s_key
{
	int				save_bool;
	int				*dda_img_data;
	int				window_width;
	int				window_heigth;
	int				map_width;
	int				map_heigth;
	int				floor_color;
	int				cieling_color;
	char			*north_path;
	char			*south_path;
	char			*east_path;
	char			*west_path;
	char			*sprite_path;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	double			pos_x;
	double			pos_y;
	double			projection_distance;
	double			dir_x;
	double			dir_y;
	double			angle;
	double			plane_x;
	double			plane_y;
	double			camera_x;
	char			*worldmap;
	t_img			texture_no;
	t_img			texture_so;
	t_img			texture_ea;
	t_img			texture_we;
	t_img			texture_sprite;
	t_sprite		*sprite;
	t_sprite		*sprite_save;
	t_img			texture_saber;
	t_img			texture_saber_a;
	t_img			game_over;
	t_img			health_bar;
	int				sprite_num;
	t_player		player;
}					t_key;

typedef struct		s_dda
{
	double			ray_dir_x;
	double			ray_dir_y;
	double			dist_x;
	double			dist_y;
	double			decalage_ray_x;
	double			decalage_ray_y;
	int				step_x;
	int				step_y;
	int				wall;
	char			wall_side;
	long			map_x;
	long			map_y;
	double			wall_distance;
	long			wall_height;
	double			wall_x;
	double			wall_y;
	long			texture_x;
	long			texture_y;
	double			sprite_x;
	double			sprite_y;
	double			invert;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				sprite_height;
	int				sprite_width;
}					t_dda;

int					window_quit(t_key *k);
int					deal_key(int key, t_key *k);
int					release_key(int key, t_key *k);
int					loop_hook(t_key *k);
void				wall_loop(t_key *k, t_dda *dda);
void				dda_init(t_key *k, t_dda *dda, int i);
int					parsing_init(int fd, t_key *param);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				save_img();
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
char				*ft_strdup(const char *s);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(const char *s);
int					ft_isalpha(int c);
t_sprite			*ft_new_sprite(int x, int y);
void				ft_lst_sort(t_sprite *begin_list, t_key *param);
int					save_first_frame(t_key *s, char *filename);
void				resolution(char *line, t_key *param);
void				north_path(char *line, t_key *param);
void				south_path(char *line, t_key *param);
void				west_path(char *line, t_key *param);
void				east_path(char *line, t_key *param);
void				sprite_path(char *line, t_key *param);
void				floor_color(char *line, t_key *param);
void				cieling_color(char *line, t_key *param);
void				map_parsing(char *line, t_key *param, int fd);
int					sprite_parsing(t_key *param);
void				parsing_error(t_key *param);
void				set_position(int i, t_key *param);
int					finding_position(char *str, t_key *param);
void				deal_forward(t_key *k);
void				deal_backward(t_key *k);
void				deal_left(t_key *k);
void				deal_right(t_key *k);
void				loop_call_up(t_key *k, t_img *img_data, int *pixel, int j);
void				loop_call_down(t_key *k, t_img *img_data, int *pixel);
void				wall_calculate(t_key *k, t_dda *dda);
void				img_create(t_key *k, int i, t_img *img_data, t_dda *dda);
void				sprite_loop(t_key *k, t_dda *dda, t_img *img_data,
double *z_buffer);
void				wall_side_ew(t_key *k, t_dda *dda);
void				wall_side_ns(t_key *k, t_dda *dda);
void				add_saber(t_key *k, t_dda *dda, t_img *img_data);
void				add_saber_attack(t_key *k, t_dda *dda, t_img *img_data);
void				add_health_bar(t_key *k, t_dda *dda, t_img *img_data);
int					hook_attack(t_key *k);
void				delete_loop(t_key *k, double i, double j);
void				took_damage(t_key *k);
void				game_over(t_key *k, t_img *img_data);
void				texture_init(t_key *param);
void				value_init(t_key *param);
int					init_error(int ac, char **av);
void				shot_check(t_key *k);
void				map_error(t_key *param);
t_key				*map_border_check(t_key *param);
void				texture_init_north(t_key *param);
void				texture_init_south(t_key *param);
void				texture_init_east(t_key *param);
void				texture_init_west(t_key *param);
void				texture_init_sprite(t_key *param);
void				texture_error(void);

#endif
