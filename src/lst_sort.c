/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:18:49 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/06 15:14:59 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		cmp(t_sprite *current, t_sprite *next, t_key *param)
{
	double totcurrent;
	double totnext;
	totcurrent = powf(current->x - param->pos_x, 2)
	+ powf(current->y - param->pos_y, 2);
	totnext = powf(next->x - param->pos_x, 2)
	+ powf(next->y - param->pos_y, 2);
	if (totcurrent < totnext)
		return (1);
	else
		return (0);
}
void	swap_data(t_sprite *current)
{
	double		tmpx;
	double		tmpy;
	
	tmpx = current->x;
	tmpy = current->y;
	current->x = current->next->x;
	current->y = current->next->y;
	current->next->x = tmpx;
	current->next->y = tmpy;
}

void	ft_lst_sort(t_sprite *begin_list, t_key *param)
{
	t_sprite	*count;
	t_sprite	*current;
	
	if (!begin_list || !begin_list)
		return ;
	count = begin_list;
	while (count)
	{
		current = begin_list;
		while (current->next)
		{
			if (cmp(current, current->next, param) > 0)
			{
				swap_data(current);
				break ;
			}
			else
				current = current->next;
		}
		count = count->next;
	}
}