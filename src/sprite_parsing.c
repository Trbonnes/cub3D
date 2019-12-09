/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 12:15:10 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/09 12:19:31 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_sprite	*ft_new_sprite(int x, int y)
{
	t_sprite	*new;

	if ((new = malloc(sizeof(t_sprite))) == NULL)
		return (NULL);
	if (new)
	{
		new->x = x + 0.5;
		new->y = y + 0.5;
		new->next = NULL;
	}
	return (new);
}

int			sprite_parsing(t_key *param)
{
	int x;
	int y;

	x = 0;
	y = 0;
	param->sprite = ft_new_sprite(0, 0);
	param->sprite_save = param->sprite;
	while (y < param->map_heigth)
	{
		if (param->worldmap[y * param->map_width + x] == '2')
		{
			param->sprite->next = ft_new_sprite(x, y);
			param->sprite = param->sprite->next;
			param->sprite_num++;
		}
		if (x < param->map_width - 1)
			x++;
		else
		{
			x = 0;
			y++;
		}
	}
	parsing_error(param);
	return (0);
}
