/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmohamed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 13:26:09 by nmohamed          #+#    #+#             */
/*   Updated: 2016/04/12 13:26:13 by nmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void				compute_camera(int x, t_env *env)
{
	env->cam_x = 2.0 * (double)x / (double)env->win_width - 1.0;
	env->ray_pos = new_vec2(env->pos.x, env->pos.y);
	env->ray_dir = new_vec2(env->dir.x + env->plane.x * env->cam_x,
	env->dir.y + env->plane.y * env->cam_x);
	env->hit = 0;
	env->map_pos = new_vec2(env->ray_pos.x, env->ray_pos.y);
	env->delta_dist = new_vec2(sqrt(1 + (env->ray_dir.y * env->ray_dir.y)
	/ (env->ray_dir.x * env->ray_dir.x)),
	sqrt(1 + (env->ray_dir.x * env->ray_dir.x)
	/ (env->ray_dir.y * env->ray_dir.y)));
}

void				compute_step(t_env *env)
{
	if (env->ray_dir.x < 0.0)
	{
		env->step.x = -1.0;
		env->side_dist.x = (env->ray_pos.x - env->map_pos.x)
		* env->delta_dist.x;
	}
	else
	{
		env->step.x = 1.0;
		env->side_dist.x = (env->map_pos.x + 1.0 - env->ray_pos.x)
		* env->delta_dist.x;
	}
	if (env->ray_dir.y < 0.0)
	{
		env->step.y = -1.0;
		env->side_dist.y = (env->ray_pos.y - env->map_pos.y)
		* env->delta_dist.y;
	}
	else
	{
		env->step.y = 1.0;
		env->side_dist.y = (env->map_pos.y + 1.0 - env->ray_pos.y)
		* env->delta_dist.y;
	}
}

void				compute_map_pos(t_env *env)
{
	if (env->side_dist.x < env->side_dist.y)
	{
		env->side_dist.x += env->delta_dist.x;
		env->map_pos.x += env->step.x;
		env->side = 0;
	}
	else
	{
		env->side_dist.y += env->delta_dist.y;
		env->map_pos.y += env->step.y;
		env->side = 1;
	}
}
