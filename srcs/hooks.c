/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 18:46:18 by ykolomie          #+#    #+#             */
/*   Updated: 2017/10/01 18:47:26 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"
#include "fractol_fdf.h"
#include "mathx.h"
#include "base_structures.h"
#include <stdlib.h>

int	motion_hook(int x, int y, t_fractol *all)
{
	if (all->set == 0 && all->change_julia_const)
	{
		if (IN_RANGE(x, 0, WIN_WIDTH - 1) && IN_RANGE(y, 0, WIN_HEIGHT - 1))
		{
			all->julia_const.r = all->change_julia_start.r +
					((double)x - all->change_julia_x) / WIN_WIDTH;
			all->julia_const.i = all->change_julia_start.i +
					((double)y - all->change_julia_y) / WIN_HEIGHT;
		}
	}
	render(all);
	return (0);
}

int	keys_hook(int keycode, t_fractol *all)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 35)
		fractol_3d(all);
	else if (keycode == 36)
	{
		all->julia_const = cn_create(0, 0);
		all->zoom = 1;
		all->move_y = 0;
		all->move_x = 0;
		all->map_area_x = WIN_WIDTH;
		all->map_area_y = WIN_HEIGHT;
	}
	else if (keycode == 49)
		all->palette = (all->palette + 1) % 4;
	else if (keycode == 24 && all->max_iter < 500)
		all->max_iter += 50;
	else if (keycode == 27 && all->max_iter > 50)
		all->max_iter -= 50;
	render(all);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_fractol *all)
{
	if (button == 1 && all->set == 0)
	{
		all->change_julia_const = 1 - all->change_julia_const;
		all->change_julia_x = x;
		all->change_julia_y = y;
		all->change_julia_start = all->julia_const;
	}
	if (button == 5 && x > 0 && y > 0 && all->zoom <= 1099511627776.0)
	{
		all->zoom *= 2.0;
		all->move_x += -(WIN_WIDTH / 2.0 - x) / (float)all->map_area_x / 2.0;
		all->move_y += -(WIN_HEIGHT / 2.0 - y) / (float)all->map_area_y / 2.0;
		all->map_area_x = WIN_WIDTH * all->zoom;
		all->map_area_y = WIN_HEIGHT * all->zoom;
	}
	else if (button == 4)
	{
		all->zoom /= 2.0;
		all->map_area_x = WIN_WIDTH * all->zoom;
		all->map_area_y = WIN_HEIGHT * all->zoom;
		all->move_x += (WIN_WIDTH / 2.0 - x) / (float)all->map_area_x / 2.0;
		all->move_y += (WIN_HEIGHT / 2.0 - y) / (float)all->map_area_y / 2.0;
	}
	render(all);
	return (0);
}

int	pressed_hook(int keycode, t_fractol *all)
{
	t_cnum	c;

	c = all->julia_const;
	if (keycode == 7 && all->mandel_pow < 4.98f)
		all->mandel_pow += 0.02;
	else if (keycode == 8 && all->mandel_pow > 0.07f)
		all->mandel_pow -= 0.02;
	if (keycode == 123)
		all->c_shift = (all->c_shift + 1) % 64;
	else if (keycode == 124)
		all->c_shift = all->c_shift ? all->c_shift - 1 : 63;
	else if (keycode == 13)
		all->move_y -= 0.001;
	else if (keycode == 1)
		all->move_y += 0.001;
	else if (keycode == 2)
		all->move_x += 0.001;
	else if (keycode == 0)
		all->move_x -= 0.001;
	all->julia_const = c;
	render(all);
	return (0);
}

int	expose_hook(t_fractol *all)
{
	render(all);
	return (0);
}
