#include "minilibx_opengl_20191021/mlx.h"
#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

int		ft_pixel_key(int key, void *par)
{
	char *a;
	t_list	*param;
	static void	*img;
	static int x;
	static int y;
	int		size[2]; size[0] = 10; size[1] = 10;

	param = (t_list *)par;
	img = mlx_png_file_to_image(param->content, "2.png", size, size + 1);
	a = ft_itoabase(key, "0123456789");
	mlx_string_put(param->content, (param->next)->content, 250, 250, 100000 * key, "SALUT LES AMIS");
	write(1, a, ft_strlen(a));
	write(1, "\n", 1);
	if (key == 53)
		exit(0);
	if (key == 49)
	{
		x = 100;
		y = 100;
		mlx_put_image_to_window(param->content, (param->next)->content, img, x, y);
	}
	if (key == 123)
	{
		mlx_destroy_image(param->content, img);
		mlx_put_image_to_window(param->content, (param->next)->content, img, x--, y);
	}
	if (key == 124)
	{
		mlx_destroy_image(param->content, img);
		mlx_put_image_to_window(param->content, (param->next)->content, img, x++, y);
	}
	if (key == 125)
	{
		mlx_destroy_image(param->content, img);
		mlx_put_image_to_window(param->content, (param->next)->content, img, x, y++);
	}
	if (key == 126)
	{
		mlx_destroy_image(param->content, img);
		mlx_put_image_to_window(param->content, (param->next)->content, img, x, y--);
	}
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
	t_list	**begin;

	if ((mlx_ptr = mlx_init()))
	{
		begin = malloc(sizeof(t_list **) * 1);
		*begin = ft_lstnew(mlx_ptr);
		win = mlx_new_window(mlx_ptr, 500, 500, "Ventana");
		(*begin)->next = ft_lstnew(win);
		mlx_pixel_put(mlx_ptr, win, 250, 250, 0xFFFFFF);
		mlx_key_hook(win, ft_pixel_key, *begin);
		mlx_mouse_hook(win, ft_close, *begin);
		mlx_loop(mlx_ptr);
		free(begin);
	}
	return (0);
}
