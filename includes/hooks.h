/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 15:17:00 by ykolomie          #+#    #+#             */
/*   Updated: 2017/09/30 15:17:01 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "fractol.h"

int keys_hook(int keycode, t_fractol *all);
int pressed_hook(int keycode, t_fractol *all);
int mouse_hook(int button, int x, int y, t_fractol *all);
int expose_hook(t_fractol *all);
int motion_hook(int x, int y, t_fractol *all);

#endif
