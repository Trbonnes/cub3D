#include "mlx.h"
#include "X.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define mapHeight 6
#define mapWidth 7
#define windowHeight 480
#define windowWidth 720

static char map[] = {
  1, 1, 1, 1, 1, 1, 1,
  1, 0, 0, 0, 0, 0, 1,
  1, 0, 1, 0, 1, 0, 1,
  1, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 1,
  1, 1, 1, 1, 1, 1, 1
};

typedef	struct		s_key
{
	void    *mlx_ptr;
	void    *win_ptr;
  double  Pos_X;
  double  Pos_Y;
  double  Projection_distance;
  double  Ray_angle;
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
  if (key == 126 && k->Pos_Y > 0)
    k->Pos_Y = k->Pos_Y - 1;
  if (key == 125 && k->Pos_Y < mapHeight)
    k->Pos_Y = k->Pos_Y + 1;
  if (key == 123 && k->Pos_X > 0)
    k->Pos_X = k->Pos_X - 1;
  if (key == 124 && k->Pos_X < mapWidth)
    k->Pos_X = k->Pos_X + 1;
  return (0);
}

int loop_hook(t_key *k)
{
  //double    Dir_X;
  //double    Dir_Y;
  int       Dir;
  double    Plane_X;
  double    Plane_Y;
  double    Ray_X;
  double    Ray_Y;
  double    intersection_X;
  double    intersection_Y;
  double    intersection_tmp;
  long      Horizontal_Wall_X;
  long      Horizontal_Wall_Y;
  long      Vertical_Wall_X;
  long      Vertical_Wall_Y;
  long      intersection_decalage_X;
  long      intersection_decalage_Y;
  int       Wall;
  int       i;
  double    decal_ray;
  double    WallHeight_Horizontal;
  double    WallHeight_Vertical;
  double    WallHeight;
  int       j;
  int       pixel_number;
  int       Wall_color;

  Plane_X = windowWidth;
  Plane_Y = windowHeight;
  Dir = 1;
  i = 0;
  while(i <= windowWidth)
  {
    //HORIZONTAL

    if (Dir == 1)
    {
      intersection_X = k->Pos_X ;
      intersection_Y = (long)k->Pos_Y + 1;
      intersection_decalage_Y = -1;
    }
    else if (Dir == 2)
    {
      intersection_X= (long)k->Pos_X;
      Horizontal_Wall_Y = (long)k->Pos_Y;
      intersection_decalage_Y = 1;
    }
    intersection_decalage_X = 1/tan(1.0472);
    while (Wall != 1)
    {
      if (k->worldMap[Horizontal_Wall_Y * mapWidth + Horizontal_Wall_X] == 1)
        Wall = 1;
      else
      {
      }
    }

    //printf("Horizontal Heiht: %f\n", WallHeight_Horizontal);
    //printf("Vertical Height: %f", WallHeight_Vertical);
    if (WallHeight_Horizontal >= WallHeight_Vertical)
    {
      //printf("Horizontal\n");
      WallHeight = WallHeight_Horizontal;
      Wall_color = 0x000000;
    }
    else
    {
      WallHeight = WallHeight_Vertical;
      Wall_color = 0xff0000;
    }
    printf("%f\n", WallHeight);
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
      mlx_pixel_put(k->mlx_ptr, k->win_ptr, windowWidth - i, pixel_number, Wall_color);
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
  param.Projection_distance = (windowWidth / 2) / tan(0.523599);
  param.Ray_angle = 1.0472/windowWidth;
  param.Pos_X = 3.5;
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
