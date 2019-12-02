/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:46:23 by trbonnes          #+#    #+#             */
/*   Updated: 2019/11/28 09:51:17 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_memjoin(char const *s1, int size1, char const *s2, int size2)
{
	char	*str;
	char	*ptr;

	if (!(str = malloc(size1 + size2 + 1)))
		return (0);
	ptr = str;
	if (size1)
		while (size1--)
			*ptr++ = *s1++;
	if (size2)
		while (size2--)
			*ptr++ = *s2++;
	*ptr = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	if (!(dest = (malloc(len + 1))))
		return (0);
	dest[len] = 0;
	i = 0;
	while (i < len)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

t_list	*ft_lstnew(int fd)
{
	t_list *elem;

	if (!(elem = malloc(sizeof(t_list))))
		return (NULL);
	elem->fd = fd;
	elem->left = 0;
	elem->size = 0;
	elem->next = 0;
	return (elem);
}

void	ft_lst_remove(int fd, t_list **lst)
{
	t_list	*previous;
	t_list	*current;

	current = *lst;
	if (current->fd == fd)
	{
		current = current->next;
		free(*lst);
		*lst = current;
		return ;
	}
	previous = current;
	while (current)
	{
		if (current->fd == fd)
		{
			previous->next = current->next;
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

t_list	*ft_lst_fd(int fd, t_list **lst)
{
	t_list	*previous;
	t_list	*tmp;

	if (!*lst)
	{
		*lst = ft_lstnew(fd);
		return (*lst);
	}
	tmp = *lst;
	while (tmp)
		if (fd == tmp->fd)
			return (tmp);
		else
		{
			previous = tmp;
			tmp = tmp->next;
		}
	previous->next = ft_lstnew(fd);
	return (previous->next);
}
