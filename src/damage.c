/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:39:35 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/12 10:28:39 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	game_over(t_key *k, t_img *img_data)
{
	int x_w;
	int x;
	int y;

	x = 0;
	x_w = k->window_width / 2 - k->game_over.width / 2;
	while (x_w < k->window_width && x < k->game_over.width)
	{
		y = 0;
		while (y < k->window_heigth && y < k->game_over.height)
		{
			img_data->img_data[y * k->window_width + x_w] =
			k->game_over.img_data[y * k->game_over.width + x];
			y++;
		}
		x++;
		x_w++;
	}
}

void	took_damage(t_key *k)
{
	if (!k->player.protected)
		k->player.hp--;
}

void	shot_check(t_key *k)
{
	if (k->player.shot == 1)
		k->player.shot = 0;
	else
		k->player.shot = 1;
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
	if (k->player.protected == 1 && k->player.hp < 50000)
		k->player.hp += 200;
	if (k->player.hp > 50000)
		k->player.hp = 50000;
	add_health_bar(k, dda, img_data);
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
