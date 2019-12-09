/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 13:09:32 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/09 13:09:49 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ceiling_loop(t_key *k, t_img *img_data, int *pixel_index)
{
	img_data->img_data[pixel_index[0]] = k->cieling_color;
	pixel_index[0] += k->window_width;
}

void	floor_loop(t_key *k, t_img *img_data,
int *pixel_index, int pixel_number)
{
	img_data->img_data[pixel_index[0]] = k->floor_color;
	if (pixel_number < (int)k->window_heigth - 1)
		pixel_index[0] += k->window_width;
}
