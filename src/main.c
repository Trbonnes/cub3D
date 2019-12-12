/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:16:51 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/12 10:18:18 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	parameters_error(void)
{
	write(2, "Parameters Error\nExiting\n", 25);
	exit(0);
}

int		main(int ac, char **av)
{
	int		fd;
	t_key	param;

	if (ac > 1 && (fd = init_error(ac, av)) != -1)
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
		mlx_hook(param.win_ptr, KEYPRESS, KEYPRESSMASK, deal_key, &param);
		mlx_hook(param.win_ptr, DESTROYNOTIFY,
		STRUCTURENOTIFYMASK, window_quit, &param);
		mlx_hook(param.win_ptr, KEYRELEASE,
		KEYRELEASEMASK, release_key, &param);
		mlx_loop(param.mlx_ptr);
	}
	else
		parameters_error();
	return (0);
}
