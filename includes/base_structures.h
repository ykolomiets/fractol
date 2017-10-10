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

typedef struct		s_image
{
	void			*image;
	int				*ps;
	int				bpp;
	int				sl;
	int				endian;
}					t_image;

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
}					t_fractol;

typedef int			(*t_set_pixel)(int, int, t_fractol*);

typedef struct		s_param
{
	int				thread_num;
	t_fractol		*all;
}					t_param;

#endif
