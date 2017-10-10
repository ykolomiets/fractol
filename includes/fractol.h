/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 15:05:08 by ykolomie          #+#    #+#             */
/*   Updated: 2017/09/30 18:21:01 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "base_structures.h"

# define WIN_WIDTH 512
# define WIN_HEIGHT 256
# define NUM_THREADS 4
# define NUM_SETS 4

void		fractol(int set);
void		render_pthread(t_fractol *all);
void        render_gpu(t_fractol *all);
int			*get_color_palette(int num);
t_set_pixel	get_set_func(int num);

#endif
