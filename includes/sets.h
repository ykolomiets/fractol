/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 13:31:00 by ykolomie          #+#    #+#             */
/*   Updated: 2017/10/10 13:31:01 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETS_H
# define SETS_H

# include "base_structures.h"

int	julia_pixel(int x, int y, t_fractol *all);
int	mandelbrot_pixel(int x, int y, t_fractol *all);
int	ship_pixel(int x, int y, t_fractol *all);
int	mandelbrot_n_pixel(int x, int y, t_fractol *all);
int	tricorn_pixel(int x, int y, t_fractol *all);

#endif
