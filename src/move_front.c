/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_front.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 12:27:36 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/11 16:16:01 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		collision_check_forward(t_key *k)
{
	double		i;
	double		j;
	int			count;
	char		check;

	i = k->dir_x / 35;
	j = k->dir_y / 35;
	count = 0;
	check = 0;
	while (count <= 5)
	{
		check = k->worldmap[(long)(k->pos_y + j) * k->map_width
		+ (long)(k->pos_x + i)];
		if (check == '1' || (check == '2' && count < 5))
			return (1);
		i += i;
		j += j;
		count++;
	}
	return (0);
}

void	deal_forward(t_key *k)
{
	if (!collision_check_forward(k))
	{
		k->pos_x += k->dir_x / 2;
		k->pos_y += k->dir_y / 2;
	}
}
