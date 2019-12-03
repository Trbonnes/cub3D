/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:17:40 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/03 17:29:06 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		window_quit(t_key *k)
{
	mlx_destroy_window(k->mlx_ptr, k->win_ptr);
	write(1, "ESC\nExiting\n", 12);
	exit(0);
	return (0);
}

int		collision_check_forward(t_key *k)
{
	double		i;
	double		j;
	int			count;
	int			check;

	i = k->dir_x / 25;
	j = k->dir_y / 25;
	count = 0;
	check = 0;
	while (count <= 5)
	{
		if (k->worldmap[(long)(k->pos_y + j) * k->map_width + (long)(k->pos_x + i)] == '1')
			check = 1;
		i += i;
		j += j;
		count++;
		printf("i: %lf\n", i);
		printf("j: %lf\n", j);
	}
	printf("%d\n", check);
	return (check);
}

int		collision_check_backward(t_key *k)
{
	double		i;
	double		j;
	int			count;
	int			check;

	i = k->dir_x / 25;
	j = k->dir_y / 25;
	count = 0;
	check = 0;
	while (count <= 5)
	{
		if (k->worldmap[(long)(k->pos_y - j) * k->map_width + (long)(k->pos_x - i)] == '1')
			check = 1;
		i += i;
		j += j;
		count++;
		printf("i: %lf\n", i);
		printf("j: %lf\n", j);
	}
	printf("%d\n", check);
	return (check);
}

int		collision_check_left(t_key *k)
{
	double		i;
	double		j;
	int			count;
	int			check;

	i = k->dir_x / 25;
	j = k->dir_y / 25;
	count = 0;
	check = 0;
	while (count <= 5)
	{
		if (k->worldmap[(long)(k->pos_y - i) * k->map_width + (long)(k->pos_x - -1 * j)] == '1')
			check = 1;
		i += i;
		j += j;
		count++;
		printf("i: %lf\n", i);
		printf("j: %lf\n", j);
	}
	printf("%d\n", check);
	return (check);
}

int		collision_check_right(t_key *k)
{
	double		i;
	double		j;
	int			count;
	int			check;

	i = k->dir_x / 25;
	j = k->dir_y / 25;
	count = 0;
	check = 0;
	while (count <= 5)
	{
		if (k->worldmap[(long)(k->pos_y + i) * k->map_width + (long)(k->pos_x + -1 * j)] == '1')
			check = 1;
		i += i;
		j += j;
		count++;
		printf("i: %lf\n", i);
		printf("j: %lf\n", j);
	}
	printf("%d\n", check);
	return (check);
}

void	deal_forward(t_key *k)
{
	if (!collision_check_forward(k))
	{
		k->pos_x += k->dir_x;
		k->pos_y += k->dir_y;
	}
}

void	deal_backward(t_key *k)
{
	if (!collision_check_backward(k))
	{
		k->pos_x -= k->dir_x;
		k->pos_y -= k->dir_y;
	}
}

void	deal_left(t_key *k)
{
	if (!collision_check_left(k))
	{
		k->pos_x -= -1 * k->dir_y;
		k->pos_y -= k->dir_x;
	}
}

void	deal_right(t_key *k)
{
	if (!collision_check_right(k))
	{
		k->pos_x += -1 * k->dir_y;
		k->pos_y += k->dir_x;
	}
}

int		deal_key(int key, t_key *k)
{
	if (key == 53)
		window_quit(k);
	if (key == 13)
		deal_forward(k);
	if (key == 1)
		deal_backward(k);
	if (key == 0)
		deal_left(k);
	if (key == 2)
		deal_right(k);
	if (key == 124)
		k->angle += ROT;
	if (key == 123)
		k->angle -= ROT;
	k->dir_x = cos(k->angle);
	k->dir_y = sin(k->angle);
	k->plane_x = -1 * k->dir_y;
	k->plane_y = k->dir_x;
	return (0);
}

