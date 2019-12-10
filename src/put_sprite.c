/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 12:31:47 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/10 17:26:51 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	took_damage(k);
	while (put->y < put->end_y)
	{
		put->d = put->y * 256 - k->window_heigth
		* 128 + dda->sprite_height * 128;
		dda->texture_y = (put->d * k->texture_sprite.height
		/ dda->sprite_height) / 256;
		if (k->texture_sprite.img_data[dda->texture_y
		* k->texture_sprite.width + dda->texture_x] > 0x101010)
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

void	sprite_loop(t_key *k, t_dda *dda, t_img *img_data, double *z_buffer)
{
	int i;

	i = 0;
	if (k->sprite_save && k->sprite_save->next)
	{
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
}
