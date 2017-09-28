#include "fractol.h"
#include "libft.h"

int         set_num(char    *set_name)
{
	static  char    *all[2] = {"julia", "mondel"};
	int             i;

	i = 0;
	while (i < 2)
	{
		if (ft_strcmp(set_name, all[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int		main(int argc, char **argv)
{
	int num;

	if (argc != 2)
		ft_putendl("using: fractol name");
	else
	{
		num = set_num(argv[1]);
		if (num == -1)
			ft_putendl("using: fractol [julia | mondel]");
		else
			fractol(num);
	}
}
