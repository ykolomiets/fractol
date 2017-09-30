/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 17:46:54 by ykolomie          #+#    #+#             */
/*   Updated: 2017/09/30 17:46:55 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hooks.h"
#include "fractol.h"

int		fractol_init(t_fractol *all)
{
	all->mlx = mlx_init();
	if (!all->mlx)
		return (1);
	all->window = mlx_new_window(all->mlx, WIN_WIDTH, WIN_HEIGHT, "Fractol");
	if (!all->window)
		return (2);
	all->image.image = mlx_new_image(all->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!all->image.image)
		return (3);
	all->image.ps = (int *)mlx_get_data_addr(all->image.image, &all->image.bpp,
											&all->image.sl, &all->image.endian);
	all->julia_const = cn_create(0, 0);
	all->change_julia_const = 0;
	all->mandel_pow = 0.05f;
	all->zoom = 1;
	all->move_y = 0;
	all->move_x = 0;
	all->map_area_x = WIN_WIDTH;
	all->map_area_y = WIN_HEIGHT;
	all->max_iter = 100;
	all->palette = 0;
	all->c_shift = 0;
	return (0);
}

void	fractol(int set_num)
{
	t_fractol	all;

	all.set = set_num;
	if (!fractol_init(&all))
	{
		render(&all);
		mlx_mouse_hook(all.window, mouse_hook, &all);
		mlx_key_hook(all.window, keys_hook, &all);
		mlx_hook(all.window, 2, 0, pressed_hook, &all);
		mlx_hook(all.window, 6, 1L << 6, motion_hook, &all);
		mlx_expose_hook(all.window, expose_hook, &all);
		mlx_loop(all.mlx);
	}
	else
		ft_putendl("error: initialization failed");
}
