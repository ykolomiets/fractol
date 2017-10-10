#ifndef SETS_H
#define SETS_H

# include "base_structures.h"

int	julia_pixel(int x, int y, t_fractol *all);
int	mandelbrot_pixel(int x, int y, t_fractol *all);
int	ship_pixel(int x, int y, t_fractol *all);
int	mandelbrot_n_pixel(int x, int y, t_fractol *all);
int	tricorn_pixel(int x, int y, t_fractol *all);

#endif
