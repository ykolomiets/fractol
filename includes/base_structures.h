/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 18:10:40 by ykolomie          #+#    #+#             */
/*   Updated: 2017/04/20 15:41:49 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_STRUCTURES_H
# define BASE_STRUCTURES_H

#include "mathx.h"
#include "mlx.h"
#include "colors.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define NUM_THREADS 8

typedef struct      s_image
{
    void            *image;
    int             *pixels; // TRY ANOTHER DEVICE
    int             bpp;
    int             size_line;
    int             endian;
}                   t_image;

typedef struct      s_fractol
{
    void            *mlx;
    void            *window;
    int             set;
    int             max_iter;
    int             pallete;
    t_image         image;
    t_cnum          julia_const;
    float           mandel_pow;
    double          zoom;
    double          moveY;
    double          moveX;
    double          mapAreaX;
    double          mapAreaY;
}                   t_fractol;

#endif
