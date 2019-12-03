/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 09:09:45 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/02 09:13:19 by trbonnes         ###   ########.fr       */
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
# define MAPHEIGHT 14
# define MAPWIDTH 29
# define WINDOWHEIGHT 480
# define WINDOWWIDTH 720
# define ROT .1

typedef	struct		s_key
{
  int     window_width;
  int     window_heigth;
  int     map_width;
  int     map_heigth;
  int     floor_color;
  int     cieling_color;
  char    *north_path;
  char    *south_path;
  char    *east_path;
  char    *west_path;
  char    *sprite_path;
	void	  *mlx_ptr;
	void	  *win_ptr;
	void	  *img_ptr;
	double	pos_x;
	double	pos_y;
	double	projection_distance;
	double	dir_x;
	double	dir_y;
	double	angle;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	char	  *worldmap;
}					t_key;

int		    parsing_init(char *file, t_key *param);
int		    ft_strncmp(const char *s1, const char *s2, size_t n);
void	    save_img();
int		    ft_atoi(const char *str);
int		    ft_isdigit(int c);
char	    *ft_strdup(const char *s);
char	    *ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
int		    ft_isalpha(int c);

#endif