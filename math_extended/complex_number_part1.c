#include "mathx.h"
#include <math.h>

t_cnum  cn_create(float re, float im)
{
    t_cnum  res;

    res.r = re;
    res.i = im;
    return (res);
}

t_cnum  cn_add(t_cnum *a, t_cnum *b)
{
    t_cnum  res;

    res.r = a->r + b->r;
    res.i = a->i + b->i;
    return (res);
}

t_cnum  cn_sub(t_cnum *a, t_cnum *b)
{
    t_cnum  res;

    res.r = a->r - b->r;
    res.i = a->i - b->i;
    return (res);
}

t_cnum  cn_mult(t_cnum  *a, t_cnum *b)
{
    t_cnum  res;

    res.r = a->r * b->r - a->i * b->i;
    res.i = a->r * b->i + a->i * b->r;
    return (res);
}

int     cn_div(t_cnum *a, t_cnum *b, t_cnum *res)
{
    if (fabsl(b->r) < 0.00005 && fabsl(b->i) < 0.00005)
        return (1);
    res->r = (a->r * b->r + a->i * b->i) / (b->r * b->r + b->i * b->i);
    res->i = (a->i * b->r - a->r * b->i) / (b->r * b->r + b->i * b->i);
    return (0);
}