#include "wolf3d.h"

void				turn(double speed, t_env *env)
{
	t_vec2	oldplane;
	t_vec2	olddir;

	olddir.x = env->dir.x;
	oldplane.x = env->plane.x;
	env->dir.x = env->dir.x * cos(speed) - env->dir.y * sin(speed);
	env->dir.y = olddir.x * sin(speed) + env->dir.y * cos(speed);
	env->plane.x = env->plane.x * cos(speed) - env->plane.y * sin(speed);
	env->plane.y = oldplane.x * sin(speed) + env->plane.y * cos(speed);
}

void				forward(double speed, t_env *env)
{
	if (env->tiles[(int)(env->pos.y) * env->conf_height
		+ (int)(env->pos.x + env->dir.x * speed)] == 0)
		env->pos.x += env->dir.x * speed;
	if (env->tiles[(int)(env->pos.y + env->dir.y * speed)
		* env->conf_height + (int)(env->pos.x)] == 0)
		env->pos.y += env->dir.y * speed;
}

void				keys(int key, int x, int y)
{
	if (key == SDL_SCANCODE_LEFT)
		turn((sin(0.2)), singleton());
	if (key == SDL_SCANCODE_RIGHT)
		turn(-(sin(0.2)), singleton());
	if (key == SDL_SCANCODE_UP)
		forward(0.5, singleton());
	if (key == SDL_SCANCODE_DOWN)
		forward(-0.5, singleton());
	if (key == SDL_SCANCODE_ESCAPE)
		exit(0);
	(void)x;
	(void)y;
}
