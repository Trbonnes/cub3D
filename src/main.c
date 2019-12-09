/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:16:51 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/09 10:31:45 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	parameters_error(void)
{
	write(2, "Parameters Error\nExiting\n", 25);
	exit(0);
}

void	texture_init(t_key *param)
{
	param->texture_no.img_data = (int *)mlx_get_data_addr(mlx_xpm_file_to_image(
	param->mlx_ptr, param->north_path, &param->texture_no.width,
	&param->texture_no.height), &param->texture_no.bits_per_pixel,
	&param->texture_no.size_line, &param->texture_no.endian);
	param->texture_so.img_data = (int *)mlx_get_data_addr(mlx_xpm_file_to_image(
	param->mlx_ptr, param->south_path, &param->texture_so.width,
	&param->texture_so.height), &param->texture_so.bits_per_pixel,
	&param->texture_so.size_line, &param->texture_so.endian);
	param->texture_ea.img_data = (int *)mlx_get_data_addr(mlx_xpm_file_to_image(
	param->mlx_ptr, param->east_path, &param->texture_ea.width,
	&param->texture_ea.height), &param->texture_ea.bits_per_pixel,
	&param->texture_ea.size_line, &param->texture_ea.endian);
	param->texture_we.img_data = (int *)mlx_get_data_addr(mlx_xpm_file_to_image(
	param->mlx_ptr, param->west_path, &param->texture_we.width,
	&param->texture_we.height), &param->texture_we.bits_per_pixel,
	&param->texture_we.size_line, &param->texture_we.endian);
	param->texture_sprite.img_data = (int *)mlx_get_data_addr(
	mlx_xpm_file_to_image(param->mlx_ptr, param->sprite_path,
	&param->texture_sprite.width, &param->texture_sprite.height),
	&param->texture_sprite.bits_per_pixel, &param->texture_sprite.size_line,
	&param->texture_sprite.endian);
}

void	value_init(t_key *param)
{
	param->dir_x = cos(param->angle);
	param->dir_y = sin(param->angle);
	param->projection_distance = 0.866;
	param->plane_x = -1 * param->dir_y;
	param->plane_y = param->dir_x;
	param->mlx_ptr = mlx_init();
}

int		init_error(int ac, char **av)
{
	int fd;

	fd = open(av[1], O_RDONLY);
	if ((ac == 2 || (ac == 3 && !ft_strncmp(av[2], "-save", 5))) && fd != -1)
		return (fd);
	else
		return (-1);
}

int		main(int ac, char **av)
{
	int		fd;
	t_key	param;

	if ((fd = init_error(ac, av)) != -1)
	{
		param = (t_key) { 0 };
		param.angle = -(M_PI / 2);
		parsing_init(fd, &param);
		value_init(&param);
		texture_init(&param);
		if (ac == 3)
			save_first_frame(&param, "save.bmp");
		param.win_ptr = mlx_new_window(param.mlx_ptr,
		param.window_width, param.window_heigth, "cub3D");
		mlx_loop_hook(param.mlx_ptr, &loop_hook, &param);
		mlx_hook(param.win_ptr, KeyPress, KeyPressMask, deal_key, &param);
		mlx_hook(param.win_ptr, DestroyNotify,
		StructureNotifyMask, window_quit, &param);
		mlx_loop(param.mlx_ptr);
	}
	else
		parameters_error();
	exit(0);
	return (0);
}
