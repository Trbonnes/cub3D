/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:17:40 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/06 15:12:41 by trbonnes         ###   ########.fr       */
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

void	img_put_sprite(t_key *k, double	z_buffer[k->window_width + 1], t_img *img_data, t_dda *dda)
{
	int		start_y;
	int		end_y;
	int		start_x;
	int		end_x;
	int		stripe;
	int		y;
	int		d;

	start_y = -1 * dda->sprite_height / 2 + k->window_heigth / 2;
    if(start_y < 0) 
		start_y = 0;
    end_y = dda->sprite_height / 2 + k->window_heigth / 2;
    if(end_y >= k->window_heigth) 
		end_y = k->window_heigth - 1;
	start_x = -1* dda->sprite_width / 2 + dda->sprite_screen_x;
    if(start_x < 0)
		start_x = 0;
    end_x = dda->sprite_width / 2 + dda->sprite_screen_x;
    if(end_x >= k->window_width)
		end_x = k->window_width - 1;
	stripe = start_x;
	while (stripe < end_x)
	{
		dda->texture_x = (int)(256 * (stripe - (-1 * dda->sprite_width / 2 + dda->sprite_screen_x)) * k->texture_sprite.width / dda->sprite_width) / 256;
        if(dda->transform_y > 0 && stripe > 0 && stripe < k->window_width && dda->transform_y < z_buffer[stripe])
		{
			y = start_y;
			while (y < end_y)
			{
				d = (y) * 256 - k->window_heigth * 128 + dda->sprite_height * 128;
				dda->texture_y = ((d * k->texture_sprite.height) / dda->sprite_height) / 256;
				if (k->texture_sprite.img_data[dda->texture_y * k->texture_sprite.width + dda->texture_x] != 0)
					img_data->img_data[y * k->window_width + stripe] = k->texture_sprite.img_data[dda->texture_y * k->texture_sprite.width + dda->texture_x];
				y++;
			}
		}
		stripe++;
	}
}

void	img_create(t_key *k, int i, t_img *img_data, t_dda *dda)
{
	int		pixel_index;
	int		pixel_number;
	int		j;
	int		texture_index;

	pixel_number = -1;
	pixel_index = i;
	j = (int)((k->window_heigth - dda->wall_height) / 2);
	texture_index = 0;
	while (++pixel_number < j)
	{
		img_data->img_data[pixel_index] = k->cieling_color;
		pixel_index += k->window_width;
	}
	while (++pixel_number <= (j + (int)dda->wall_height) && pixel_number < k->window_heigth)
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
		if (pixel_number < k->window_heigth - 1)
			pixel_index += k->window_width;
		texture_index++;
	}
	while (++pixel_number <= (int)k->window_heigth)
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
	i = 0;
	ft_lst_sort(k->sprite_save->next, k);
	k->sprite = k->sprite_save->next;
	while (i < k->sprite_num)
	{
		dda->sprite_x = k->sprite->x - k->pos_x;
		dda->sprite_y = k->sprite->y - k->pos_y;
		dda->invert = 1.0 / (k->plane_x * k->dir_y - k->dir_x * k->plane_y);
		dda->transform_x = dda->invert * (k->dir_y * dda->sprite_x - k->dir_x * dda->sprite_y);
		dda->transform_y = dda->invert * (-1 * k->plane_y * dda->sprite_x + k->plane_x * dda->sprite_y);
		dda->sprite_screen_x = (int)((k->window_width / 2) * (1 + dda->transform_x / dda->transform_y));
		dda->sprite_height = abs((int)(k->window_heigth / (dda->transform_y)));
		dda->sprite_width = abs((int)(k->window_heigth / (dda->transform_y)));
		img_put_sprite(k, z_buffer, img_data ,dda);
		k->sprite = k->sprite->next;
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
