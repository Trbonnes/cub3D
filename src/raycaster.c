/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 09:10:03 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/03 12:24:51 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int    window_quit(t_key *k)
{
  mlx_destroy_window(k->mlx_ptr, k->win_ptr);
  write(1, "Exiting\n", 8);
  exit(0);
  return (0);
}

int			deal_key(int key, t_key *k)
{
  if (key == 53)
  {
		mlx_destroy_window(k->mlx_ptr, k->win_ptr);
    write(1, "ESC\nExiting\n", 12);
    exit(0);
  }
  if (key == 13 && k->worldmap[(long)(k->pos_y + k->dir_y) * MAPWIDTH + (long)(k->pos_x + k->dir_x)] != '1')
  {
    k->pos_x += k->dir_x;
    k->pos_y += k->dir_y;
  }
  if (key == 1 && k->worldmap[(long)(k->pos_y - k->dir_y) * MAPWIDTH + (long)(k->pos_x - k->dir_x)] != '1')
  {
    k->pos_x -= k->dir_x;
    k->pos_y -= k->dir_y;
  }
  if (key == 0 && k->worldmap[(long)(k->pos_y - k->dir_x) * MAPWIDTH + (long)(k->pos_x - -1 * k->dir_y)] != '1')
  {
    k->pos_x -= -1 * k->dir_y;
    k->pos_y -= k->dir_x;
  }
  if (key == 2 && k->worldmap[(long)(k->pos_y + k->dir_x) * MAPWIDTH + (long)(k->pos_x + -1 * k->dir_y)] != '1')
  {
    k->pos_x += -1 * k->dir_y;
    k->pos_y += k->dir_x;
  }
  if (key == 124)
    k->angle += ROT;
  if (key == 123)
    k->angle -= ROT;
  k->dir_x = cos(k->angle);
  k->dir_y = sin(k->angle);
  k->plane_x = -1 * k->dir_y;
  k->plane_y = k->dir_x;
  printf("dir x: %lf\n", k->dir_x);
  printf("dir y: %lf\n", k->dir_y);
  printf("plane x: %lf\n", k->plane_x);
  printf("plane y: %lf\n", k->plane_y);
  printf("angle: %lf\n", k->angle);
  return (0);
}

int loop_hook(t_key *k)
{
  double    ray_dir_x;
  double    ray_dir_y;
  double    dist_x;
  double    dist_y;
  double    decalage_ray_x;
  double    decalage_ray_y;
  int       step_x;
  int       step_y;
  int       wall;
  int       wall_side;
  long      map_x;
  long      map_y;
  double    wall_distance;
  long      wall_height;
  int       i;
  int       pixel_number;
  int       wall_color;
  int       j;
  int       *img_data_addr;
  int       bits_per_pixel;
  int       size_line;
  int       endian;
  int       pixel_index;
  
  i = 0;
  if (k->img_ptr)
    mlx_destroy_image(k->mlx_ptr, k->img_ptr);
  k->img_ptr = mlx_new_image(k->mlx_ptr, WINDOWWIDTH, WINDOWHEIGHT);
  img_data_addr = (int *)mlx_get_data_addr(k->img_ptr, &bits_per_pixel, &size_line, &endian);
  while(i <= WINDOWWIDTH)
  {
    k->camera_x = 2 * i / (double)WINDOWWIDTH - 1;
    ray_dir_x = k->dir_x + k->plane_x * k->camera_x;
    ray_dir_y = k->dir_y + k->plane_y * k->camera_x;
    map_x = (long) k->pos_x;
    map_y= (long) k->pos_y;
    decalage_ray_x = fabs(1 / ray_dir_x);
    decalage_ray_y = fabs(1 / ray_dir_y);
    wall = 0;
    if (ray_dir_x < 0)
    {
      step_x = -1;
      dist_x = (k->pos_x - map_x) * decalage_ray_x;
    }
    else
    {
      step_x = 1;
      dist_x = (map_x + 1.0 - k->pos_x) * decalage_ray_x;
    }
    if (ray_dir_y < 0)
    {
      step_y = -1;
      dist_y = (k->pos_y - map_y) * decalage_ray_y;
    }
    else
    {
      step_y = 1;
      dist_y = (map_y + 1.0 - k->pos_y) * decalage_ray_y;
    }
    while (wall != 1)
    {
      if (dist_x < dist_y)
      {
        dist_x += decalage_ray_x;
        map_x += step_x;
        wall_side = 0;
      }
      else
      {
        dist_y += decalage_ray_y;
        map_y += step_y;
        wall_side = 1;
      }
      if (k->worldmap[map_y * MAPWIDTH + map_x] == '1')
        wall = 1;
    }
    if (wall_side == 0) 
      wall_distance = (map_x - k->pos_x + (1 - step_x) / 2) / ray_dir_x;
    else           
      wall_distance = (map_y - k->pos_y + (1 - step_y) / 2) / ray_dir_y;
    wall_height = WINDOWHEIGHT / wall_distance;
    if (wall_side == 0)
      wall_color = 0x00000000;
    else
      wall_color = 0x000000ff;
    j = (int)((WINDOWHEIGHT - wall_height) / 2);
    pixel_number = 0;
    pixel_index = i;
    while (pixel_number < j)
    {
      img_data_addr[pixel_index] = k->cieling_color;
      pixel_number++;
      pixel_index += WINDOWWIDTH;
    }
    while (pixel_number <= (j + (int)wall_height))
    {
      img_data_addr[pixel_index] = wall_color;
      pixel_number++;
      pixel_index += WINDOWWIDTH;
    }
    while (pixel_number <= (int)WINDOWHEIGHT)
    {
      img_data_addr[pixel_index] = k->floor_color;
      pixel_number++;
      if (pixel_number < (int)WINDOWHEIGHT - 1)
        pixel_index += WINDOWWIDTH;
    }
    i++;
  }
  mlx_put_image_to_window(k->mlx_ptr, k->win_ptr, k->img_ptr, 0, 0);
  return (0);
}

int main(int ac, char **av)
{
	t_key	    param;

  if (ac == 2 || (ac == 3 && !ft_strncmp(av[2], "-save", 5)))
  {
    param = (t_key) { 0 };
    param.angle = -(M_PI / 2);
    parsing_init(av[1], &param);
    param.projection_distance = 0.866;
    param.plane_x = -1 * param.dir_y;
    param.plane_y = param.dir_x;
    param.mlx_ptr = mlx_init();
    if (ac < 3)
      param.win_ptr = mlx_new_window(param.mlx_ptr, WINDOWWIDTH, WINDOWHEIGHT, "cub3D");
    else
      save_img();
    mlx_loop_hook(param.mlx_ptr, &loop_hook, &param);
    mlx_hook(param.win_ptr, KeyPress, KeyPressMask, deal_key, &param);
    mlx_hook(param.win_ptr, DestroyNotify, StructureNotifyMask, window_quit, &param);
    mlx_loop(param.mlx_ptr);
  }
  else
    write(2, "Parameters Error\nExiting\n", 25);
  exit (0);
	return(0);
}
