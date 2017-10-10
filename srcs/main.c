/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 18:51:27 by ykolomie          #+#    #+#             */
/*   Updated: 2017/10/01 18:51:43 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

static int	set_num(char *set_name)
{
	static	char	*all[NUM_SETS] = {"julia", "mandel", "mandel_n", "ship", "tricorn"};
	int				i;

	i = 0;
	while (i < NUM_SETS)
	{
		if (ft_strcmp(set_name, all[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static void	precheck(int c, char **names)
{
	while (c-- > 0)
	{
		if (set_num(names[c]) == -1)
		{
			ft_putendl("using: fractol [julia | mandel | mandel_n | ship | tricorn]\n"
						"			   [julia | mandel | mandel_n | ship | tricorn]");
			exit(1);
		}
	}
}

static void	wait_children(void)
{
	int status;

	status = 1;
	while (status > 0)
	{
		status = wait(0);
		if (status == -1 && errno != ECHILD)
		{
			ft_putendl("Error during wait()");
			exit(1);
		}
	}
}

int			main(int argc, char **argv)
{
	int pid;

	if (argc == 1 || argc > 3)
		ft_putendl("using: fractol [julia | mandel | mandel_n | ship]\n"
				"			   [julia | mandel | mandel_n | ship]");
	else if (argc <= 3)
	{
		precheck(argc - 1, argv + 1);
		while (--argc)
		{
			pid = fork();
			if (pid > 0)
				continue;
			else if (pid == 0)
				fractol(set_num(argv[argc]));
			else
			{
				ft_putendl("ERROR: fork() failed");
				exit(1);
			}
		}
		if (pid > 0)
			wait_children();
	}
}
