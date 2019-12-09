/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_side.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 13:12:03 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/09 13:12:16 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	wall_side_ew(t_key *k, t_dda *dda)
{
	dda->wall_distance = (dda->map_x - k->pos_x
	+ (1 - dda->step_x) / 2) / dda->ray_dir_x;
	dda->wall_x = k->pos_y + dda->wall_distance * dda->ray_dir_y;
	dda->wall_x -= (long)dda->wall_x;
}

void	wall_side_ns(t_key *k, t_dda *dda)
{
	dda->wall_distance = (dda->map_y - k->pos_y
	+ (1 - dda->step_y) / 2) / dda->ray_dir_y;
	dda->wall_x = k->pos_x + dda->wall_distance * dda->ray_dir_x;
	dda->wall_x -= (long)dda->wall_x;
}
