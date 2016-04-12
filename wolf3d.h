#ifndef WOLF_3D
# define WOLF_3D
# include <time.h>
# include <unistd.h>
# include <string.h>
# include <strings.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# ifdef __linux__
# else
#  ifdef _WIN32
#  else
#   include <SDL2/SDL.h>
#  endif
# endif

typedef struct		s_vec2
{
	double	x;
	double	y;
}					t_vec2;

typedef struct		s_env
{
	t_vec2			pos;
	t_vec2			dir;
	t_vec2			plane;
	int				win_width;
	int				win_height;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	int				*tiles;
	t_vec2			ray_pos;
	t_vec2			ray_dir;
	t_vec2			map_pos;
	t_vec2			side_dist;
	t_vec2			delta_dist;
	double			cam_x;
	double			perp_wall_dist;
	t_vec2			step;
	int				hit;
	int				side;
	int				conf_height;
	int				conf_width;
}					t_env;

struct				poubelle
{
	int				fd;
	int				num;
	char			c;
	int				x;
	int				y;
	int				width;
	int				sp;
	int				count;
};

void				print_map(void);
void				ver_line(int x, double draw_start, double drawend, int cl);
void				turn(double speed, t_env *env);
void				update_size(int *arr, struct poubelle *st);
int					*parse_file(char *filename);
void				init_conf(int ac, char **av);
void				init_gl(void);
void				forward(double speed, t_env *env);
void				keys(int key, int x, int y);
void				draw_wall_line(int x, t_env *env);
void				find_hit(int x, t_env *env);
void				display(void);
t_env				*singleton(void);
t_vec2				new_vec2(double x, double y);
void				fatal(char *str);
void				compute_camera(int x, t_env *env);
void				compute_step(t_env *env);
void				compute_map_pos(t_env *env);

#endif
