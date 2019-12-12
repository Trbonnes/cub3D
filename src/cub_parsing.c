/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 09:20:39 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/12 11:14:23 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		parsing_error(t_key *param)
{
	int error_bool;

	error_bool = 0;
	if (param->window_width == 0 || param->window_heigth == 0)
		error_bool = 1;
	else if (param->north_path == 0)
		error_bool = 1;
	else if (param->south_path == 0)
		error_bool = 1;
	else if (param->east_path == 0)
		error_bool = 1;
	else if (param->west_path == 0)
		error_bool = 1;
	else if (param->sprite_path == 0)
		error_bool = 1;
	else if (param->floor_color < 0)
		error_bool = 1;
	else if (param->cieling_color < 0)
		error_bool = 1;
	if (error_bool)
	{
		write(2, "Error\nFile not well formated\nExiting\n", 37);
		exit(0);
	}
}

void		set_position(int i, t_key *param)
{
	if (i == 0 || i == -1)
		return ;
	param->pos_x = (double)i + 0.5;
	param->pos_y = (double)param->map_heigth - 0.5;
}

int			finding_position(char *str, t_key *param)
{
	int	i;

	i = -1;
	while (str[++i])
		if (ft_isalpha(str[i]))
		{
			if (str[i] == 'N' && param->pos_x == 0)
				;
			else if (str[i] == 'S' && param->pos_x == 0)
				param->angle = -1 * param->angle;
			else if (str[i] == 'E' && param->pos_x == 0)
				param->angle = param->angle - param->angle;
			else if (str[i] == 'W' && param->pos_x == 0)
				param->angle = param->angle + param->angle;
			else
				return (-1);
			str[i] = '0';
			return (i);
		}
	return (0);
}

int			parsing_init(int fd, t_key *param)
{
	char		*line;

	while (get_next_line(fd, &line) && line[0] != '1')
	{
		if (line[0] == 'R' && line[1] == ' ')
			resolution(line, param);
		else if (line[0] == 'N' && line[1] == 'O')
			north_path(line, param);
		else if (line[0] == 'S' && line[1] == 'O')
			south_path(line, param);
		else if (line[0] == 'W' && line[1] == 'E')
			west_path(line, param);
		else if (line[0] == 'E' && line[1] == 'A')
			east_path(line, param);
		else if (line[0] == 'S' && line[1] == ' ')
			sprite_path(line, param);
		else if (line[0] == 'F' && line[1] == ' ')
			floor_color(line, param);
		else if (line[0] == 'C' && line[1] == ' ')
			cieling_color(line, param);
		free(line);
	}
	map_parsing(line, param, fd);
	close(fd);
	return (sprite_parsing(map_border_check(param)));
}
