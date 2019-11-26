#include "mlx.h"
#include "X.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define mapHeight 5
#define mapWidth 5
#define windowHeight 480
#define windowWidth 720

static char map[] = {
  0, 0, 1, 0, 0,
  1, 1, 0, 1, 1,
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
  long  Colision_Check_X;
  long  Colision_Check_Y;

  Colision_Check_X = (long)k->Pos_X;
  Colision_Check_Y = (long)k->Pos_Y;
  if (key == 53)
		mlx_destroy_window(k->mlx_ptr, k->win_ptr);
  if (key == 126 && k->worldMap[(Colision_Check_Y - 1) * mapWidth + Colision_Check_X] != 1)
    k->Pos_Y = k->Pos_Y - 1;
  if (key == 125 && k->worldMap[(Colision_Check_Y + 1) * mapWidth + Colision_Check_X] != 1)
    k->Pos_Y = k->Pos_Y + 1;
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
  long      Horizontal_Wall_X;
  long      Horizontal_Wall_Y;
  long      Vertical_Wall_X;
  long      Vertical_Wall_Y;
  int       Wall;
  int       i;
  double    decal_ray;
  double    WallHeight_Horizontal;
  double    WallHeight_Vertical;
  double    WallHeight;
  int       j;
  int       pixel_number;

  Dir_X = 0/*((k->Pos_X + 0) - k->Pos_X)*/;
  Dir_Y = ((k->Pos_Y - k->Projection_distance) - k->Pos_Y);
  Plane_X = 0.5/*(k->Pos_X + Dir_X + 0.5) - (k->Pos_X + Dir_X)*/;
  Plane_Y = 0/*(k->Pos_Y + Dir_Y + 0) - (k->Pos_Y + Dir_Y)*/;
  //printf("Plane : %f\n", Plane_X);
  i = 0;
  while(i <= windowWidth)
  {
    Wall = 0;
    decal_ray = (double)((double)i / (double)windowWidth);
    Ray_X = (k->Pos_X + Dir_X + (Plane_X - decal_ray));
    //printf("decal_ray : %f\n", decal_ray);
    if (decal_ray >= 0.5)
      Ray_Y = (k->Pos_Y + Dir_Y + Plane_Y);
    else
      Ray_Y = (k->Pos_Y + Dir_Y - Plane_Y);
    //printf("Ray_X: %f\n", Ray_X);
    //printf("Ray_Y: %f\n", Ray_Y);
    intersection_Y = k->Pos_Y - (k->Pos_Y - (long)k->Pos_Y);
    intersection_X = (Ray_X * intersection_Y - 3.541) / Ray_Y;
    while (Wall != 1)
    {
      Horizontal_Wall_X = (long)intersection_X;
      Horizontal_Wall_Y = (long)intersection_Y;
      if (k->worldMap[(Horizontal_Wall_Y - 1) * mapWidth + Horizontal_Wall_X] == 1)
        Wall = 1;
      else
      {
        intersection_Y += 0.1;
        intersection_X = (Ray_X * intersection_Y - 3.541) / Ray_Y;
      }
    } 
    WallHeight_Horizontal = (1 / sqrt(pow(Horizontal_Wall_X - k->Pos_X, 2) + pow(Horizontal_Wall_Y - k->Pos_Y, 2))) * k->Projection_distance;
    WallHeight_Horizontal = windowHeight * WallHeight_Horizontal;
    Wall = 0;
    intersection_X = k->Pos_X - (k->Pos_X - (long)k->Pos_X);
    intersection_Y = (Ray_Y * intersection_X + 3.541) / Ray_X;
    while (Wall != 1)
    {
      Vertical_Wall_X = (long)intersection_X;
      Vertical_Wall_Y = (long)intersection_Y;
      if (k->worldMap[Vertical_Wall_Y * mapWidth + Vertical_Wall_X - 1] == 1)
        Wall = 1;
      else
      {
        intersection_X += 0.1;
        intersection_Y = (Ray_Y * intersection_X + 3.541) / Ray_X;
      }
    }
    WallHeight_Vertical = (1 / sqrt(pow(Vertical_Wall_X - k->Pos_X, 2) + pow(Vertical_Wall_Y - k->Pos_Y, 2))) * k->Projection_distance;
    WallHeight_Vertical = windowHeight * WallHeight_Vertical;
    //printf("Horizontal Heiht: %f\n", WallHeight_Horizontal);
    //printf("Vertical Height: %f", WallHeight_Vertical);
    if (WallHeight_Horizontal > WallHeight_Vertical)
    {
      //printf("Horizontal\n");
      WallHeight = WallHeight_Horizontal;
    }
    else
      WallHeight = WallHeight_Vertical;
    //printf("%f\n", WallHeight);
    j = (int)((windowHeight - WallHeight) / 2);
    pixel_number = 0;
    //printf("%d\n", j);
    while (pixel_number < j)
    {
      mlx_pixel_put(k->mlx_ptr, k->win_ptr, windowWidth - i, pixel_number, 0x0000ff);
      pixel_number++;
    }
    while (pixel_number <= (j + (int)WallHeight))
    {
      mlx_pixel_put(k->mlx_ptr, k->win_ptr, windowWidth - i, pixel_number, 0x000000);
      pixel_number++;
    }
    while (pixel_number <= (int)windowHeight)
    {
      mlx_pixel_put(k->mlx_ptr, k->win_ptr, windowWidth - i, pixel_number, 0xffffff);
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
  param.Pos_Y = 2.5;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, windowWidth, windowHeight, "cub3D");
	param.mlx_ptr = mlx_ptr;
	param.win_ptr = win_ptr;
  mlx_loop_hook(mlx_ptr, &loop_hook, &param);
  mlx_hook(win_ptr, KeyPress, KeyPressMask, deal_key, &param);
  mlx_loop(mlx_ptr);
	return(0);
}
