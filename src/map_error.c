/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 10:54:36 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/12 10:58:10 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		map_error(t_key *param)
{
	write(2, "Error\nMap not well formated\nExiting\n", 36);
	free(param->worldmap);
	exit(0);
}

t_key		*map_border_check(t_key *param)
{
	int i;
	int j;

	i = 0;
	while (i < param->map_width)
	{
		if (param->worldmap[i] != '1')
			map_error(param);
		i++;
	}
	while (param->worldmap[i + 1])
	{
		if (param->worldmap[i] < '0' || param->worldmap[i] > '2')
			map_error(param);
		i++;
	}
	j = 0;
	while (j < param->map_width)
	{
		if (param->worldmap[i] != '1')
			map_error(param);
		i--;
		j++;
	}
	return (param);
}
