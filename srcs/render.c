/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 18:47:58 by ykolomie          #+#    #+#             */
/*   Updated: 2017/10/01 18:47:59 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include <pthread.h>

static void	clean_image(t_fractol *all)
{
	int i;
	int j;

	i = -1;
	while (++i < WIN_HEIGHT)
	{
		j = -1;
		while (++j < WIN_WIDTH)
			all->image.ps[i * WIN_WIDTH + j] = 0xffffff;
	}
	mlx_put_image_to_window(all->mlx, all->window, all->image.image, 0, 0);
}

void		*render_part(void *param)
{
	t_param		*p;
	t_set_pixel	set_pixel;
	int			*palette;
	int			i;
	int			res;

	p = (t_param *)param;
	set_pixel = get_set_func(p->all->set);
	palette = get_color_palette(p->all->palette);
	i = p->thread_num;
	while (i < WIN_WIDTH * WIN_HEIGHT)
	{
		res = set_pixel(i % WIN_WIDTH, i / WIN_WIDTH, p->all);
		p->all->image.ps[i] = palette[(res % 64 + p->all->c_shift) % 64];
		i += NUM_THREADS;
	}
	pthread_exit(NULL);
}

void		render(t_fractol *all)
{
	pthread_t		threads[NUM_THREADS];
	pthread_attr_t	attr;
	t_param			params[NUM_THREADS];
	int				i;
	void			*res;

	clean_image(all);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	i = -1;
	while (++i < NUM_THREADS)
	{
		params[i].thread_num = i;
		params[i].all = all;
		pthread_create(&threads[i], &attr, render_part, &params[i]);
	}
	pthread_attr_destroy(&attr);
	i = -1;
	while (++i < NUM_THREADS)
		pthread_join(threads[i], &res);
	mlx_put_image_to_window(all->mlx, all->window, all->image.image, 0, 0);
}
