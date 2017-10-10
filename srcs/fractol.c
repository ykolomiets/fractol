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

void    read_kernel(int set_num, char **str, size_t *size)
{
    static char*    kernels[] = {"srcs/julia.cl", "srcs/mandelbrot.cl", "srcs/ship.cl"};
    int             fd;

    ft_putendl("read_kernel");
    fd = open(kernels[set_num], O_RDONLY);
    if (fd > 0)
    {
        *str = read_file(fd);
        *size = ft_strlen(*str);
        ft_putendl(*str);
    }
    else
    {
        *str = NULL;
        *size = 0;
    }
    close(fd);
}

int     opencl_init(t_opencl *opencl, int set_num)
{
    cl_int          ret;
    cl_uint          temp;
    size_t          kernel_str_size;
    char            *kernel_str;

    ft_putendl("opencl_init");
    ret = clGetPlatformIDs(1, &opencl->platform_id, &temp);
    ret = clGetDeviceIDs(opencl->platform_id, CL_DEVICE_TYPE_GPU, 1, &opencl->device_id, &temp);
    opencl->context = clCreateContext(NULL, 1, &opencl->device_id, NULL, NULL, &ret);
    opencl->command_queue = clCreateCommandQueue(opencl->context, opencl->device_id, 0, &ret);
    read_kernel(set_num, &kernel_str, &kernel_str_size);
    if (!kernel_str)
        return (1);
    opencl->program = clCreateProgramWithSource(opencl->context, 1, (const char **)&kernel_str,
                                                (const size_t *)&kernel_str_size, &ret);
    ret = clBuildProgram(opencl->program, 1, &opencl->device_id, NULL, NULL, NULL);
    opencl->kernel = clCreateKernel(opencl->program, "julia", &ret);
    opencl->memobj = clCreateBuffer(opencl->context, CL_MEM_READ_WRITE, WIN_WIDTH * WIN_HEIGHT * sizeof(int), NULL, &ret);
    opencl->global_size[0] = WIN_WIDTH;
    opencl->global_size[1] = WIN_HEIGHT;
    opencl->local_size[0] = 16;
    opencl->local_size[1] = 16;
    ft_putnbr(ret);
    if (ret)
        return (1);
    return (0);
}

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
    all->render_unit = CPU;
    if (!opencl_init(&all->opencl, all->set))
        all->render_unit = GPU;
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
