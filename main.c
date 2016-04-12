/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmohamed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 13:26:26 by nmohamed          #+#    #+#             */
/*   Updated: 2016/04/12 13:26:26 by nmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void				init_conf(int ac, char **av)
{
	(void)ac;
	singleton()->tiles = parse_file(av[1]);
	singleton()->win_width = 1280;
	singleton()->win_height = 800;
	singleton()->pos = new_vec2(2, 2);
	singleton()->dir = new_vec2(-1, 0);
	singleton()->plane = new_vec2(0, 0.9);
}

void				init_gl(void)
{
	SDL_Event		event;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		fatal("sdl error");
	if ((singleton()->win = SDL_CreateWindow("Nazi simulator 2014",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	singleton()->win_width, singleton()->win_height,
	SDL_WINDOW_OPENGL)) == NULL)
		fatal("window error");
	singleton()->ren = SDL_CreateRenderer(singleton()->win,
	-1, SDL_RENDERER_SOFTWARE);
	while (1)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				exit(0);
			if (event.type == SDL_KEYDOWN)
				keys(event.key.keysym.scancode, 0, 0);
		}
		display();
	}
}

int					main(int ac, char **av)
{
	if (ac < 2)
		fatal("provide one file");
	init_conf(ac, av);
	init_gl();
	return (0);
}
