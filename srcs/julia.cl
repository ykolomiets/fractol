__kernel void julia(__global int *pixels,
                    int width,
                    int height,
                    double move_x,
                    double move_y,
                    double area_size_x,
                    double area_size_y,
                    double const_r,
                    double const_im,
                    int max_iter)
{
    float   new_r = 0.0f;
    float   new_im = 0.0f;
    float   old_r = 0.0f;
    float   old_im = 0.0f;
    int     k = 0;

    int x = get_global_id(0);
    int y = get_global_id(1);

    new_r = 4 * (x - width / 2.0) / area_size_x + 4 * move_x;
    new_im = 4 * (y - height / 2.0) / area_size_y + 4 * move_y;
    k = 0;
    while (k < max_iter && (new_im * new_im + new_r * new_r) < 4)
    {
        old_r = new_r;
        old_im = new_im;
        new_r = old_r * old_r - old_im * old_im + const_r;
        new_im = 2 * old_im * old_r + const_im;
        k++;
    }
    pixels[y * width + x] = k;
}