void	img_create(t_key *k, int i, t_img *img_data, int wall_height)
{
	int		pixel_index;
	int		pixel_number;
	int		j;

	pixel_number = 0;
	pixel_index = i;
	j = (int)((k->window_heigth - wall_height) / 2);
	while (pixel_number++ < j)
	{
		img_data->img_data[pixel_index] = k->cieling_color;
		pixel_index += k->window_width;
	}
	while (pixel_number++ <= (j + (int)wall_height))
	{
		img_data->img_data[pixel_index] = img_data->wall_color;
		pixel_index += k->window_width;
	}
	while (pixel_number++ <= (int)k->window_heigth)
	{
		img_data->img_data[pixel_index] = k->floor_color;
		if (pixel_number < (int)k->window_heigth - 1)
			pixel_index += k->window_width;
	}
}

void	ray_init(t_key *k, t_dda *dda)
{
	if (dda->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->dist_x = (k->pos_x - dda->map_x) * dda->decalage_ray_x;
	}
	else
	{
		dda->step_x = 1;
		dda->dist_x = (dda->map_x + 1.0 - k->pos_x) * dda->decalage_ray_x;
	}
	if (dda->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->dist_y = (k->pos_y - dda->map_y) * dda->decalage_ray_y;
	}
	else
	{
		dda->step_y = 1;
		dda->dist_y = (dda->map_y + 1.0 - k->pos_y) * dda->decalage_ray_y;
	}
}

void	dda_init(t_key *k, t_dda *dda, int i)
{
	k->camera_x = 2 * i / (double)k->window_width - 1;
	dda->ray_dir_x = k->dir_x + k->plane_x * k->camera_x;
	dda->ray_dir_y = k->dir_y + k->plane_y * k->camera_x;
	dda->map_x = (long)k->pos_x;
	dda->map_y = (long)k->pos_y;
	dda->decalage_ray_x = fabs(1 / dda->ray_dir_x);
	dda->decalage_ray_y = fabs(1 / dda->ray_dir_y);
	dda->wall = 0;
	ray_init(k, dda);
}

void	wall_calculate(t_key *k, t_dda *dda, t_img *img_data)
{
	if (dda->wall_side == 0)
	{
		dda->wall_distance = (dda->map_x - k->pos_x
		+ (1 - dda->step_x) / 2) / dda->ray_dir_x;
	}
	else
	{
		dda->wall_distance = (dda->map_y - k->pos_y
		+ (1 - dda->step_y) / 2) / dda->ray_dir_y;
	}
	dda->wall_height = k->window_heigth / dda->wall_distance;
	if (dda->wall_side == 0)
		img_data->wall_color = 0x00000000;
	else
		img_data->wall_color = 0x00ff0000;
}

void	wall_loop(t_key *k, t_dda *dda)
{
	while (dda->wall != 1)
	{
		if (dda->dist_x < dda->dist_y)
		{
			dda->dist_x += dda->decalage_ray_x;
			dda->map_x += dda->step_x;
			dda->wall_side = 0;
		}
		else
		{
			dda->dist_y += dda->decalage_ray_y;
			dda->map_y += dda->step_y;
			dda->wall_side = 1;
		}
		if (k->worldmap[dda->map_y * k->map_width + dda->map_x] == '1')
			dda->wall = 1;
	}
}

void	window_loop(t_key *k, t_dda *dda, t_img *img_data)
{
	int i;

	i = 0;
	while (i <= k->window_width)
	{
		dda_init(k, dda, i);
		wall_loop(k, dda);
		wall_calculate(k, dda, img_data);
		img_create(k, i, img_data, dda->wall_height);
		i++;
	}
}

int		loop_hook(t_key *k)
{
	t_dda	dda;
	t_img	img_data;

	img_data = (t_img) { 0 };
	dda = (t_dda) { 0 };
	img_data = (t_img) { 0 };
	if (k->img_ptr)
		mlx_destroy_image(k->mlx_ptr, k->img_ptr);
	k->img_ptr = mlx_new_image(k->mlx_ptr, k->window_width, k->window_heigth);
	img_data.img_data = (int *)mlx_get_data_addr(k->img_ptr,
	&img_data.bits_per_pixel, &img_data.size_line, &img_data.endian);
	window_loop(k, &dda, &img_data);
	mlx_put_image_to_window(k->mlx_ptr, k->win_ptr, k->img_ptr, 0, 0);
	return (0);
}
