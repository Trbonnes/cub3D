/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 12:17:27 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/12 11:25:22 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char		*ft_map_trim(char *map)
{
	char	*new_map;
	int		spaces_count;
	int		i;
	int		j;

	spaces_count = 0;
	i = 0;
	while (map[i++])
	{
		if (map[i] == ' ')
			spaces_count++;
	}
	if (!(new_map = malloc(sizeof(char) * (i - spaces_count + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (map[i])
	{
		if (map[i] != ' ')
			new_map[j++] = map[i];
		i++;
	}
	new_map[j] = '\0';
	return (new_map);
}

void		map_realloc(int width, char *line, t_key *param)
{
	char		*tmp_map;

	param->map_width = width;
	if (!param->worldmap)
		tmp_map = ft_strdup(line);
	else
		tmp_map = ft_strjoin(param->worldmap, line);
	free(param->worldmap);
	param->worldmap = ft_strdup(tmp_map);
	free(tmp_map);
}

void		map_parsing(char *line, t_key *param, int fd)
{
	char		*save;
	int			width;
	int			i;

	param->map_heigth = 0;
	while (line[0] != '\0' && ++param->map_heigth)
	{
		save = ft_map_trim(line);
		free(line);
		line = ft_strdup(save);
		free(save);
		width = ft_strlen(line);
		set_position((i = finding_position(line, param)), param);
		if ((param->map_width && width != param->map_width)
		|| i == -1 || line[0] != '1' || line[width - 1] != '1')
		{
			write(2, "Error\nMap not well formated\nExiting\n", 36);
			free(line);
			exit(0);
		}
		map_realloc(width, line, param);
		free(line);
		get_next_line(fd, &line);
	}
	free(line);
}
