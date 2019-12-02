/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 09:20:39 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/02 12:55:40 by trbonnes         ###   ########.fr       */
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

int		parsing_init(char *file, t_key *param)
{
	int			fd;
	char		*line;
	char 		*save;
	char		*tmp_map;
	t_parsing	parse;
	int			r;
	int			g;
	int			b;

	(void)param;
	parse = (t_parsing) { 0 }; 
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		save = line;
		if (line[0] == 'R' && line[1] == ' ')
		{
			while (!ft_isdigit(*line))
				line++;
			parse.window_width = ft_atoi(line);
			while (ft_isdigit(*line))
				line++;
			parse.window_heigth = ft_atoi(line);
		}
		else if (line[0] == 'N' && line[1] == 'O')
		{
			line += 2;
			while (*line == ' ')
				line++;
			parse.north_path = ft_strdup(line);
		}
		else if (line[0] == 'S' && line[1] == 'O')
		{
			line += 2;
			while (*line == ' ')
				line++;
			parse.south_path = ft_strdup(line);
		}
		else if (line[0] == 'W' && line[1] == 'E')
		{
			line += 2;
			while (*line == ' ')
				line++;
			parse.west_path = ft_strdup(line);
		}
		else if (line[0] == 'E' && line[1] == 'A')
		{
			line += 2;
			while (*line == ' ')
				line++;
			parse.east_path = ft_strdup(line);
		}
		else if (line[0] == 'S' && line[1] == ' ')
		{
			line++;
			while (*line == ' ')
				line++;
			parse.sprite_path = ft_strdup(line);
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
			parse.floor_color = (r << 16 | g << 8 | b);
			printf("%X\n", parse.floor_color);
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
			parse.cieling_color = (r << 16 | g << 8 | b);
			printf("%X\n", parse.cieling_color);
		}
		else if (line[0] == '1')
		{
			if (!parse.map)
				tmp_map = ft_strdup(line);
			else
				tmp_map = ft_strjoin(parse.map, line);
			if (parse.map)
				free(parse.map);
			parse.map = ft_strdup(tmp_map);
			free(tmp_map);
			tmp_map = ft_map_trim(parse.map);
			free(parse.map);
			parse.map = ft_strdup(tmp_map);
			free(tmp_map);
			printf("map: %s\n", parse.map);
		}
		if (save)
			free(save);
	}
	return (0);
}