/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmohamed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 13:26:26 by nmohamed          #+#    #+#             */
/*   Updated: 2016/04/12 13:26:26 by nmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_env				*singleton(void)
{
	static t_env	e;
	static int		inited = 0;

	if (inited == 0)
	{
		ft_memset(&e, 0, sizeof(e));
		inited = 1;
	}
	return (&e);
}

t_vec2				new_vec2(double x, double y)
{
	t_vec2	v;

	v.x = x;
	v.y = y;
	return (v);
}

void				fatal(char *str)
{
	while (*str)
		write(1, str++, 1);
	exit(0);
}

void				ft_memset(void *b, int c, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		((unsigned char*)b)[i] = c;
		i++;
	}
}
