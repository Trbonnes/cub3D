/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_left.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 12:29:45 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/09 12:30:10 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		collision_check_left(t_key *k)
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
		check = k->worldmap[(long)(k->pos_y - i) * k->map_width
		+ (long)(k->pos_x - -1 * j)];
		if (check == '1' || (check == '2' && count < 5))
			return (1);
		i += i;
		j += j;
		count++;
	}
	return (0);
}

void	deal_left(t_key *k)
{
	if (!collision_check_left(k))
	{
		k->pos_x -= -1 * k->dir_y / 2;
		k->pos_y -= k->dir_x / 2;
	}
}
