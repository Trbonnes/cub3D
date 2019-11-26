#include "mlx.h"
#include "X.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define mapHeight 5
#define mapWidth 5
#define windowHeight 720
#define windowWidth 1080

static char map[] = {
  1, 1, 1, 1, 1,
  1, 0, 0, 0, 1,
  1, 0, 0, 0, 1,
  1, 0, 0, 0, 1,
  1, 1, 1, 1, 1
};

typedef	struct		s_key
{
	void    *mlx_ptr;
	void    *win_ptr;
  double  Pos_X;
  double  Pos_Y;
  double  Projection_distance;
  char     *worldMap;
}					t_key;

int			deal_key(int key, t_key *k)
{
  if (key == 126)
    k->Pos_Y = k->Pos_Y + 1;
  if (key == 125)
    k->Pos_Y = k->Pos_Y - 1;
  return (0);
}

int loop_hook(t_key *k)
{
  double    Dir_X;
  double    Dir_Y;
  double    Plane_X;
  double    Plane_Y;
  double    Ray_X;
  double    Ray_Y;
  double    intersection_X;
  double    intersection_Y;
  long      Wall_X;
  long      Wall_Y;
  int       Wall;
  int       i;
  double    WallHeight;
  int       j;
  int       pixel_number;

  Dir_X = ((k->Pos_X + 0) - k->Pos_X);
  Dir_Y = ((k->Pos_Y - k->Projection_distance) - k->Pos_Y);
  Plane_X = (k->Pos_X + Dir_X + 0.5) - (k->Pos_X + Dir_X);
  Plane_Y = (k->Pos_Y + Dir_Y + 0) - (k->Pos_Y + Dir_Y);
  i = 0;
  while(i < windowWidth)
  {
    Wall = 0;
    Ray_X = (Dir_X + ((-1 * Plane_X) + (double)(i / windowWidth)));
    if (((-1 * Plane_X) + (double)(i / windowWidth) < 0))
      Ray_Y = (Dir_Y - Plane_Y);
    else
      Ray_Y = (Dir_Y + Plane_Y);
    intersection_Y = k->Pos_Y - (k->Pos_Y - (long)k->Pos_Y);
    intersection_X = (Ray_X * intersection_Y - 3.541) / Ray_Y;
    while (Wall != 1)
    {
      Wall_X = (long)intersection_X;
      Wall_Y = (long)intersection_Y;
      if (k->worldMap[Wall_Y * mapWidth + Wall_X] == 1)
        Wall = 1;
      else
      {
        intersection_Y += 1.;
        intersection_X = (Ray_X * intersection_Y - 3.541) / Ray_Y;
      }
    }
    WallHeight = (1 / sqrt(pow(Wall_X - k->Pos_X, 2) + pow(Wall_Y - k->Pos_Y, 2))) * k->Projection_distance;
    WallHeight = windowHeight * WallHeight;
    printf("%f\n", WallHeight);
    j = (int)((windowHeight - WallHeight) / 2);
    pixel_number = 0;
    printf("%d\n", j);
    while (pixel_number < j)
    {
      //printf("i: %d j: %d\n", i, j);
      mlx_pixel_put(k->mlx_ptr, k->win_ptr, i, pixel_number, 0xff0000);
      pixel_number++;
    }
    while (pixel_number <= (j + (int)WallHeight))
    {
      mlx_pixel_put(k->mlx_ptr, k->win_ptr, i, pixel_number, 0x0000ff);
      pixel_number++;
    }
    while (pixel_number <= (int)windowHeight)
    {
      mlx_pixel_put(k->mlx_ptr, k->win_ptr, i, pixel_number, 0x00ff00);
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
  param.worldMap = map;
  param.Projection_distance = 0.866;
  param.Pos_X = 2.5;
  param.Pos_Y = 3.5;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, windowWidth, windowHeight, "cub3D");
	param.mlx_ptr = mlx_ptr;
	param.win_ptr = win_ptr;
  mlx_loop_hook(mlx_ptr, &loop_hook, &param);
  mlx_hook(win_ptr, KeyPress, KeyPressMask, deal_key, &param);
  mlx_loop(mlx_ptr);
	return(0);
}
