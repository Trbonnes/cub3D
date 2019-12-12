/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 13:09:32 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/12 10:25:02 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ceiling_loop(t_key *k, t_img *img_data,
int *pixel_index, int pixel_number)
{
	t_color c;

	c.v = k->cieling_color;
	if ((c.color.r - pixel_number / (k->window_heigth / 200)) > 0)
		c.color.r = c.color.r - pixel_number / (k->window_heigth / 200);
	if ((c.color.g - pixel_number / (k->window_heigth / 200)) > 0)
		c.color.g = c.color.g - pixel_number / (k->window_heigth / 200);
	if ((c.color.b - pixel_number / (k->window_heigth / 200)) > 0)
		c.color.b = c.color.b - pixel_number / (k->window_heigth / 200);
	img_data->img_data[pixel_index[0]] = c.v;
	pixel_index[0] += k->window_width;
}

void	floor_loop(t_key *k, t_img *img_data,
int *pixel_index, int pixel_number)
{
	t_color c;

	c.v = k->floor_color;
	if ((c.color.r - (k->window_heigth - pixel_number) /
	(k->window_heigth / 200)) > 0)
		c.color.r = c.color.r - (k->window_heigth - pixel_number) /
		(k->window_heigth / 200);
	if ((c.color.g - (k->window_heigth - pixel_number) /
	(k->window_heigth / 200)) > 0)
		c.color.g = c.color.g - (k->window_heigth - pixel_number) /
		(k->window_heigth / 200);
	if ((c.color.b - (k->window_heigth - pixel_number) /
	(k->window_heigth / 200)) > 0)
		c.color.b = c.color.b - (k->window_heigth - pixel_number) /
		(k->window_heigth / 200);
	img_data->img_data[pixel_index[0]] = c.v;
	if (pixel_number < (int)k->window_heigth - 1)
		pixel_index[0] += k->window_width;
}

void	loop_call_up(t_key *k, t_img *img_data, int *pixel, int j)
{
	while (++pixel[2] < j)
		ceiling_loop(k, img_data, pixel, pixel[2]);
}

void	loop_call_down(t_key *k, t_img *img_data, int *pixel)
{
	while (++pixel[2] <= (int)k->window_heigth)
		floor_loop(k, img_data, pixel, pixel[2]);
}
