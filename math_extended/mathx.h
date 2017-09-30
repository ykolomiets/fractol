/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathx.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 22:47:27 by ykolomie          #+#    #+#             */
/*   Updated: 2017/04/20 16:19:38 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHX_H
# define MATHX_H

# define PI 3.141592653589793f
# define ROUND(a) ((int)(a + 0.5))
# define ABS(a) ((a) < 0 ? -(a) : (a))

typedef struct  s_vec2
{
    float x;
    float y;
}               t_vec2;

typedef struct  s_vec3
{
    float x;
    float y;
    float z;
}               t_vec3;

typedef struct  s_hvec
{
    float x;
    float y;
    float z;
    float w;
}               t_hvec;

typedef struct  s_cnum
{
    double  r;
    double  i;
}               t_cnum;

typedef float   matrix3[9];
typedef float   matrix4[16];

t_vec2          v2_create(float x, float y);
t_vec2          v2_add(t_vec2 a, t_vec2 b);
t_vec2          v2_sub(t_vec2 a, t_vec2 b);
int             v2_mult_by_scalar(t_vec2 *a, float c);
int             v2_div_by_scalar(t_vec2 *a, float c);
float           v2_dot_product(t_vec2 *a, t_vec2 *b);
float           v2_magnitude(t_vec2 *a);
t_vec2          v2_normalize(t_vec2 a);

t_vec3          v3_create(float x, float y, float z);
t_vec3          v3_add(t_vec3 a, t_vec3 b);
t_vec3          v3_sub(t_vec3 a, t_vec3 b);
int             v3_mult_by_scalar(t_vec3 *a, float c);
int             v3_div_by_scalar(t_vec3 *a, float c);
float           v3_dot_product(t_vec3 *a, t_vec3 *b);
t_vec3          v3_cross_product(t_vec3 *a, t_vec3 *b);
float           v3_magnitude(t_vec3 *a);
t_vec3          v3_normalize(t_vec3 v);

t_hvec          hv_create_point(float x, float y, float z);
t_hvec          hv_create_direction(float x, float y, float z);
t_hvec          hv_normalize(t_hvec v);

void            m3_fill_null(matrix3 m);
void            m3_identity(matrix3 m);
float           m3_det(matrix3 m);
int             m3_inverse(matrix3 m, matrix3 res);

t_vec3          m3_mult_v3(matrix3 m, t_vec3 *v);

void            m4_fill_null(matrix4 m);
void            m4_identity(matrix4 m);
void            m4_mult(matrix4 a, matrix4 b, matrix4 res);
void            m4_add(matrix4 a, matrix4 b, matrix4 res);
void            m4_sub(matrix4 a, matrix4 b, matrix4 res);
void            m4_submat(matrix4 m, matrix3 sub, int i, int j);
float           m4_det(matrix4 m);
int             m4_inverse(matrix4 m, matrix4 res);

t_hvec          m4_mult_hv(matrix4 m, t_hvec *v);

t_cnum          cn_create(float re, float im);
t_cnum          cn_add(t_cnum *a, t_cnum *b);
t_cnum          cn_sub(t_cnum *a, t_cnum *b);
t_cnum          cn_mult(t_cnum *a, t_cnum *b);
int             cn_div(t_cnum *a, t_cnum *b, t_cnum *res);
t_cnum          cn_pow(t_cnum *c, float pow);



#endif
