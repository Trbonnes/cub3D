/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:17:40 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/05 12:33:20 by trbonnes         ###   ########.fr       */
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

	i = k->dir_x / 25;
	j = k->dir_y / 25;
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

	i = k->dir_x / 25;
	j = k->dir_y / 25;
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

	i = k->dir_x / 25;
	j = k->dir_y / 25;
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

void	img_put_sprite(t_key *k, int i, t_img *img_data, t_dda *dda)
{
	int		pixel_index;
	int		pixel_number;
	int		j;
	int		texture_index;

	pixel_number = 0;
	pixel_index = i;
	j = (int)((k->window_heigth - dda->sprite_height) / 2);
	texture_index = 0;
	while (pixel_number++ < j)
		pixel_index += k->window_width;
	while (pixel_number++ <= (j + (int)dda->sprite_height))
	{
		dda->texture_y = (long)(texture_index * k->texture_sprite.height / dda->sprite_height);
		img_data->img_data[pixel_index] = k->texture_sprite.img_data[dda->texture_y * k->texture_sprite.width + dda->texture_x];
		pixel_index += k->window_width;
		texture_index++;
	}
}

void	img_create(t_key *k, int i, t_img *img_data, t_dda *dda)
{
	int		pixel_index;
	int		pixel_number;
	int		j;
	int		texture_index;

	pixel_number = 0;
	pixel_index = i;
	j = (int)((k->window_heigth - dda->wall_height) / 2);
	texture_index = 0;
	while (pixel_number++ < j)
	{
		img_data->img_data[pixel_index] = k->cieling_color;
		pixel_index += k->window_width;
	}
	while (pixel_number++ <= (j + (int)dda->wall_height))
	{
		if (dda->wall_side == 'S')
		{
			dda->texture_y = (long)(texture_index * k->texture_so.height / dda->wall_height);
			img_data->img_data[pixel_index] = k->texture_so.img_data[dda->texture_y * k->texture_so.width + dda->texture_x];
		}
		else if (dda->wall_side == 'N')
		{
			dda->texture_y = (long)(texture_index * k->texture_no.height / dda->wall_height);
			img_data->img_data[pixel_index] = k->texture_no.img_data[dda->texture_y * k->texture_no.width + dda->texture_x];
		}
		else if (dda->wall_side == 'E')
		{
			dda->texture_y = (long)(texture_index * k->texture_ea.height / dda->wall_height);
			img_data->img_data[pixel_index] = k->texture_ea.img_data[dda->texture_y * k->texture_ea.width + dda->texture_x];
		}
		else
		{
			dda->texture_y = (long)(texture_index * k->texture_we.height / dda->wall_height);
			img_data->img_data[pixel_index] = k->texture_we.img_data[dda->texture_y * k->texture_we.width + dda->texture_x];
		}
		pixel_index += k->window_width;
		texture_index++;
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

void	sprite_calculate(t_key *k, t_dda *dda)
{
	if (dda->sprite_side == 'E' || dda->sprite_side == 'W')
	{
		dda->sprite_distance = (dda->map_x - k->pos_x
		+ (1 - dda->step_x) / 2) / dda->ray_dir_x;
		dda->sprite_x = k->pos_y + dda->sprite_distance * dda->ray_dir_y;
		dda->sprite_x -= (long)dda->sprite_x;
	}
	else
	{
		dda->sprite_distance = (dda->map_y - k->pos_y
		+ (1 - dda->step_y) / 2) / dda->ray_dir_y;
		dda->sprite_x = k->pos_x + dda->sprite_distance * dda->ray_dir_x;
		dda->sprite_x -= (long)dda->sprite_x;
	}
	dda->sprite_height = k->window_heigth / dda->sprite_distance;
	dda->texture_x = (long)(dda->sprite_x * (double)k->texture_sprite.width);
	if (dda->sprite_side == 'S' && dda->ray_dir_y > 0)
		dda->texture_x = k->texture_sprite.width - dda->texture_x - 1;
	else if (dda->sprite_side == 'N' && dda->ray_dir_y > 0)
		dda->texture_x = k->texture_sprite.width - dda->texture_x - 1;
	else if (dda->sprite_side == 'E' && dda->ray_dir_x < 0)
		dda->texture_x = k->texture_sprite.width - dda->texture_x - 1;
	else if (dda->ray_dir_x < 0)
		dda->texture_x = k->texture_sprite.width - dda->texture_x - 1;
}

void	sprite_loop(t_key *k, t_dda *dda)
{
	while (dda->sprite != 1)
	{
		if (dda->dist_x < dda->dist_y)
		{
			dda->dist_x += dda->decalage_ray_x;
			dda->map_x += dda->step_x;
			if (dda->map_x > k->pos_x)
				dda->sprite_side = 'W';
			else
				dda->sprite_side = 'E';
		}
		else
		{
			dda->dist_y += dda->decalage_ray_y;
			dda->map_y += dda->step_y;
			if (dda->map_y > k->pos_y)
				dda->sprite_side = 'N';
			else
				dda->sprite_side = 'S';
		}
		if (k->worldmap[dda->map_y * k->map_width + dda->map_x] == '2')
			dda->sprite = 1;
		if (k->worldmap[dda->map_y * k->map_width + dda->map_x] == '1')
			break ;
	}
}

void	wall_calculate(t_key *k, t_dda *dda)
{
	if (dda->wall_side == 'E' || dda->wall_side == 'W')
	{
		dda->wall_distance = (dda->map_x - k->pos_x
		+ (1 - dda->step_x) / 2) / dda->ray_dir_x;
		dda->wall_x = k->pos_y + dda->wall_distance * dda->ray_dir_y;
		dda->wall_x -= (long)dda->wall_x;
	}
	else
	{
		dda->wall_distance = (dda->map_y - k->pos_y
		+ (1 - dda->step_y) / 2) / dda->ray_dir_y;
		dda->wall_x = k->pos_x + dda->wall_distance * dda->ray_dir_x;
		dda->wall_x -= (long)dda->wall_x;
	}
	dda->wall_height = k->window_heigth / dda->wall_distance;
	if (dda->wall_side == 'S')
	{
		dda->texture_x = (long)(dda->wall_x * (double)k->texture_so.width);
		if (dda->ray_dir_y > 0)
			dda->texture_x = k->texture_so.width - dda->texture_x - 1;
	}
	else if (dda->wall_side == 'N')
	{
		dda->texture_x = (long)(dda->wall_x * (double)k->texture_no.width);
		if (dda->ray_dir_y > 0)
			dda->texture_x = k->texture_no.width - dda->texture_x - 1;
	}
	else if (dda->wall_side == 'E')
	{
		dda->texture_x = (long)(dda->wall_x * (double)k->texture_ea.width);
		if (dda->ray_dir_x < 0)
			dda->texture_x = k->texture_ea.width - dda->texture_x - 1;
	}
	else
	{
		dda->texture_x = (long)(dda->wall_x * (double)k->texture_we.width);
		if (dda->ray_dir_x < 0)
			dda->texture_x = k->texture_we.width - dda->texture_x - 1;
	}
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
	int i;

	i = 0;
	while (i <= k->window_width)
	{
		dda_init(k, dda, i);
		wall_loop(k, dda);
		wall_calculate(k, dda);
		img_create(k, i, img_data, dda);
		dda_init(k, dda, i);
		sprite_loop(k, dda);
		if (dda->sprite == 1)
		{
			sprite_calculate(k, dda);
			img_put_sprite(k, i, img_data, dda);
		}
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
