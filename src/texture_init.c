/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:27:19 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/12 14:30:58 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	texture_init_north(t_key *param)
{
	void	*t_ptr;

	if ((t_ptr = mlx_xpm_file_to_image(param->mlx_ptr, param->north_path,
	&param->texture_no.width, &param->texture_no.height)) == NULL)
		texture_error();
	param->texture_no.img_data = (int *)mlx_get_data_addr(t_ptr,
	&param->texture_no.bits_per_pixel,
	&param->texture_no.size_line, &param->texture_no.endian);
}

void	texture_init_south(t_key *param)
{
	void	*t_ptr;

	if ((t_ptr = mlx_xpm_file_to_image(param->mlx_ptr, param->south_path,
	&param->texture_so.width, &param->texture_so.height)) == NULL)
		texture_error();
	param->texture_so.img_data = (int *)mlx_get_data_addr(t_ptr,
	&param->texture_so.bits_per_pixel,
	&param->texture_so.size_line, &param->texture_so.endian);
}

void	texture_init_east(t_key *param)
{
	void	*t_ptr;

	if ((t_ptr = mlx_xpm_file_to_image(
	param->mlx_ptr, param->east_path, &param->texture_ea.width,
	&param->texture_ea.height)) == NULL)
		texture_error();
	param->texture_ea.img_data = (int *)mlx_get_data_addr(t_ptr,
	&param->texture_ea.bits_per_pixel,
	&param->texture_ea.size_line, &param->texture_ea.endian);
}

void	texture_init_west(t_key *param)
{
	void	*t_ptr;

	if ((t_ptr = mlx_xpm_file_to_image(
	param->mlx_ptr, param->west_path, &param->texture_we.width,
	&param->texture_we.height)) == NULL)
		texture_error();
	param->texture_we.img_data = (int *)mlx_get_data_addr(t_ptr,
	&param->texture_we.bits_per_pixel,
	&param->texture_we.size_line, &param->texture_we.endian);
}

void	texture_init_sprite(t_key *param)
{
	void	*t_ptr;

	if ((t_ptr = mlx_xpm_file_to_image(param->mlx_ptr, param->sprite_path,
	&param->texture_sprite.width, &param->texture_sprite.height)) == NULL)
		texture_error();
	param->texture_sprite.img_data = (int *)mlx_get_data_addr(t_ptr,
	&param->texture_sprite.bits_per_pixel, &param->texture_sprite.size_line,
	&param->texture_sprite.endian);
}
