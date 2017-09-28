#ifndef FRACTOL_SETS_H
#define FRACTOL_SETS_H

#include "base_structures.h"

typedef int(*t_set_pixel)(int, int, t_fractol*);

t_set_pixel get_set_func(int num);

#endif
