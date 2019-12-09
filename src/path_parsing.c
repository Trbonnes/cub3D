/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 12:16:28 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/09 12:17:00 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		north_path(char *line, t_key *param)
{
	if (param->north_path != 0)
	{
		write(2, "Error\nFile not well formated\nExiting\n", 36);
		free(line);
		exit(0);
	}
	line += 2;
	while (*line == ' ')
		line++;
	param->north_path = ft_strdup(line);
}

void		south_path(char *line, t_key *param)
{
	if (param->south_path != 0)
	{
		write(2, "Error\nFile not well formated\nExiting\n", 36);
		free(line);
		exit(0);
	}
	line += 2;
	while (*line == ' ')
		line++;
	param->south_path = ft_strdup(line);
}

void		west_path(char *line, t_key *param)
{
	if (param->west_path != 0)
	{
		write(2, "Error\nFile not well formated\nExiting\n", 36);
		free(line);
		exit(0);
	}
	line += 2;
	while (*line == ' ')
		line++;
	param->west_path = ft_strdup(line);
}

void		east_path(char *line, t_key *param)
{
	if (param->east_path != 0)
	{
		write(2, "Error\nFile not well formated\nExiting\n", 36);
		free(line);
		exit(0);
	}
	line += 2;
	while (*line == ' ')
		line++;
	param->east_path = ft_strdup(line);
}

void		sprite_path(char *line, t_key *param)
{
	if (param->sprite_path != 0)
	{
		write(2, "Error\nFile not well formated\nExiting\n", 36);
		free(line);
		exit(0);
	}
	line++;
	while (*line == ' ')
		line++;
	param->sprite_path = ft_strdup(line);
}
