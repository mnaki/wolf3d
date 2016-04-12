/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmohamed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 13:26:27 by nmohamed          #+#    #+#             */
/*   Updated: 2016/04/12 13:26:27 by nmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void				update_size(int *arr, struct s_poubelle *st)
{
	arr[st->y * st->width + st->x] = st->num;
	st->sp = 0;
	if (st->width == 0)
		st->width = st->x;
	st->x = 0;
	st->num = 0;
}

void				preparse(struct s_poubelle *st, char *filename)
{
	ft_memset(st, 0, sizeof(*st));
	if ((st->fd = open(filename, O_RDONLY)) <= 0)
		fatal("open error");
}

int					*parse_file(char *filename)
{
	static int			arr[1000 * 1000] = { 0 };
	struct s_poubelle	st;

	preparse(&st, filename);
	while ((st.count = read(st.fd, &st.c, 1)) > 0)
	{
		if ((st.count <= 0) || ((st.c == '\n') && !st.sp))
		{
			update_size(arr, &st);
			if (st.count == 0)
				break ;
			st.y++;
		}
		else if (st.c >= '0' && st.c <= '9' && (st.sp = 0) == 0)
			st.num = st.num * 10 + st.c - '0';
		else if ((st.c == ' ' || st.c == '\t') && !st.sp && (st.sp = 1) == 1)
		{
			arr[st.y * st.width + st.x++] = st.num;
			st.num = 0;
		}
	}
	singleton()->conf_width = st.width;
	singleton()->conf_height = st.y;
	return (arr);
}
