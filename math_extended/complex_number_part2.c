#include "mathx.h"
#include <math.h>

t_cnum  cn_pow(t_cnum *c, float p)
{
    double r;
    double phi;
    t_cnum      res;

    r = sqrt(c->r * c->r + c->i * c->i);
    phi = atan2(c->i, c->r);
    r = pow(r, p);
    res.r = r * cos(phi * p);
    res.i = r * sin(phi * p);
    return (res);
}