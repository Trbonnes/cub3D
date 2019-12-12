/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:28:26 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/12 10:17:03 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_lstdelone(t_sprite *current, t_sprite *previous, t_key *k)
{
	if (current == NULL)
		return ;
	if (previous != NULL)
		previous->next = current->next;
	else
		k->sprite_save = current->next;
	k->sprite_num--;
	free(current);
	current = NULL;
}

void	delete_loop(t_key *k, double i, double j)
{
	t_sprite	*delete;
	t_sprite	*previous;

	delete = k->sprite_save;
	previous = NULL;
	while (delete)
	{
		if ((long)delete->x == (long)(k->pos_x + i)
		&& (long)delete->y == (long)(k->pos_y + j))
		{
			ft_lstdelone(delete, previous, k);
			k->worldmap[(long)(k->pos_y + j) * k->map_width
			+ (long)(k->pos_x + i)] = '0';
			return ;
		}
		else
		{
			previous = delete;
			delete = delete->next;
		}
	}
}
