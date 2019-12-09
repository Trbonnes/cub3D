/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:17:40 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/09 09:11:59 by trbonnes         ###   ########.fr       */
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

	i = k->dir_x / 35;
	j = k->dir_y / 35;
	count = 0;
	check = 0;
	while (count <= 5)
	{
		if (k->worldmap[(long)(k->pos_y + j) * k->map_width
		+ (long)(k->pos_x + i)] == '1')
			check = 1;
		i += i;
		j += j;
		count++;
	}
	return (check);
}

int		collision_check_backward(t_key *k)
{
	double		i;
	double		j;
	int			count;
	int			check;

	i = k->dir_x / 35;
	j = k->dir_y / 35;
	count = 0;
	check = 0;
	while (count <= 5)
	{
		if (k->worldmap[(long)(k->pos_y - j) * k->map_width
		+ (long)(k->pos_x - i)] == '1')
			check = 1;
		i += i;
		j += j;
		count++;
	}
	return (check);
}

int		collision_check_left(t_key *k)
{
	double		i;
	double		j;
	int			count;
	int			check;

	i = k->dir_x / 35;
	j = k->dir_y / 35;
	count = 0;
	check = 0;
	while (count <= 5)
	{
		if (k->worldmap[(long)(k->pos_y - i) * k->map_width
		+ (long)(k->pos_x - -1 * j)] == '1')
			check = 1;
		i += i;
		j += j;
		count++;
	}
	return (check);
}

int		collision_check_right(t_key *k)
{
	double		i;
	double		j;
	int			count;
	int			check;

	i = k->dir_x / 35;
	j = k->dir_y / 35;
	count = 0;
	check = 0;
	while (count <= 5)
	{
		if (k->worldmap[(long)(k->pos_y + i) * k->map_width
		+ (long)(k->pos_x + -1 * j)] == '1')
			check = 1;
		i += i;
		j += j;
		count++;
	}
	return (check);
}

void	deal_forward(t_key *k)
{
	if (!collision_check_forward(k))
	{
		k->pos_x += k->dir_x / 2;
		k->pos_y += k->dir_y / 2;
	}
}

void	deal_backward(t_key *k)
{
	if (!collision_check_backward(k))
	{
		k->pos_x -= k->dir_x / 2;
		k->pos_y -= k->dir_y / 2;
	}
}

void	deal_left(t_key *k)
{
	if (!collision_check_left(k))
	{
		k->pos_x -= -1 * k->dir_y / 2;
		k->pos_y -= k->dir_x / 2;
	}
}

