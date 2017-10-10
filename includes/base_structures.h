/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 15:09:18 by ykolomie          #+#    #+#             */
/*   Updated: 2017/09/30 18:07:29 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_STRUCTURES_H
# define BASE_STRUCTURES_H

# include "mathx.h"
# include "mlx.h"
# include <OpenCL/opencl.h>

typedef struct		s_image
{
	void			*image;
	int				*ps;
	int				bpp;
	int				sl;
	int				endian;
}					t_image;

typedef struct      s_opencl
{
    cl_platform_id  platform_id;
    cl_device_id    device_id;
    cl_context      context;
    cl_command_queue command_queue;
    cl_program      program;
    cl_kernel       kernel;
    cl_mem          memobj;
	size_t 			global_size[3];
	size_t 			local_size[3];
}                   t_opencl;

typedef struct		s_fractol
{
	void			*mlx;
	void			*window;
	int				set;
	int				max_iter;
	int				palette;
	int				c_shift;
	t_image			image;
	t_cnum			julia_const;
	int				change_julia_const;
	int				change_julia_x;
	int				change_julia_y;
	t_cnum			change_julia_start;
	float			mandel_pow;
	double			zoom;
	double			move_y;
	double			move_x;
	double			map_area_x;
	double			map_area_y;
    t_opencl        opencl;
}					t_fractol;

typedef struct		s_param
{
	int				thread_num;
	t_fractol		*all;
}					t_param;

typedef int			(*t_set_pixel)(int, int, t_fractol*);

#endif
