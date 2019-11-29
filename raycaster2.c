#include "mlx.h"
#include "X.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAPHEIGHT 14
#define MAPWIDTH 29
#define WINDOWHEIGHT 480
#define WINDOWWIDTH 720
#define ROT 0.1

static char map[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
  1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
  1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1,
  1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
  1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1,
  1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
  1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1,
  1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1,
  1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

typedef	struct		s_key
{
	void    *mlx_ptr;
	void    *win_ptr;
  void    *img_ptr;
  double  pos_x;
  double  pos_y;
  double  projection_distance;
  double  dir_x;
  double  dir_y;
  double  angle;
  double  plane_x;
  double  plane_y;
  double  camera_x;
  char     *worldmap;
}					t_key;

int			deal_key(int key, t_key *k)
{
  if (key == 53)
  {
		mlx_destroy_window(k->mlx_ptr, k->win_ptr);
    exit(0);
  }
  if (key == 13 && k->pos_y > 0)
    k->pos_y = k->pos_y - 0.5;
  if (key == 1 && k->pos_y < MAPHEIGHT)
    k->pos_y = k->pos_y + 0.5;
  if (key == 0 && k->pos_x > 0)
    k->pos_x = k->pos_x - 0.5;
  if (key == 2 && k->pos_x < MAPWIDTH)
    k->pos_x = k->pos_x + 0.5;
  if (key == 124)
  {
    //pivot gauche
    k->angle += ROT;
  }
  if (key == 123)
  {
    //pivot drt
    k->angle -= ROT;
  }
  k->dir_x = cos(k->angle);
  k->dir_y = sin(k->angle);
  k->plane_x = -1 * k->dir_y;
  k->plane_y = k->dir_x;
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
  double    time;
  double    old_time;
  int       i;
  int       pixel_number;
  int       wall_color;
  int       j;

  int       *img_data_addr;
  int       bits_per_pixel;
  int       size_line;
  int       endian;
  int       pixel_index;

  time = 0;
  old_time = 0;
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
      if (k->worldmap[map_y * MAPWIDTH + map_x] == 1)
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
      wall_color = 0x00ff0000;
    j = (int)((WINDOWHEIGHT - wall_height) / 2);
    pixel_number = 0;
    pixel_index = i;
    while (pixel_number < j)
    {
      img_data_addr[pixel_index] = 0x000000ff;
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
      img_data_addr[pixel_index] = 0x00ffffff;
      pixel_number++;
      if (pixel_number < (int)WINDOWHEIGHT - 1)
        pixel_index += WINDOWWIDTH;
    }
    i++;
  }
  mlx_put_image_to_window(k->mlx_ptr, k->win_ptr, k->img_ptr, 0, 0);
  return (0);
}

int main()
{
	void 	    *mlx_ptr;
	void 	    *win_ptr;
	t_key	    param;

	param = (t_key) { 0 };
  param.worldmap = map;
  param.projection_distance = 0.866;
  param.pos_x = 26.5;
  param.pos_y = 11.5;
  param.angle = -(M_PI / 2);
  param.dir_x = cos(param.angle);
  param.dir_y = sin(param.angle);
  param.plane_x = -1 * param.dir_y;
  param.plane_y = param.dir_x;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WINDOWWIDTH, WINDOWHEIGHT, "cub3D");
	param.mlx_ptr = mlx_ptr;
	param.win_ptr = win_ptr;
  mlx_loop_hook(mlx_ptr, &loop_hook, &param);
  mlx_hook(win_ptr, KeyPress, KeyPressMask, deal_key, &param);
  mlx_loop(mlx_ptr);
	return(0);
}
