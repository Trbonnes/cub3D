#include "mlx.h"
#include "X.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAPHEIGHT 6
#define MAPWIDTH 7
#define WINDOWHEIGHT 384
#define WINDOWWIDTH 512

static char map[] = {
  1, 1, 1, 1, 1, 1, 1,
  1, 0, 0, 0, 0, 0, 1,
  1, 1, 1, 0, 1, 1, 1,
  1, 0, 0, 0, 0, 0, 1,
  1, 0, 1, 0, 1, 0, 1,
  1, 1, 1, 1, 1, 1, 1
};

typedef	struct		s_key
{
	void    *mlx_ptr;
	void    *win_ptr;
  double  pos_x;
  double  pos_y;
  double  projection_distance;
  char     *worldmap;
}					t_key;

int			deal_key(int key, t_key *k)
{
  long  Colision_Check_X;
  long  Colision_Check_Y;

  Colision_Check_X = (long)k->pos_x;
  Colision_Check_Y = (long)k->pos_y;
  if (key == 53)
		mlx_destroy_window(k->mlx_ptr, k->win_ptr);
  if (key == 126 && k->pos_y > 0)
    k->pos_y = k->pos_y - 1;
  if (key == 125 && k->pos_y < MAPHEIGHT)
    k->pos_y = k->pos_y + 1;
  if (key == 123 && k->pos_x > 0)
    k->pos_x = k->pos_x + 1;
  if (key == 124 && k->pos_x < MAPWIDTH)
    k->pos_x = k->pos_x - 1;
  return (0);
}

int loop_hook(t_key *k)
{
  double    dir_x;
  double    dir_y;
  double    plane_x;
  double    plane_y;
  double    camera_x;
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

  dir_x = 0;
  dir_y = (k->pos_x - k->projection_distance) - k->pos_x;
  plane_x = 0.60;
  plane_y = 0;
  time = 0;
  old_time = 0;
  i = 0;
  while(i <= WINDOWWIDTH)
  {
    camera_x = 2 * i / (double)WINDOWWIDTH - 1;
    ray_dir_x = dir_x + plane_x * camera_x;
    ray_dir_y = dir_y + plane_y * camera_x;
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
      wall_color = 0x000000;
    else
      wall_color = 0xff0000;
    j = (int)((WINDOWHEIGHT - wall_height) / 2);
    pixel_number = 0;
    while (pixel_number < j)
    {
      mlx_pixel_put(k->mlx_ptr, k->win_ptr, WINDOWWIDTH - i, pixel_number, 0x0000ff);
      pixel_number++;
    }
    while (pixel_number <= (j + (int)wall_height))
    {
      mlx_pixel_put(k->mlx_ptr, k->win_ptr, WINDOWWIDTH - i, pixel_number, wall_color);
      pixel_number++;
    }
    while (pixel_number <= (int)WINDOWHEIGHT)
    {
      mlx_pixel_put(k->mlx_ptr, k->win_ptr, WINDOWWIDTH - i, pixel_number, 0xffffff);
      pixel_number++;
    }
    i++;
  }
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
  param.pos_x = 3.5;
  param.pos_y = 3.5;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WINDOWWIDTH, WINDOWHEIGHT, "cub3D");
	param.mlx_ptr = mlx_ptr;
	param.win_ptr = win_ptr;
  mlx_loop_hook(mlx_ptr, &loop_hook, &param);
  mlx_hook(win_ptr, KeyPress, KeyPressMask, deal_key, &param);
  mlx_loop(mlx_ptr);
	return(0);
}
