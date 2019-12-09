/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 10:33:51 by trbonnes          #+#    #+#             */
/*   Updated: 2019/12/09 10:36:33 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void		write_int(t_saver *sv, unsigned int val)
{
	sv->buf[sv->index++] = val >> 0;
	sv->buf[sv->index++] = val >> 8;
	sv->buf[sv->index++] = val >> 16;
	sv->buf[sv->index++] = val >> 24;
}

static void		write_body(t_key *s, t_saver *sv)
{
	int x;
	int y;

	y = s->window_heigth - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < s->window_width)
		{
			sv->buf[sv->index++] = s->dda_img_data[y *
			s->window_width + x] >> 0;
			sv->buf[sv->index++] = s->dda_img_data[y *
			s->window_width + x] >> 8;
			sv->buf[sv->index++] = s->dda_img_data[y *
			s->window_width + x] >> 16;
			x++;
		}
		x = 0;
		while (x < (4 - (s->window_width * 3) % 4) % 4)
		{
			sv->buf[sv->index++] = 0;
			x++;
		}
		y--;
	}
}

static void		write_file_info(t_key *s, t_saver *sv)
{
	int i;

	sv->buf[sv->index++] = 40;
	sv->buf[sv->index++] = 0;
	sv->buf[sv->index++] = 0;
	sv->buf[sv->index++] = 0;
	write_int(sv, s->window_width);
	write_int(sv, s->window_heigth);
	sv->buf[sv->index++] = 1;
	sv->buf[sv->index++] = 0;
	sv->buf[sv->index++] = 24;
	sv->buf[sv->index++] = 0;
	i = 0;
	while (i < 24)
	{
		sv->buf[sv->index++] = 0;
		i++;
	}
}

static void		write_file_header(t_saver *sv)
{
	sv->buf[sv->index++] = 'B';
	sv->buf[sv->index++] = 'M';
	write_int(sv, sv->size);
	write_int(sv, 0x00000000);
	sv->buf[sv->index++] = 54;
	sv->buf[sv->index++] = 0;
	sv->buf[sv->index++] = 0;
	sv->buf[sv->index++] = 0;
}

int				save_first_frame(t_key *s, char *filename)
{
	int				fd;
	t_saver			sv;

	s->save_bool = 1;
	loop_hook(s);
	sv = (t_saver) { 0 };
	sv.size = 54 + 3 * s->window_width * s->window_heigth +
		((4 - (s->window_width * 3) % 4) % 4) * s->window_heigth;
	sv.buf = malloc(sv.size);
	if ((fd = open(filename, O_WRONLY | O_CREAT)) < 0)
		return (-1);
	write_file_header(&sv);
	write_file_info(s, &sv);
	write_body(s, &sv);
	write(fd, sv.buf, sv.size);
	close(fd);
	exit(0);
	return (0);
}
