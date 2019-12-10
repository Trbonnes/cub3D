/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 12:31:16 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/10 18:02:56 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	deal_attack(t_key *k)
{
	double		i;
	double		j;
	int			count;
	t_sprite 	*delete;
	t_sprite 	*previous;
	char		check;

	delete = k->sprite_save;
	previous = NULL;
	hook_attack(k);
	k->player.protected = 1;
	i = 0;
	j = 0;
	count = 0;
	check = 0;
	while (count <= 3)
	{
		check = k->worldmap[(long)(k->pos_y + j) * k->map_width
		+ (long)(k->pos_x + i)];
		if (check == '2' || check == '1')
			break ;
		i += k->dir_x / 5;
		j += k->dir_y / 5;
		count++;
	}
	if (check == '2')
	{
		while (delete)
		{
			if ((long)delete->x == (long)(k->pos_x + i) && (long)delete->y == (long)(k->pos_y + j))
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
}

int		window_quit(t_key *k)
{
	mlx_destroy_window(k->mlx_ptr, k->win_ptr);
	write(1, "ESC\nExiting\n", 12);
	exit(0);
	return (0);
}

int		deal_key(int key, t_key *k)
{
	if (k->player.hp <= 0)
		return (0);
	if (key == 53)
		window_quit(k);
	if (key == 13)
		deal_forward(k);
	if (key == 1)
		deal_backward(k);
	if (key == 0)
		deal_left(k);
	if (key == 2)
		deal_right(k);
	if (key == 124)
		k->angle += ROT;
	if (key == 123)
		k->angle -= ROT;
	if (key == 14)
		deal_attack(k);
	k->dir_x = cos(k->angle);
	k->dir_y = sin(k->angle);
	k->plane_x = -1 * k->dir_y;
	k->plane_y = k->dir_x;
	return (0);
}


int		release_key(int key, t_key *k)
{
	if (k->player.hp <= 0)
		return (0);
	if (key == 14)
		k->player.protected = 0;
	return (0);
}