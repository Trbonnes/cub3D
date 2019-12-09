/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_res_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 12:18:40 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/09 12:19:07 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		resolution(char *line, t_key *param)
{
	if (param->window_heigth != 0 || param->window_width != 0)
	{
		write(2, "Error\nFile not well formated\nExiting\n", 36);
		free(line);
		exit(0);
	}
	while (!ft_isdigit(*line))
		line++;
	if ((param->window_width = ft_atoi(line)) > 2560)
		param->window_width = 2560;
	else if (param->window_width < 50)
		param->window_width = 50;
	while (ft_isdigit(*line))
		line++;
	if ((param->window_heigth = ft_atoi(line)) > 1440)
		param->window_heigth = 1440;
	else if (param->window_heigth < 50)
		param->window_heigth = 50;
}

void		floor_color(char *line, t_key *param)
{
	int			r;
	int			g;
	int			b;

	if (param->floor_color != 0)
	{
		write(2, "Error\nFile not well formated\nExiting\n", 36);
		free(line);
		exit(0);
	}
	line++;
	while (!ft_isdigit(*line))
		line++;
	r = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	while (!ft_isdigit(*line))
		line++;
	g = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	while (!ft_isdigit(*line))
		line++;
	b = ft_atoi(line);
	param->floor_color = (r << 16 | g << 8 | b);
}

void		cieling_color(char *line, t_key *param)
{
	int			r;
	int			g;
	int			b;

	if (param->cieling_color != 0)
	{
		write(2, "Error\nFile not well formated\nExiting\n", 36);
		free(line);
		exit(0);
	}
	line++;
	while (!ft_isdigit(*line))
		line++;
	r = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	while (!ft_isdigit(*line))
		line++;
	g = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	while (!ft_isdigit(*line))
		line++;
	b = ft_atoi(line);
	param->cieling_color = (r << 16 | g << 8 | b);
}
