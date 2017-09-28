#include "base_structures.h"
#include "sets.h"

static int  julia_pixel(int x, int y, t_fractol *all)
{
    int     i;
    int     max_iter;
    t_cnum  new;
    t_cnum  old;
    t_cnum  c;

    c = all->julia_const;
    max_iter = all->max_iter;
    new.r = 4 * ((long double)x - (long double)WIN_WIDTH / 2) / all->mapAreaX  + 4 * all->moveX ;
    new.i = 4 * ((long double)y - (long double)WIN_HEIGHT / 2) / all->mapAreaY + 4 * all->moveY ;
    i = 0;
    while (i < max_iter && (new.r * new.r + new.i * new.i) < 4)
    {
        old = new;
        new.r = old.r * old.r - old.i * old.i + c.r;
        new.i = 2 * old.i * old.r + c.i;
        i++;
    }
    return (i);
}

static int  mandelbrot_pixel(int x, int y, t_fractol *all)
{
    int     i;
    t_cnum  new;
    t_cnum  old;
    t_cnum  pixel;
    int     max_iter;

    pixel.r =4 * (x - WIN_WIDTH / 2) / all->mapAreaX  + 4 * all->moveX ;
    pixel.i =4 * (y - WIN_HEIGHT / 2) / all->mapAreaY + 4 * all->moveY ;
    new.i = 0;
    new.r = 0;
    i = 0;
    max_iter = all->max_iter;
    while (i < max_iter && (new.r * new.r + new.i * new.i) < 4)
    {
        old = new;
        new.r = old.r * old.r - old.i * old.i + pixel.r;
        new.i = 2 * old.r * old.i + pixel.i;
        i++;
    }
    return (i);
}

t_set_pixel get_set_func(int n)
{
    if (n == 0)
        return julia_pixel;
    else if (n == 1)
        return mandelbrot_pixel;
    return (0);
}