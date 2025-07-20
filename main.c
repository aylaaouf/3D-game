#include "cub3d.h"

int main()
{
    void    *mlx;
    void    *win;

    mlx = mlx_init();
    win = mlx_new_window(mlx, 640, 480, "cub3D");
    
    (void)win;
    
    mlx_loop(mlx);
    return (0);
}