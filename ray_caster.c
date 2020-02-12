/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 20:00:13 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/12 16:13:22 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_pixel_textures(t_imgs *img, int i, int j, t_vars *var)
{
	char	*dst;
//	int		img_w;
//	int		img_h;
//	int		el;
//	t_imgs	textu;

	dst = img->addr + j * img->ll + i * (img->bpp / 8);
//	el =  0 * (var->side == 'n') + (var->side == 's') + 2 * (var->side == 'w')
//	+ 3 * (var->side == 'e');
//	textu.img = mlx_xpm_file_to_image(var->mlx, var->map->textures[el], &img_w, &img_h);
//	printf("text %d %s llamada\n", el, var->map->textures[el]);
//	textu.addr = mlx_get_data_addr(textu.img, &textu.bpp, &textu.ll, &textu.endian);
//	printf("asginamos pixel\n");
//	*(unsigned int*)dst = *(textu.addr + j * textu.ll + i * (textu.bpp / 8));
	if (var->side == 'n')
		*(unsigned int*)dst = 0x00ff00;
	if (var->side == 's')
		*(unsigned int*)dst = 0x008000;
	else if (var->side == 'w')
		*(unsigned int*)dst = 0xffff00;
	else if (var->side == 'e')
		*(unsigned int*)dst = 0xdaa520;
}

static void	put_pixel_solid(t_imgs *img, int i, int j, unsigned int color)
{
	char	*dst;

	//printf("pixel solid called for %d %d\n", i, j);
	dst = img->addr + j * img->ll + i * (img->bpp / 8);
	*(unsigned int*)dst = color;
	//printf("Pixel %d, %d asignado color %u\n", i, j, color);
}

static void	set_pixel_limits(t_vars *var, double *len)
{
	if (fabs(len[0] - 0.0) < 10e-7)
	{
		len[2] = 0;
		len[1] = var->map->res_height - 1;
	}
	else
	{
		len[2] = (int)((0.5 * var->map->res_height) * (1.0 - 1 / len[0]));
		len[1] = (int)((0.5 * var->map->res_height) * (1.0 + 1 / len[0]));
	}
	if (len[2] < 0)
		len[2] = 0;
	if (len[1] >= var->map->res_height)
		len[1] = var->map->res_height - 1;
	//printf("\tPixeles cota: %d, %d\n", (int)len[0], (int)len[1]);
}

static void	save_img(t_vars *var, void *img)
{
	//Guarda la imagen en bpp
	var->must_save = 0;
	img = 0;
}

int			ray_caster(t_vars *var)
{
	int		i;
	int		j;
	double	len[3];
	t_imgs	img;

	img.img = mlx_new_image(var->mlx,
		var->map->res_width, var->map->res_height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.endian);
	//printf("Imagen del frame creada\n");
	i = -1;
	while (++i < var->map->res_width)
	{
		len[0] = ray_distance(var, i);
		//printf("\tDistancia %f para rayo %d\n", len[0], i);
		set_pixel_limits(var, len);
		j = -1;
		//printf("\tPutting ceiling till %d\n", (int)len[2]);
		//printf("\tPutting wall till %d\n", (int)len[1]);
		//printf("\tPutting floor till %d\n", var->map->res_height - 1);
		while (++j < (int)len[2])
			put_pixel_solid(&img, i, j, 0xff0000/*var->map->ceiling_color*/);
		while (j < (int)len[1])
			put_pixel_textures(&img, i, j++, var);
		while (j < var->map->res_height - 1)
			put_pixel_solid(&img, i, j++, 0x0000ff /*var->map->floor_color*/);
	}
	//printf("Pusheamos la imagen a la ventana\n");
	mlx_put_image_to_window(var->mlx, var->win, img.img, 0, 0);
	mlx_destroy_image(var->win, img.img);
	//printf("sigma : %f\n", var->sigma * 180.0 / PI);
	if (var->must_save == 1)
		save_img(var, img.img);
	return (0);
}
