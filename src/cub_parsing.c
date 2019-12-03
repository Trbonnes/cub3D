/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 09:20:39 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/03 12:27:17 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	*ft_map_trim(char *map)
{
	char	*new_map;
	int 	spaces_count;
	int 	i;
	int		j;

	spaces_count = 0;
	i = 0;
	while (map[i++])
	{
		if (map[i] == ' ')
			spaces_count++;
	}
	if (!(new_map = malloc(sizeof(char) * (i - spaces_count +1))))
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
	printf("i: %d\n", i);
	param->pos_x = (double)i + 0.5;
	param->pos_y = (double)param->map_heigth - 0.5;
	printf("pos x: %lf\n", param->pos_x);
	printf("pos y: %lf\n", param->pos_y);
}

int		finding_position(char *str, t_key *param)
{
	int	i;

	i = -1;
	while (str[++i])
		if (ft_isalpha(str[i]))
		{
			if (str[i] == 'N')
			{
    			param->dir_x = cos(param->angle);
    			param->dir_y = sin(param->angle);
				str[i] = '0';
				return (i);
			}
			else if (str[i] == 'S')
			{
				param->dir_x = cos(param->angle);;
    			param->dir_y = -sin(param->angle);
				str[i] = '0';
				return (i);
			}
			else if (str[i] == 'E')
			{
				param->dir_x = cos(param->angle);
    			param->dir_y = sin(param->angle);
				str[i] = '0';
				return (i);
			}
			else if (str[i] == 'Z')
			{
				param->dir_x = -cos(param->angle);
    			param->dir_y = sin(param->angle);
				str[i] = '0';
				return (i);
			}
			else
				return (-1);
		}
	return (0);
}

int		parsing_init(char *file, t_key *param)
{
	int			fd;
	char		*line;
	char 		*save;
	char		*tmp_map;
	int			r;
	int			g;
	int			b;
	int			width;
	int			i;

	fd = open(file, O_RDONLY);
	line = 0;
	while (get_next_line(fd, &line))
	{
		save = line;
		if (line[0] == 'R' && line[1] == ' ')
		{
			while (!ft_isdigit(*line))
				line++;
			param->window_width = ft_atoi(line);
			while (ft_isdigit(*line))
				line++;
			param->window_heigth = ft_atoi(line);
		}
		else if (line[0] == 'N' && line[1] == 'O')
		{
			line += 2;
			while (*line == ' ')
				line++;
			param->north_path = ft_strdup(line);
		}
		else if (line[0] == 'S' && line[1] == 'O')
		{
			line += 2;
			while (*line == ' ')
				line++;
			param->south_path = ft_strdup(line);
		}
		else if (line[0] == 'W' && line[1] == 'E')
		{
			line += 2;
			while (*line == ' ')
				line++;
			param->west_path = ft_strdup(line);
		}
		else if (line[0] == 'E' && line[1] == 'A')
		{
			line += 2;
			while (*line == ' ')
				line++;
			param->east_path = ft_strdup(line);
		}
		else if (line[0] == 'S' && line[1] == ' ')
		{
			line++;
			while (*line == ' ')
				line++;
			param->sprite_path = ft_strdup(line);
		}
		else if (line[0] == 'F' && line[1] == ' ')
		{
			line++;
			while (!ft_isdigit(*line))
				line++;
			r = ft_atoi(line);
			printf("%d\n", r);
			while (ft_isdigit(*line))
				line++;
			while (!ft_isdigit(*line))
				line++;
			g = ft_atoi(line);
			printf("%d\n", g);
			while (ft_isdigit(*line))
				line++;
			while (!ft_isdigit(*line))
				line++;
			b = ft_atoi(line);
			printf("%d\n", b);
			param->floor_color = (r << 16 | g << 8 | b);
			printf("%X\n", param->floor_color);
		}
		else if (line[0] == 'C' && line[1] == ' ')
		{
			line++;
			while (!ft_isdigit(*line))
				line++;
			r = ft_atoi(line);
			printf("%d\n", r);
			while (ft_isdigit(*line))
				line++;
			while (!ft_isdigit(*line))
				line++;
			g = ft_atoi(line);
			printf("%d\n", g);
			while (ft_isdigit(*line))
				line++;
			while (!ft_isdigit(*line))
				line++;
			b = ft_atoi(line);
			printf("%d\n", b);
			param->cieling_color = (r << 16 | g << 8 | b);
			printf("%X\n", param->cieling_color);
		}
		if (line[0] == '1')
			break ;
		free(save);
	}
	param->map_heigth = 0;
	while (line[0] != '\0')
	{
		param->map_heigth++;
		save = ft_map_trim(line);
		free(line);
		line = ft_strdup(save);
		free(save);
		width = ft_strlen(line);
		i = finding_position(line, param);
		set_position(i, param);
		if ((param->map_width && width != param->map_width) || i == -1 || line[0] != '1' || line[width - 1] != '1')
		{
			write(2, "Error\nMap not well formated\nExiting\n", 36);
			free(line);
			exit(0);
		}
		else if (!param->map_width)
			param->map_width = width;
		if (!param->worldmap)
			tmp_map = ft_strdup(line);
		else
			tmp_map = ft_strjoin(param->worldmap, line);
		free(param->worldmap);
		param->worldmap = ft_strdup(tmp_map);
		free(tmp_map);
		free(line);
		get_next_line(fd, &line);
	}
	printf("map: %s\n", param->worldmap);
	free(line);
	return (0);
}