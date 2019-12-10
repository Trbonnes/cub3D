/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:39:35 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/10 17:47:54 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	game_over(t_key *k, t_img *img_data)
{
	int x;
	int y;

	x = 0;
	printf("dead\n");
	while (x < k->window_width && x < k->game_over.width)
	{
		y = 0;
		while (y < k->window_heigth && y < k->game_over.height)
		{
			img_data->img_data[y * k->window_width + x] =
			k->game_over.img_data[y * k->game_over.width + x];
			y++;
		}
		x++;
	}
}

void	took_damage(t_key *k)
{
	if (!k->player.protected)
	{
		printf("%d\n", k->player.hp);
		k->player.hp--;
	}
}