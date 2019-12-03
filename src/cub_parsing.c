/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 09:20:39 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/03 15:48:13 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_map_trim(char *map)
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

void	set_position(int i, t_key *param)
{
	if (i == 0 || i == -1)
		return ;
	param->pos_x = (double)i + 0.5;
	param->pos_y = (double)param->map_heigth - 0.5;
}

int		finding_position(char *str, t_key *param)
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

void	resolution(char *line, t_key *param)
{
	while (!ft_isdigit(*line))
		line++;
	param->window_width = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	param->window_heigth = ft_atoi(line);
}

void	north_path(char *line, t_key *param)
{
	line += 2;
	while (*line == ' ')
		line++;
	param->north_path = ft_strdup(line);
}

void	south_path(char *line, t_key *param)
{
	line += 2;
	while (*line == ' ')
		line++;
	param->south_path = ft_strdup(line);
}

void	west_path(char *line, t_key *param)
{
	line += 2;
	while (*line == ' ')
		line++;
	param->west_path = ft_strdup(line);
}

void	east_path(char *line, t_key *param)
{
	line += 2;
	while (*line == ' ')
		line++;
	param->east_path = ft_strdup(line);
}

void	sprite_path(char *line, t_key *param)
{
	line++;
	while (*line == ' ')
		line++;
	param->sprite_path = ft_strdup(line);
}

void	floor_color(char *line, t_key *param)
{
	int			r;
	int			g;
	int			b;

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

void	cieling_color(char *line, t_key *param)
{
	int			r;
	int			g;
	int			b;

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

void	map_realloc(int width, char *line, t_key *param)
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

void	map_parsing(char *line, t_key *param, int fd)
{
	char		*save;
	int			width;
	int			i;

	param->map_heigth = 0;
	while (line[0] != '\0')
	{
		param->map_heigth++;
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
}

int		parsing_init(int fd, t_key *param)
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
	return (0);
}
