/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:16:51 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/03 15:44:38 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int		main(int ac, char **av)
{
	t_key	param;

	if (ac == 2 || (ac == 3 && !ft_strncmp(av[2], "-save", 5)))
	{
		param = (t_key) { 0 };
		param.angle = -(M_PI / 2);
		parsing_init(open(av[1], O_RDONLY), &param);
		param.dir_x = cos(param.angle);
		param.dir_y = sin(param.angle);
		param.projection_distance = 0.866;
		param.plane_x = -1 * param.dir_y;
		param.plane_y = param.dir_x;
		param.mlx_ptr = mlx_init();
		if (ac < 3)
			param.win_ptr = mlx_new_window(param.mlx_ptr, param.window_width, param.window_heigth, "cub3D");
		else
			save_img();
		mlx_loop_hook(param.mlx_ptr, &loop_hook, &param);
		mlx_hook(param.win_ptr, KeyPress, KeyPressMask, deal_key, &param);
		mlx_hook(param.win_ptr, DestroyNotify, StructureNotifyMask, window_quit, &param);
		mlx_loop(param.mlx_ptr);
	}
	else
		write(2, "Parameters Error\nExiting\n", 25);
	exit(0);
	return (0);
}
