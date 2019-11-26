#include "mlx.h"
#include "X.h"
#include <stdio.h>
#include <stdlib.h>

typedef	struct		s_key
{
	void *mlx_ptr;
	void *win_ptr;
}					t_key;

int			deal_key(int key, void *param)
{
	t_key	*k;
	static int u_y = 251;
	static int l_y = 250;
	static int m_y = 250;
	static int r_y = 250;
	static int b_y = 249;
	static int u_x = 250;
	static int l_x = 249;
	static int m_x = 250;
	static int r_x = 251;
	static int b_x = 250;

	k = param;
	printf("key : %d\n", key);
	if (key == 53)
		mlx_destroy_window(k->mlx_ptr, k->win_ptr);
	if (key == 126)
	{
		mlx_clear_window(k->mlx_ptr, k->win_ptr);
		u_y--;
		l_y--;
		m_y--;
		r_y--;
		b_y--;
		mlx_pixel_put(k->mlx_ptr, k->win_ptr, m_x, m_y, 0xffffff);
		mlx_pixel_put(k->mlx_ptr, k->win_ptr, l_x, l_y, 0xffffff);
		mlx_pixel_put(k->mlx_ptr, k->win_ptr, r_x, r_y, 0xffffff);
		mlx_pixel_put(k->mlx_ptr, k->win_ptr, u_x, u_y, 0xffffff);
		mlx_pixel_put(k->mlx_ptr, k->win_ptr, b_x, b_y, 0xffffff);
	}
	if (key == 125)
	{
		mlx_clear_window(k->mlx_ptr, k->win_ptr);
		u_y++;
		l_y++;
		m_y++;
		r_y++;
		b_y++;
		mlx_pixel_put(k->mlx_ptr, k->win_ptr, m_x, m_y, 0xffffff);
		mlx_pixel_put(k->mlx_ptr, k->win_ptr, l_x, l_y, 0xffffff);
		mlx_pixel_put(k->mlx_ptr, k->win_ptr, r_x, r_y, 0xffffff);
		mlx_pixel_put(k->mlx_ptr, k->win_ptr, u_x, u_y, 0xffffff);
		mlx_pixel_put(k->mlx_ptr, k->win_ptr, b_x, b_y, 0xffffff);
	}
	if (key == 123)
	{
		mlx_clear_window(k->mlx_ptr, k->win_ptr);
		u_x--;
		l_x--;
		m_x--;
		r_x--;
		b_x--;
		mlx_pixel_put(k->mlx_ptr, k->win_ptr, m_x, m_y, 0xffffff);
		mlx_pixel_put(k->mlx_ptr, k->win_ptr, l_x, l_y, 0xffffff);
		mlx_pixel_put(k->mlx_ptr, k->win_ptr, r_x, r_y, 0xffffff);
		mlx_pixel_put(k->mlx_ptr, k->win_ptr, u_x, u_y, 0xffffff);
		mlx_pixel_put(k->mlx_ptr, k->win_ptr, b_x, b_y, 0xffffff);
	}
	if (key == 124)
	{
		mlx_clear_window(k->mlx_ptr, k->win_ptr);
		u_x++;
		l_x++;
		m_x++;
		r_x++;
		b_x++;
		mlx_pixel_put(k->mlx_ptr, k->win_ptr, m_x, m_y, 0xffffff);
		mlx_pixel_put(k->mlx_ptr, k->win_ptr, l_x, l_y, 0xffffff);
		mlx_pixel_put(k->mlx_ptr, k->win_ptr, r_x, r_y, 0xffffff);
		mlx_pixel_put(k->mlx_ptr, k->win_ptr, u_x, u_y, 0xffffff);
		mlx_pixel_put(k->mlx_ptr, k->win_ptr, b_x, b_y, 0xffffff);
	}
	return (0);
}

int 		main()
{
	void 	*mlx_ptr;
	void 	*win_ptr;
	t_key	param;

	param = (t_key) {};
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "cub3D");
	param.mlx_ptr = mlx_ptr;
	param.win_ptr = win_ptr;
	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xffffff);
	mlx_pixel_put(mlx_ptr, win_ptr, 249, 250, 0xffffff);
	mlx_pixel_put(mlx_ptr, win_ptr, 251, 250, 0xffffff);
	mlx_pixel_put(mlx_ptr, win_ptr, 250, 251, 0xffffff);
	mlx_pixel_put(mlx_ptr, win_ptr, 250, 249, 0xffffff);
	mlx_hook(win_ptr, KeyPress, KeyPressMask, deal_key, &param);
	mlx_loop(mlx_ptr);
	return(0);
}
