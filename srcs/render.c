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

static void *render_part(void *param)
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

void		render_cpu(t_fractol *all)
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

void        render_gpu(t_fractol *all)
{
    t_opencl    *opencl;
    cl_int      ret;
    int         width;
    int         height;

    opencl = &all->opencl;
    width = WIN_WIDTH;
    height = WIN_HEIGHT;
    ret = clSetKernelArg(opencl->kernel, 0, sizeof(cl_mem), (void *)&opencl->memobj);
    ret |= clSetKernelArg(opencl->kernel, 1, sizeof(int), (void *)&width);
    ret |= clSetKernelArg(opencl->kernel, 2, sizeof(int), (void *)&height);
    ret |= clSetKernelArg(opencl->kernel, 3, sizeof(double), (void *)&all->move_x);
    ret |= clSetKernelArg(opencl->kernel, 4, sizeof(double), (void *)&all->move_y);
    ret |= clSetKernelArg(opencl->kernel, 5, sizeof(double), (void *)&all->map_area_x);
    ret |= clSetKernelArg(opencl->kernel, 6, sizeof(double), (void *)&all->map_area_y);
	ret |= clSetKernelArg(opencl->kernel, 7, sizeof(double), (void *)&all->julia_const.r);
	ret |= clSetKernelArg(opencl->kernel, 8, sizeof(double), (void *)&all->julia_const.i);
    ret |= clSetKernelArg(opencl->kernel, 9, sizeof(int), (void *)&all->max_iter);
    if (!ret)
    {
        clEnqueueNDRangeKernel(opencl->command_queue, opencl->kernel, 2, NULL,
                               opencl->global_size, opencl->local_size,
                               0, NULL, NULL);
        ret = clEnqueueReadBuffer(opencl->command_queue, opencl->memobj, CL_TRUE, 0,
                                  WIN_HEIGHT * WIN_HEIGHT * sizeof(int), all->image.ps, 0, NULL, NULL);
        mlx_put_image_to_window(all->mlx, all->window, all->image.image, 0, 0);
        ft_putendl("GPU RENDER");
    }
}

void        render(t_fractol *all)
{
    if (all->render_unit == GPU)
		render_gpu(all);
    else if (all->render_unit == CPU)
		render_cpu(all);
}
