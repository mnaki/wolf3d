/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmohamed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 13:26:26 by nmohamed          #+#    #+#             */
/*   Updated: 2016/04/12 13:26:26 by nmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void				ver_line(int x, double draw_start, double drawend, int cl)
{
	int				y;

	SDL_SetRenderDrawColor(singleton()->ren,
	50 + cl * 50, 50 + cl * 150, 50 + cl * 100, 255);
	y = draw_start;
	while (y < drawend)
	{
		SDL_RenderDrawPoint(singleton()->ren, x, y);
		y++;
	}
	SDL_SetRenderDrawColor(singleton()->ren, 150, 150, 150, 255);
	SDL_RenderDrawPoint(singleton()->ren, x, draw_start);
	SDL_RenderDrawPoint(singleton()->ren, x, drawend);
	SDL_RenderDrawPoint(singleton()->ren, x, draw_start + 1);
	SDL_RenderDrawPoint(singleton()->ren, x, drawend - 1);
}

void				draw_wall_line(int x, t_env *env)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;

	line_height = (int)(env->win_height / env->perp_wall_dist);
	draw_start = -line_height / 2.0 + env->win_height / 2.0;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2.0 + env->win_height / 2.0;
	if (draw_end >= env->win_height)
		draw_end = env->win_height - 1.0;
	color = env->tiles[(int)env->map_pos.y * env->conf_height
	+ (int)env->map_pos.x];
	if (env->side == 1)
		color = color * 10;
	ver_line(x, draw_start, draw_end, color);
}

void				find_hit(int x, t_env *env)
{
	while (env->hit == 0)
	{
		compute_map_pos(env);
		if (env->tiles[(int)env->map_pos.y * env->conf_height
			+ (int)env->map_pos.x] > 0)
			env->hit = 1;
		if (env->side == 0)
			env->perp_wall_dist = (env->map_pos.x - env->ray_pos.x
			+ (1.0 - env->step.x) / 2.0) / env->ray_dir.x;
		else
			env->perp_wall_dist = (env->map_pos.y - env->ray_pos.y
			+ (1.0 - env->step.y) / 2.0) / env->ray_dir.y;
		draw_wall_line(x, env);
	}
}

void				display(void)
{
	t_env	*env;
	int		x;

	env = singleton();
	SDL_RenderClear(env->ren);
	x = 0;
	while (x < env->win_width)
	{
		compute_camera(x, env);
		compute_step(env);
		find_hit(x, env);
		x++;
	}
	SDL_RenderPresent(env->ren);
}