void	deal_right(t_key *k)
{
	if (!collision_check_right(k))
	{
		k->pos_x += -1 * k->dir_y / 2;
		k->pos_y += k->dir_x / 2;
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

void	put_sprite_init(t_key *k, t_sprite_put *put, t_dda *dda)
{
	put->start_y = -1 * dda->sprite_height / 2 + k->window_heigth / 2;
	if (put->start_y < 0)
		put->start_y = 0;
	put->end_y = dda->sprite_height / 2 + k->window_heigth / 2;
	if (put->end_y >= k->window_heigth)
		put->end_y = k->window_heigth - 1;
	put->start_x = -1 * dda->sprite_width / 2 + dda->sprite_screen_x;
	if (put->start_x < 0)
		put->start_x = 0;
	put->end_x = dda->sprite_width / 2 + dda->sprite_screen_x;
	if (put->end_x >= k->window_width)
		put->end_x = k->window_width - 1;
}

void	put_sprite_loop(t_key *k, t_sprite_put *put,
t_img *img_data, t_dda *dda)
{
	put->y = put->start_y;
	while (put->y < put->end_y)
	{
		put->d = put->y * 256 - k->window_heigth
		* 128 + dda->sprite_height * 128;
		dda->texture_y = (put->d * k->texture_sprite.height
		/ dda->sprite_height) / 256;
		if (k->texture_sprite.img_data[dda->texture_y
		* k->texture_sprite.width + dda->texture_x] != 0)
			img_data->img_data[put->y * k->window_width + put->stripe] =
			k->texture_sprite.img_data[dda->texture_y
			* k->texture_sprite.width + dda->texture_x];
		put->y++;
	}
}

void	img_put_sprite(t_key *k, double *z_buffer, t_img *img_data, t_dda *dda)
{
	t_sprite_put	put;

	put = (t_sprite_put) { 0 };
	put_sprite_init(k, &put, dda);
	put.stripe = put.start_x;
	while (put.stripe < put.end_x)
	{
		dda->texture_x = (int)(256 * (put.stripe - (-1
		* dda->sprite_width / 2 + dda->sprite_screen_x))
		* k->texture_sprite.width / dda->sprite_width) / 256;
		if (dda->transform_y > 0 && put.stripe > 0
		&& put.stripe < k->window_width
		&& dda->transform_y < z_buffer[put.stripe])
			put_sprite_loop(k, &put, img_data, dda);
		put.stripe++;
	}
}

void	pick_s_texture(t_key *k, t_dda *dda, t_img *img_data, int *pixel_index)
{
	dda->texture_y = (long)(pixel_index[1]
	* k->texture_so.height / dda->wall_height);
	img_data->img_data[pixel_index[0]] = k->texture_so.img_data[dda->texture_y
	* k->texture_so.width + dda->texture_x];
}

void	pick_n_texture(t_key *k, t_dda *dda, t_img *img_data, int *pixel_index)
{
	dda->texture_y = (long)(pixel_index[1]
	* k->texture_no.height / dda->wall_height);
	img_data->img_data[pixel_index[0]] = k->texture_no.img_data[dda->texture_y
	* k->texture_no.width + dda->texture_x];
}

void	pick_e_texture(t_key *k, t_dda *dda, t_img *img_data, int *pixel_index)
{
	dda->texture_y = (long)(pixel_index[1]
	* k->texture_ea.height / dda->wall_height);
	img_data->img_data[pixel_index[0]] = k->texture_ea.img_data[dda->texture_y
	* k->texture_ea.width + dda->texture_x];
}

void	pick_w_texture(t_key *k, t_dda *dda, t_img *img_data, int *pixel_index)
{
	dda->texture_y = (long)(pixel_index[1]
	* k->texture_we.height / dda->wall_height);
	img_data->img_data[pixel_index[0]] = k->texture_we.img_data[dda->texture_y
	* k->texture_we.width + dda->texture_x];
}

void	ceiling_loop(t_key *k, t_img *img_data, int *pixel_index)
{
	img_data->img_data[pixel_index[0]] = k->cieling_color;
	pixel_index[0] += k->window_width;
}

void	floor_loop(t_key *k, t_img *img_data,
int *pixel_index, int pixel_number)
{
	img_data->img_data[pixel_index[0]] = k->floor_color;
	if (pixel_number < (int)k->window_heigth - 1)
		pixel_index[0] += k->window_width;
}

void	img_create(t_key *k, int i, t_img *img_data, t_dda *dda)
{
	int		pixel[3];
	int		j;

	pixel[2] = -1;
	pixel[0] = i;
	pixel[1] = 0;
	j = (int)((k->window_heigth - dda->wall_height) / 2);
	while (++pixel[2] < j)
		ceiling_loop(k, img_data, pixel);
	while (++pixel[2] <= j + dda->wall_height && pixel[2] < k->window_heigth)
	{
		if (dda->wall_side == 'S')
			pick_s_texture(k, dda, img_data, pixel);
		else if (dda->wall_side == 'N')
			pick_n_texture(k, dda, img_data, pixel);
		else if (dda->wall_side == 'E')
			pick_e_texture(k, dda, img_data, pixel);
		else
			pick_w_texture(k, dda, img_data, pixel);
		if (pixel[2] < k->window_heigth - 1)
			pixel[0] += k->window_width;
		pixel[1]++;
	}
	while (++pixel[2] <= (int)k->window_heigth)
		floor_loop(k, img_data, pixel, pixel[2]);
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

void	wall_side_ew(t_key *k, t_dda *dda)
{
	dda->wall_distance = (dda->map_x - k->pos_x
	+ (1 - dda->step_x) / 2) / dda->ray_dir_x;
	dda->wall_x = k->pos_y + dda->wall_distance * dda->ray_dir_y;
	dda->wall_x -= (long)dda->wall_x;
}

void	wall_side_ns(t_key *k, t_dda *dda)
{
	dda->wall_distance = (dda->map_y - k->pos_y
	+ (1 - dda->step_y) / 2) / dda->ray_dir_y;
	dda->wall_x = k->pos_x + dda->wall_distance * dda->ray_dir_x;
	dda->wall_x -= (long)dda->wall_x;
}

void	wall_texture_s(t_key *k, t_dda *dda)
{
	dda->texture_x = (long)(dda->wall_x * (double)k->texture_so.width);
	if (dda->ray_dir_y > 0)
		dda->texture_x = k->texture_so.width - dda->texture_x - 1;
}

void	wall_texture_n(t_key *k, t_dda *dda)
{
	dda->texture_x = (long)(dda->wall_x * (double)k->texture_no.width);
	if (dda->ray_dir_y > 0)
		dda->texture_x = k->texture_no.width - dda->texture_x - 1;
}

void	wall_texture_e(t_key *k, t_dda *dda)
{
	dda->texture_x = (long)(dda->wall_x * (double)k->texture_ea.width);
	if (dda->ray_dir_x < 0)
		dda->texture_x = k->texture_ea.width - dda->texture_x - 1;
}

void	wall_texture_w(t_key *k, t_dda *dda)
{
	dda->texture_x = (long)(dda->wall_x * (double)k->texture_we.width);
	if (dda->ray_dir_x < 0)
		dda->texture_x = k->texture_we.width - dda->texture_x - 1;
}

void	wall_calculate(t_key *k, t_dda *dda)
{
	if (dda->wall_side == 'E' || dda->wall_side == 'W')
		wall_side_ew(k, dda);
	else
		wall_side_ns(k, dda);
	dda->wall_height = k->window_heigth / dda->wall_distance;
	if (dda->wall_side == 'S')
		wall_texture_s(k, dda);
	else if (dda->wall_side == 'N')
		wall_texture_n(k, dda);
	else if (dda->wall_side == 'E')
		wall_texture_e(k, dda);
	else
		wall_texture_w(k, dda);
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

void	sprite_loop(t_key *k, t_dda *dda, t_img *img_data, double *z_buffer)
{
	int i;

	i = 0;
	ft_lst_sort(k->sprite_save->next, k);
	k->sprite = k->sprite_save->next;
	while (i < k->sprite_num)
	{
		dda->sprite_x = k->sprite->x - k->pos_x;
		dda->sprite_y = k->sprite->y - k->pos_y;
		dda->invert = 1.0 / (k->plane_x * k->dir_y - k->dir_x * k->plane_y);
		dda->transform_x = dda->invert
		* (k->dir_y * dda->sprite_x - k->dir_x * dda->sprite_y);
		dda->transform_y = dda->invert * (-1 * k->plane_y
		* dda->sprite_x + k->plane_x * dda->sprite_y);
		dda->sprite_screen_x = (int)((k->window_width / 2)
		* (1 + dda->transform_x / dda->transform_y));
		dda->sprite_height = abs((int)(k->window_heigth / (dda->transform_y)));
		dda->sprite_width = abs((int)(k->window_heigth / (dda->transform_y)));
		img_put_sprite(k, z_buffer, img_data, dda);
		k->sprite = k->sprite->next;
		i++;
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
	if (!k->save_bool)
		mlx_put_image_to_window(k->mlx_ptr, k->win_ptr, k->img_ptr, 0, 0);
	else
		k->dda_img_data = img_data.img_data;
	return (0);
}
