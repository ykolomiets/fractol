/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 18:05:30 by ykolomie          #+#    #+#             */
/*   Updated: 2017/09/30 18:05:32 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "sets.h"
#include "mathx.h"

int	julia_pixel(int x, int y, t_fractol *all)
{
	int		i;
	int		max_iter;
	t_cnum	new;
	t_cnum	old;
	t_cnum	c;

	c = all->julia_const;
	max_iter = all->max_iter;
	new.r = 4 * ((double)x - (double)WIN_WIDTH / 2) / all->map_area_x
													+ 4 * all->move_x;
	new.i = 4 * ((double)y - (double)WIN_HEIGHT / 2) / all->map_area_y
													+ 4 * all->move_y;
	i = 0;
	while (i < max_iter && (new.r * new.r + new.i * new.i) < 4)
	{
		old = new;
		new.r = old.r * old.r - old.i * old.i + c.r;
		new.i = 2 * old.i * old.r + c.i;
		i++;
	}
	return (i);
}

int	mandelbrot_pixel(int x, int y, t_fractol *all)
{
	int		i;
	t_cnum	new;
	t_cnum	old;
	t_cnum	pixel;
	int		max_iter;

	pixel.r = 4 * (x - WIN_WIDTH / 2) / all->map_area_x
										+ 4 * all->move_x;
	pixel.i = 4 * (y - WIN_HEIGHT / 2) / all->map_area_y
										+ 4 * all->move_y;
	new.i = 0;
	new.r = 0;
	i = 0;
	max_iter = all->max_iter;
	while (i < max_iter && (new.r * new.r + new.i * new.i) < 4)
	{
		old = new;
		new.r = old.r * old.r - old.i * old.i + pixel.r;
		new.i = 2 * old.r * old.i + pixel.i;
		i++;
	}
	return (i);
}

int	ship_pixel(int x, int y, t_fractol *all)
{
	int		i;
	t_cnum	new;
	t_cnum	old;
	t_cnum	pixel;
	int		max_iter;

	pixel.r = 4 * (x - WIN_WIDTH / 2) / all->map_area_x + 4 * all->move_x;
	pixel.i = 4 * (y - WIN_HEIGHT / 2) / all->map_area_y + 4 * all->move_y;
	new.i = 0;
	new.r = 0;
	i = 0;
	max_iter = all->max_iter;
	while (i < max_iter && (new.r * new.r + new.i * new.i) < 4)
	{
		old = new;
		new.r = old.r * old.r - old.i * old.i + pixel.r;
		new.i = 2 * ABS(old.r * old.i) + pixel.i;
		i++;
	}
	return (i);
}

int	mandelbrot_n_pixel(int x, int y, t_fractol *all)
{
	int		i;
	t_cnum	new;
	t_cnum	old;
	t_cnum	pixel;
	int		max_iter;

	pixel.r = 4 * (x - WIN_WIDTH / 2) / all->map_area_x + 4 * all->move_x;
    pixel.i = 4 * (y - WIN_HEIGHT / 2) / all->map_area_y + 4 * all->move_y;
    new.i = 0;
    new.r = 0;
	i = 0;
	max_iter = all->max_iter;
	while (i < max_iter && (new.r * new.r + new.i * new.i) < 4)
	{
		old = new;
		new = cn_pow(&old, all->mandel_pow);
		new.r += pixel.r;
		new.i += pixel.i;
		i++;
	}
	return (i);
}

int	tricorn_pixel(int x, int y, t_fractol *all)
{
	int 	i;
	t_cnum	new;
	t_cnum	c;
    double  temp;
	int 	max_iter;

	c.r = 4 * (x - WIN_WIDTH / 2) / all->map_area_x + 4 * all->move_x;
	c.i = 4 * (y - WIN_HEIGHT / 2) / all->map_area_y + 4 * all->move_y;
	i = 0;
	new.i = 0;
	new.r = 0;
	max_iter = all->max_iter;
	while (i < max_iter && (new.r * new.r + new.i * new.i) < 4)
	{
        temp = new.r;
        new.r = new.r * new.r - new.i * new.i + c.r;
        new.i = -2 * new.i * temp + c.i;
		i++;
	}
	return (i);
}
