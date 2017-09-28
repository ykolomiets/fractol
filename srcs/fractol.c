#include "libft.h"
#include "base_structures.h"
#include "render.h"
#include <stdlib.h>
#include <stdio.h>

int         keys_hook(int keycode, t_fractol *all)
{
    printf("keycode: %d\n", keycode);
    if (keycode == 53)
        exit(0);
    else if (keycode == 19)
        render(all);
    else if (keycode == 24)
        all->max_iter += 50;
    else if (keycode == 27)
        all->max_iter -= 50;
    render(all);
    return (0);
}

int         mouse_hook(int button, int x, int y, t_fractol *all)
{
    if (button == 1)
        all->set = (all->set + 1) % 2;
    if (button == 5 && x > 0 && y > 0)
    {
        all->zoom *= 2.0;
        printf("all->zoom = %Lf", all->zoom);
        all->moveX += -(WIN_WIDTH / 2.0 - x) / (float)all->mapAreaX / 2.0;
        all->moveY += -(WIN_HEIGHT / 2.0 - y) / (float)all->mapAreaY / 2.0;
        all->mapAreaX = WIN_WIDTH * all->zoom;
        all->mapAreaY = WIN_HEIGHT * all->zoom;
    }
    else if (button == 4)
    {
        all->zoom /= 2.0;
        all->mapAreaX = WIN_WIDTH * all->zoom;
        all->mapAreaY = WIN_HEIGHT * all->zoom;
        all->moveX += (WIN_WIDTH / 2.0 - x) / (float)all->mapAreaX / 2.0;
        all->moveY += (WIN_HEIGHT / 2.0 - y) / (float)all->mapAreaY / 2.0;
    }
    render(all);
    return (0);
}

int         pressed_hook(int keycode, t_fractol *all)
{
    t_cnum  c;

    printf("Keycode: %d\n", keycode);
    c = all->julia_const;
    if (keycode == 123 && (c.r * c.r + c.i * c.i) < 4)
        c.r -= 0.01;
    else if (keycode == 124 && (c.r * c.r + c.i * c.i) < 4)
        c.r += 0.01;
    else if (keycode == 125 && (c.r * c.r + c.i * c.i) < 4)
        c.i -= 0.01;
    else if (keycode == 126 && (c.r * c.r + c.i * c.i) < 4)
        c.i += 0.01;
    else if (keycode == 13)
        all->moveY -= 0.001;
    else if (keycode == 1)
        all->moveY += 0.001;
    else if (keycode == 2)
        all->moveX += 0.001;
    else if (keycode == 0)
        all->moveX -= 0.001;
    all->julia_const = c;
    render(all);
    return (0);
}

int         fractol_init(t_fractol *all)
{
    all->mlx = mlx_init();
    if (!all->mlx)
        return (1);
    all->window = mlx_new_window(all->mlx, WIN_WIDTH, WIN_HEIGHT, "Fractol");
    if (!all->window)
        return (2);
    all->image.image = mlx_new_image(all->mlx, WIN_WIDTH, WIN_HEIGHT);
    if (!all->image.image)
        return (3);
    all->image.pixels = (int *)mlx_get_data_addr(all->image.image, &all->image.bpp,
                                          &all->image.size_line, &all->image.endian);
    all->julia_const = cn_create(0, 0);
    all->zoom = 1;
    all->moveY = 0;
    all->moveX = 0;
    all->mapAreaX = WIN_WIDTH;
    all->mapAreaY = WIN_HEIGHT;
    all->max_iter = 512;
    all->pallete = 0;
    return (0);
}

void        fractol(int set_num)
{
    t_fractol   all;

    all.set = set_num;
    if (!fractol_init(&all))
    {
        render(&all);
        mlx_mouse_hook(all.window, mouse_hook, &all);
        mlx_key_hook(all.window, keys_hook, &all);
        mlx_hook(all.window, 2, 0, pressed_hook, &all);
        mlx_loop(all.mlx);
    }
    else
        ft_putendl("error: initialization failed");
}


