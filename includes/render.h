#ifndef RENDER_H
#define RENDER_H

#include  "base_structures.h"

typedef struct  s_param
{
    int         thread_num;
    t_fractol   *all;
}               t_param;

void        render(t_fractol *all);

#endif