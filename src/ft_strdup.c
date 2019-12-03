/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:26:31 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/03 13:49:04 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_strlen(const char *str)
{
	size_t size;

	size = 0;
	while (*str++)
		size++;
	return (size);
}

char			*ft_strdup(const char *s)
{
	char	*dst;
	int		i;

	i = 0;
	if (!(dst = malloc(sizeof(*dst) * (ft_strlen(s) + 1))))
		return (NULL);
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
