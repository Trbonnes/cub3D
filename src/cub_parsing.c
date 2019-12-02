/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 09:20:39 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/02 11:09:26 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int		parsing_init(char *file, t_key *param)
{
	int fd;
	char *line;
	char *save;
	t_parsing parse;

	parse = (t_parsing) { 0 }; 
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		save = line;
		if (line[0] == 'R')
		{
			line++;
			parse.window_width = ft_atoi(line);
			
		}
		if (line)
			free(line);
	}
	
	return (0);
}