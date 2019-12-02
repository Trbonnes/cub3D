/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:44:38 by trbonnes          #+#    #+#             */
/*   Updated: 2019/11/28 10:45:26 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_eol(char *str, int size)
{
	int i;

	if (!str)
		return (-1);
	i = -1;
	while (++i < size)
		if (str[i] == '\n')
			return (i);
	return (-1);
}

int		ft_leftover(t_list *lst, t_line *s_line)
{
	char	*tmp;
	int		eof;

	if (lst->left == 0)
		return (0);
	if ((eof = ft_eol(lst->left, lst->size)) != -1)
	{
		if (!(*(s_line->line) = ft_substr(lst->left, 0, eof)))
			return (-1);
		tmp = lst->left;
		if (lst->size == eof + 1)
			lst->left = 0;
		else if (!(lst->left = ft_substr(lst->left, eof + 1, lst->size - eof)))
			return (-1);
		free(tmp);
		lst->size -= eof + 1;
		return (1);
	}
	else
	{
		*(s_line->line) = lst->left;
		lst->left = 0;
		s_line->size = lst->size;
		return (lst->size = 0);
	}
}

int		ft_alloc(t_line *s_line, char *buffer, int cpysize)
{
	char *tmp;

	tmp = *(s_line->line);
	if (!(*(s_line->line) =
	ft_memjoin(*(s_line->line), s_line->size, buffer, cpysize)))
		return (-1);
	s_line->size += cpysize;
	free(tmp);
	return (0);
}

int		ft_reading(int fd, char *buffer, t_line *s_line, t_list *current)
{
	int		rd;
	int		eol;
	int		i;

	while ((rd = read(fd, buffer, BUFFER_SIZE)) > 0
	&& (eol = ft_eol(buffer, rd)) == -1)
	{
		if (ft_alloc(s_line, buffer, rd))
			return (-1);
		i = -1;
		while (++i < BUFFER_SIZE)
			buffer[i] = 0;
	}
	if (rd == -1)
		return (-1);
	if (rd == 0)
		return (0);
	if (ft_alloc(s_line, buffer, eol))
		return (-1);
	if (eol + 1 == rd)
		current->left = 0;
	else if (!(current->left = ft_substr(buffer, eol + 1, rd - eol - 1)))
		return (-1);
	current->size = rd - eol - 1;
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static t_list	*lst;
	t_list			*current;
	t_line			s_line;
	char			*buffer;
	int				i;

	if (BUFFER_SIZE <= 0 || !line || fd < 0 || !(current = ft_lst_fd(fd, &lst)))
		return (-1);
	*line = 0;
	s_line = (t_line) {.size = 0, .line = line};
	if ((i = ft_leftover(current, &s_line)) == 1)
		return (1);
	if (i == -1 || !(buffer = malloc(sizeof(char) * BUFFER_SIZE)))
		return (-1);
	if ((i = ft_reading(fd, buffer, &s_line, current)) == 0 && !*line)
	{
		if (!(*line = malloc(1)))
			return (-1);
		*line[0] = '\0';
	}
	if (i == 0)
		ft_lst_remove(fd, &lst);
	free(buffer);
	return (i);
}
