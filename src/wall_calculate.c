/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_calculate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 13:10:59 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/09 13:11:12 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	wall_texture_s(t_key *k, t_dda *dda)
{
	dda->texture_x = (long)(dda->wall_x * (double)k->texture_so.width);
	if (dda->ray_dir_y > 0)
		dda->texture_x = k->texture_so.width - dda->texture_x - 1;
}

void	wall_texture_n(t_key *k, t_dda *dda)
{
	dda->texture_x = (long)(dda->wall_x * (double)k->texture_no.width);
	if (dda->ray_dir_y > 0)
		dda->texture_x = k->texture_no.width - dda->texture_x - 1;
}

void	wall_texture_e(t_key *k, t_dda *dda)
{
	dda->texture_x = (long)(dda->wall_x * (double)k->texture_ea.width);
	if (dda->ray_dir_x < 0)
		dda->texture_x = k->texture_ea.width - dda->texture_x - 1;
}

void	wall_texture_w(t_key *k, t_dda *dda)
{
	dda->texture_x = (long)(dda->wall_x * (double)k->texture_we.width);
	if (dda->ray_dir_x < 0)
		dda->texture_x = k->texture_we.width - dda->texture_x - 1;
}

void	wall_calculate(t_key *k, t_dda *dda)
{
	if (dda->wall_side == 'E' || dda->wall_side == 'W')
		wall_side_ew(k, dda);
	else
		wall_side_ns(k, dda);
	dda->wall_height = k->window_heigth / dda->wall_distance;
	if (dda->wall_side == 'S')
		wall_texture_s(k, dda);
	else if (dda->wall_side == 'N')
		wall_texture_n(k, dda);
	else if (dda->wall_side == 'E')
		wall_texture_e(k, dda);
	else
		wall_texture_w(k, dda);
}
