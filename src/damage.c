/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:39:35 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/11 16:20:45 by trbonnes         ###   ########.fr       */
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