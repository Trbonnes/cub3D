/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:17:40 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/10 17:58:10 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	wall_loop(t_key *k, t_dda *dda)
{
	while (dda->wall != 1)
	{
		if (dda->dist_x < dda->dist_y)
		{
			dda->dist_x += dda->decalage_ray_x;
			dda->map_x += dda->step_x;
			if (dda->map_x > k->pos_x)
				dda->wall_side = 'W';
			else
				dda->wall_side = 'E';
		}
		else
		{
			dda->dist_y += dda->decalage_ray_y;
			dda->map_y += dda->step_y;
			if (dda->map_y > k->pos_y)
				dda->wall_side = 'N';
			else
				dda->wall_side = 'S';
		}
		if (k->worldmap[dda->map_y * k->map_width + dda->map_x] == '1')
			dda->wall = 1;
	}
}

void	window_loop(t_key *k, t_dda *dda, t_img *img_data)
{
	int		i;
	double	z_buffer[k->window_width + 1];

	i = 0;
	while (i <= k->window_width)
	{
		dda_init(k, dda, i);
		wall_loop(k, dda);
		wall_calculate(k, dda);
		z_buffer[i] = dda->wall_distance;
		img_create(k, i, img_data, dda);
		i++;
	}
	sprite_loop(k, dda, img_data, z_buffer);
	add_saber(k, dda, img_data);
}

int		loop_hook(t_key *k)
{
	t_dda	dda;
	t_img	img_data;

	img_data = (t_img) { 0 };
	dda = (t_dda) { 0 };
	if (k->img_ptr)
		mlx_destroy_image(k->mlx_ptr, k->img_ptr);
	k->img_ptr = mlx_new_image(k->mlx_ptr, k->window_width, k->window_heigth);
	img_data.img_data = (int *)mlx_get_data_addr(k->img_ptr,
	&img_data.bits_per_pixel, &img_data.size_line, &img_data.endian);
	if (k->player.hp <= 0)
		game_over(k, &img_data);
	else
		window_loop(k, &dda, &img_data);
	if (!k->save_bool)
		mlx_put_image_to_window(k->mlx_ptr, k->win_ptr, k->img_ptr, 0, 0);
	else
		k->dda_img_data = img_data.img_data;
	return (0);
}

void	window_loop_attack(t_key *k, t_dda *dda, t_img *img_data)
{
	int		i;
	double	z_buffer[k->window_width + 1];

	i = 0;
	while (i <= k->window_width)
	{
		dda_init(k, dda, i);
		wall_loop(k, dda);
		wall_calculate(k, dda);
		z_buffer[i] = dda->wall_distance;
		img_create(k, i, img_data, dda);
		i++;
	}
	sprite_loop(k, dda, img_data, z_buffer);
	add_saber_attack(k, dda, img_data);
}

int		hook_attack(t_key *k)
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
	window_loop_attack(k, &dda, &img_data);
	mlx_put_image_to_window(k->mlx_ptr, k->win_ptr, k->img_ptr, 0, 0);
	return (0);
}