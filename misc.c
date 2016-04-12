#include "wolf3d.h"

void				print_map(void)
{
	int		y;
	int		x;

	y = 0;
	while (y <= singleton()->conf_height)
	{
		printf("%d\t", y+1);
		x = 0;
		while (x <= singleton()->conf_width)
		{
			printf("%d ",
			singleton()->tiles[y * singleton()->conf_width + x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

t_env				*singleton(void)
{
	static t_env	e;
	static int		inited = 0;

	if (inited == 0)
	{
		memset(&e, 0, sizeof(e));
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
	printf("error: %s", str);
	exit(0);
}
