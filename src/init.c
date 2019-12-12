/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 10:18:00 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/12 14:27:31 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	texture_error(void)
{
	write(2, "Error\nInexistant texture\nExiting\n", 33);
	exit(0);
}

void	texture_add_init(t_key *param)
{
	param->texture_saber.img_data = (int *)mlx_get_data_addr(
	mlx_xpm_file_to_image(
	param->mlx_ptr, "./texture/saber.xpm", &param->texture_saber.width,
	&param->texture_saber.height), &param->texture_saber.bits_per_pixel,
	&param->texture_saber.size_line, &param->texture_saber.endian);
	param->texture_saber_a.img_data = (int *)mlx_get_data_addr(
	mlx_xpm_file_to_image(
	param->mlx_ptr, "./texture/h_saber.xpm", &param->texture_saber_a.width,
	&param->texture_saber_a.height), &param->texture_saber_a.bits_per_pixel,
	&param->texture_saber_a.size_line, &param->texture_saber_a.endian);
	param->game_over.img_data = (int *)mlx_get_data_addr(
	mlx_xpm_file_to_image(
	param->mlx_ptr, "./texture/game_over.xpm", &param->game_over.width,
	&param->game_over.height), &param->game_over.bits_per_pixel,
	&param->game_over.size_line, &param->game_over.endian);
	param->health_bar.img_data = (int *)mlx_get_data_addr(
	mlx_xpm_file_to_image(
	param->mlx_ptr, "./texture/health_bar.xpm", &param->health_bar.width,
	&param->health_bar.height), &param->health_bar.bits_per_pixel,
	&param->health_bar.size_line, &param->health_bar.endian);
}

void	texture_init(t_key *param)
{
	texture_init_north(param);
	texture_init_south(param);
	texture_init_east(param);
	texture_init_west(param);
	texture_init_sprite(param);
	texture_add_init(param);
}

void	value_init(t_key *param)
{
	param->dir_x = cos(param->angle);
	param->dir_y = sin(param->angle);
	param->projection_distance = 0.866;
	param->plane_x = -1 * param->dir_y;
	param->plane_y = param->dir_x;
	param->mlx_ptr = mlx_init();
	param->player = (t_player) {.hp = 50000, .protected = 0, .shot = 0};
}

int		init_error(int ac, char **av)
{
	int fd;
	int	i;

	i = 0;
	while (av[1][i])
		i++;
	if (i < 4)
		return (-1);
	if (av[1][--i] != 'b')
		return (-1);
	if (av[1][--i] != 'u')
		return (-1);
	if (av[1][--i] != 'c')
		return (-1);
	if (av[1][--i] != '.')
		return (-1);
	fd = open(av[1], O_RDONLY);
	if ((ac == 2 || (ac == 3 && !ft_strncmp(av[2], "-save", 5))) && fd != -1)
		return (fd);
	else
		return (-1);
}
