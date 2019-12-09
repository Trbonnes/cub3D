/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 12:33:15 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/09 12:33:55 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	pick_s_texture(t_key *k, t_dda *dda, t_img *img_data, int *pixel_index)
{
	dda->texture_y = (long)(pixel_index[1]
	* k->texture_so.height / dda->wall_height);
	img_data->img_data[pixel_index[0]] = k->texture_so.img_data[dda->texture_y
	* k->texture_so.width + dda->texture_x];
}

void	pick_n_texture(t_key *k, t_dda *dda, t_img *img_data, int *pixel_index)
{
	dda->texture_y = (long)(pixel_index[1]
	* k->texture_no.height / dda->wall_height);
	img_data->img_data[pixel_index[0]] = k->texture_no.img_data[dda->texture_y
	* k->texture_no.width + dda->texture_x];
}

void	pick_e_texture(t_key *k, t_dda *dda, t_img *img_data, int *pixel_index)
{
	dda->texture_y = (long)(pixel_index[1]
	* k->texture_ea.height / dda->wall_height);
	img_data->img_data[pixel_index[0]] = k->texture_ea.img_data[dda->texture_y
	* k->texture_ea.width + dda->texture_x];
}

void	pick_w_texture(t_key *k, t_dda *dda, t_img *img_data, int *pixel_index)
{
	dda->texture_y = (long)(pixel_index[1]
	* k->texture_we.height / dda->wall_height);
	img_data->img_data[pixel_index[0]] = k->texture_we.img_data[dda->texture_y
	* k->texture_we.width + dda->texture_x];
}

void	img_create(t_key *k, int i, t_img *img_data, t_dda *dda)
{
	int		pixel[3];
	int		j;

	pixel[2] = -1;
	pixel[0] = i;
	pixel[1] = 0;
	j = (int)((k->window_heigth - dda->wall_height) / 2);
	while (++pixel[2] < j)
		ceiling_loop(k, img_data, pixel);
	while (++pixel[2] <= j + dda->wall_height && pixel[2] < k->window_heigth)
	{
		if (dda->wall_side == 'S')
			pick_s_texture(k, dda, img_data, pixel);
		else if (dda->wall_side == 'N')
			pick_n_texture(k, dda, img_data, pixel);
		else if (dda->wall_side == 'E')
			pick_e_texture(k, dda, img_data, pixel);
		else
			pick_w_texture(k, dda, img_data, pixel);
		if (pixel[2] < k->window_heigth - 1)
			pixel[0] += k->window_width;
		pixel[1]++;
	}
	while (++pixel[2] <= (int)k->window_heigth)
		floor_loop(k, img_data, pixel, pixel[2]);
}
