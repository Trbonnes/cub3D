/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:46:43 by trbonnes          #+#    #+#             */
/*   Updated: 2019/11/28 09:50:57 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct		s_list
{
	int				fd;
	char			*left;
	int				size;
	struct s_list	*next;
}					t_list;

typedef struct		s_line
{
	char			**line;
	int				size;
}					t_line;

char				*ft_memjoin(char const *s1, int size1,
char const *s2, int size2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
t_list				*ft_lstnew(int fd);
t_list				*ft_lst_fd(int fd, t_list **lst);
void				ft_lst_remove(int fd, t_list **lst);
int					ft_eol(char *str, int size);
int					ft_leftover(t_list *lst, t_line *s_line);
int					ft_alloc(t_line *s_line, char *buffer, int cpysize);
int					ft_reading(int fd, char *buffer,
t_line *s_line, t_list *current);
int					get_next_line(int fd, char **line);

#endif
