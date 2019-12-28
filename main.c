#include "minilibx_opengl_20191021/mlx.h"
#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

int		ft_pixel_key(int key, void *par)
{
	char *a;
	t_list	*param;

	param = (t_list *)par;
	a = ft_itoabase(key, "0123456789");
	mlx_string_put(param->content, (param->next)->content, 250, 250, 1000 * key, "SALUT LES AMIS");
	write(1, a, ft_strlen(a));
	write(1, "\n", 1);
	return (0);
}

int		ft_close(int button, int x, int y, void *par)
{
	char	*a;
	t_list	*param;
	
	a = ft_itoabase(button, "0123456789");
	param = (t_list *)par;
	if ((!x) || (!y))
		mlx_destroy_window(param->content, (param->next)->content);
	write(1, a, ft_strlen(a));
	write(1, "\n", 1);
	return (0);
}

int		main(void)
{
	void	*mlx_ptr;
	void	*win;
	t_list	*param;

	if ((mlx_ptr = mlx_init()))
	{
		param = ft_lstnew(mlx_ptr);
		win = mlx_new_window(mlx_ptr, 500, 500, "Ventana");
		param->next = ft_lstnew(win);
		mlx_pixel_put(mlx_ptr, win, 250, 250, 0xFFFFFF);
		mlx_key_hook(win, ft_pixel_key, param);
		mlx_mouse_hook(win, ft_close, param);
		mlx_loop(mlx_ptr);
	}
	return (0);
}
