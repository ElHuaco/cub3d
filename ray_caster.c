/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 20:00:13 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/07 20:41:45 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_pixel_texture(t_imgs *img, int i, int j, t_vars *var)
{
	char	*dst;
	int		img_w;
	int		img_h;
	int		el;
	t_imgs	textu;

	dst = img->addr + j * img->ll + i * (img->bpp / 8);
	el =  0 * (var->side == 'n') + (var->side == 's') + 2 * (var->side == 'w')
	+ 3 * (var->side == 'e');
	textu.img = mlx_xpm_file_to_img(var->mlx, var->map->texture[el], &img_w, &img_h);
	textu.addr = mlx_get_data_addr(textu.img, &textu.bpp, &textu.ll, &textu.endian);
	*(unsigned int*)dst = *(textu.addr + j * textu.ll + i * (textu.bpp / 8));
}

static void	put_pixel_solid(t_imgs *img, int i, int j, unsigned int color)
{
	char	*dst;

	dst = img->addr + j * img->ll + i * (img->bpp / 8);
	*(unsigned int*)dst = color;
}

static void	set_pixel_limits(t_vars *var, double **len)
{
	if (*len[0] == 0.0)
		*len[1] = 0.1;	//feo
	else
		*len[1] = var->map->res_height / *len[0];
	*len[2] = *len[1];
	*len[0] = (int)((-1* (int)*len[2] + var->map->res_height) / 2);
	if (*len[0] < 0)
		*len[0] = 0;
	*len[1] = (int)(((int)*len[2] + var->map->res_height) / 2);
	if (*len[1] >= var->map->res_height)
		*len[1] = var->map->res_height - 1;
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
	i = -1;
	while (++i < var->map->res_width)
	{
		len[0] = ray_distance(var, i);
		set_pixel_limits(var, &len);
		j = -1;
		while (++j < (int)len[0])
			put_pixel_solid(&img, i, j, var->map->ceiling_color);
		while (j++ < (int)len[1])
			put_pixel_texture(&img, i, j, var);
		while (j++ < var->map->res_height)
			put_pixel_solid(&img, i, j, var->map->floor_color);
	}
	mlx_put_image_to_window(var->mlx, var->win, img.img, 0, 0);
	if (var->must_save == 1)
		save_img(var, img.img);
	return (0);
}
