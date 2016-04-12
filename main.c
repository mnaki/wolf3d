#include "wolf3d.h"

void				update_size(int *arr, struct poubelle *st)
{
	arr[st->y * st->width + st->x] = st->num;
	st->sp = 0;
	if (st->width == 0)
		st->width = st->x;
	st->x = 0;
	st->num = 0;
}

int					*parse_file(char *filename)
{
	static int		arr[1000 * 1000] = { 0 };
	struct poubelle	st;

	memset(&st, 0, sizeof(st));
	if ((st.fd = open(filename, O_RDONLY)) <= 0)
		fatal("open error");
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
	if ((singleton()->win = SDL_CreateWindow("Nazi simulator 2014", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, singleton()->win_width, singleton()->win_height, SDL_WINDOW_OPENGL)) == NULL)
		fatal("window error");
	singleton()->ren = SDL_CreateRenderer(singleton()->win, -1, SDL_RENDERER_SOFTWARE);
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
	print_map();
	init_gl();
	return (0);
}
