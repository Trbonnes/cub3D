/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 13:41:25 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/12 09:14:10 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			add_health_bar(t_key *k, t_dda *dda, t_img *img_data)
{
	t_sprite_put	put;
	int				x;

	put.start_x = 5;
	put.end_x = put.start_x + ((k->health_bar.width * k->player.hp) / 50000);
	put.start_y = 5;
	put.end_y = k->health_bar.height;
	x = put.start_x;
	dda->texture_x = 0;
	while (x < put.end_x)
	{
		put.y = put.start_y;
		dda->texture_y = 0;
		while (put.y < put.end_y && put.y < k->window_heigth)
		{
			img_data->img_data[put.y * k->window_width + x] =
			k->health_bar.img_data[dda->texture_y
			* k->health_bar.width + dda->texture_x];
			put.y++;
			dda->texture_y++;
		}
		x++;
		dda->texture_x++;
	}
}

t_sprite_put	add_saber_init(t_key *k, t_dda *dda, int *x)
{
	t_sprite_put	put;

	put.start_x = k->window_width - (k->texture_saber.width + 5);
	put.end_x = put.start_x + k->texture_saber.width;
	put.start_y = k->window_heigth - k->texture_saber.height;
	if (put.start_y < 0)
		put.start_y = 0;
	put.end_y = k->window_heigth;
	*x = put.start_x;
	dda->texture_x = 0;
	return (put);
}

void			add_saber(t_key *k, t_dda *dda, t_img *img_data)
{
	t_sprite_put	put;
	int				x;

	put = add_saber_init(k, dda, &x);
	while (x < put.end_x && x < k->window_width)
	{
		put.y = put.start_y;
		dda->texture_y = 0;
		while (put.y < put.end_y && put.y < k->window_heigth)
		{
			if (k->texture_saber.img_data[dda->texture_y
			* k->texture_saber.width + dda->texture_x] > 0x505050)
				img_data->img_data[put.y * k->window_width + x] =
				k->texture_saber.img_data[dda->texture_y
				* k->texture_saber.width + dda->texture_x];
			put.y++;
			if (k->texture_saber.height / k->window_heigth < 1)
				dda->texture_y++;
			else
				dda->texture_y = put.y *
				(k->texture_saber.height / k->window_heigth);
		}
		x++;
		dda->texture_x++;
	}
}

t_sprite_put	add_saber_attack_init(t_key *k, t_dda *dda, int *x)
{
	t_sprite_put	put;

	put.start_x = k->window_width - (k->texture_saber_a.width);
	if (put.start_x < 0)
		put.start_x = 0;
	put.end_x = put.start_x + k->texture_saber_a.width;
	put.start_y = k->window_heigth - k->texture_saber_a.height;
	if (put.start_y < 0)
		put.start_y = 0;
	put.end_y = k->window_heigth;
	*x = put.start_x;
	dda->texture_x = 0;
	return (put);
}

void			add_saber_attack(t_key *k, t_dda *dda, t_img *img_data)
{
	t_sprite_put	put;
	int				x;

	put = add_saber_attack_init(k, dda, &x);
	while (x < put.end_x && x < k->window_width)
	{
		put.y = put.start_y;
		dda->texture_y = 0;
		while (put.y < put.end_y && put.y < k->window_heigth)
		{
			if (k->texture_saber_a.img_data[dda->texture_y
			* k->texture_saber_a.width + dda->texture_x] > 0x505050)
				img_data->img_data[put.y * k->window_width + x] =
				k->texture_saber_a.img_data[dda->texture_y
				* k->texture_saber_a.width + dda->texture_x];
			put.y++;
			if (k->texture_saber_a.height / k->window_heigth < 1)
				dda->texture_y++;
			else
				dda->texture_y = put.y *
				(k->texture_saber_a.height / k->window_heigth);
		}
		x++;
		dda->texture_x++;
	}
}
