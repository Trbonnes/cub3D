/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:28:26 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/10 16:05:57 by trbonnes         ###   ########.fr       */
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
