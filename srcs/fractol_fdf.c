/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_fdf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 18:49:33 by ykolomie          #+#    #+#             */
/*   Updated: 2017/10/01 18:49:34 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_fdf.h"
#include "fractol.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static char	*color_hex(int dec)
{
	static char	*hex = "0123456789ABCDEF";
	char		*color;
	int			i;

	color = ft_strnew(9);
	i = 7;
	color[0] = '0';
	color[1] = 'x';
	while (i >= 2)
	{
		color[i] = hex[dec % 16];
		dec /= 16;
		i--;
	}
	color[8] = ' ';
	return (color);
}

static char	*form_str(int z, int color)
{
	char	*temp1;
	char	*temp2;
	char	*all;

	temp1 = ft_itoa(z);
	temp2 = ft_strjoin(temp1, ",");
	free(temp1);
	temp1 = color_hex(color);
	all = ft_strjoin(temp2, temp1);
	free(temp1);
	free(temp2);
	return (all);
}

static int	write_res(int fd, int z, int color)
{
	char	*all;
	char	*temp;
	int		wrote;
	size_t	len;

	all = form_str(z, color);
	len = ft_strlen(all);
	temp = all;
	while ((wrote = write(fd, temp, len)))
	{
		if (wrote == -1)
		{
			free(all);
			return (1);
		}
		temp += wrote;
		len -= wrote;
		if (len == 0)
			break ;
	}
	free(all);
	return (0);
}

static int	render_in_file(int fd, t_fractol *all)
{
	int			res;
	int			i;
	int			j;
	int			*palette;
	t_set_pixel	set_pixel;

	set_pixel = get_set_func(all->set);
	palette = get_color_palette(all->palette);
	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			res = set_pixel(j, i, all);
			if (write_res(fd, res, palette[(res % 64 + all->c_shift) % 64]))
				return (1);
			j += 2;
		}
		write(fd, "\n", 1);
		i += 2;
	}
	return (0);
}

int			fractol_3d(t_fractol *all)
{
	int		fd;
	int		ret;
	int		pid;

	fd = open("test.fdf", O_CREAT | O_RDWR | O_TRUNC, 0666);
	ret = 1;
	if (fd > 0)
	{
		ret = render_in_file(fd, all);
		close(fd);
		pid = fork();
		if (pid == -1)
			return (1);
		else if (pid == 0)
			execl("./fdf/fdf", "fdf", "test.fdf", (char *)NULL);
	}
	return (ret);
}
