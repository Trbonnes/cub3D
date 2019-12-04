/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:53:05 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/04 17:12:38 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "X.h"
# include "get_next_line.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# define ROT .1

typedef struct		s_img
{
	int				wall_color;
	int				*img_data;
	int				size_line;
	int				bits_per_pixel;
	int				endian;
	int				height;
	int				width;
}					t_img;

typedef	struct		s_key
{
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
}					t_dda;

int					window_quit(t_key *k);
int					deal_key(int key, t_key *k);
int					loop_hook(t_key *k);
int					parsing_init(int fd, t_key *param);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				save_img();
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
char				*ft_strdup(const char *s);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(const char *s);
int					ft_isalpha(int c);

#endif
