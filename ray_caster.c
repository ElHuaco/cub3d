/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 20:00:13 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/03/05 15:33:07 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_pixel_textures(t_imgs *img, int i, int j, t_vars *var)
{
	char	*dst;
	int		side;
	int		corresp_tex_coord[2];

	side = 1 * (var->side == 'n') + 2 * (var->side == 's')
		+ 3 * (var->side == 'w') + 4 * (var->side == 'e');
	corresp_tex_coord[0] = img[side].img_w * var->ray_hit[i];
	corresp_tex_coord[1] = img[side].img_h
		* (j - var->map->wall_start[i]) / var->map->wall_linelength[i];
	dst = img[0].addr + j * img[0].ll + i * (img[0].bpp / 8);
	*(unsigned int*)dst = *(unsigned int*)(img[side].addr
		+ corresp_tex_coord[1] * img[side].ll
		+ corresp_tex_coord[0] * (img[side].bpp / 8));
}

static void	put_pixel_solid(t_imgs *img, int i, int j, unsigned int color)
{
	char	*dst;

	dst = img[0].addr + j * img[0].ll + i * (img[0].bpp / 8);
	*(unsigned int *)dst = color;
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
		len[2] = (int)((0.5 * var->map->res_height) * (1.0 - 1.0 / len[0]));
		len[1] = (int)((0.5 * var->map->res_height) * (1.0 + 1.0 / len[0]));
	}
	len[3] = len[2];
	len[4] = len[1];
	if (len[2] < 0)
		len[2] = 0;
	if (len[1] >= var->map->res_height)
		len[1] = var->map->res_height - 1;
}

int			ray_caster(t_vars *var)
{
	int		i;
	int		j;
	double	len[5];
	t_imgs	img[1 + 4 + SPRITE_NUMBER];

	create_textures_mlx_img(var, img);
	i = -1;
	var->ray_hit = malloc(sizeof(double) * var->map->res_width);
	var->map->wall_linelength = malloc(sizeof(int) * var->map->res_width);
	var->map->wall_start = malloc(sizeof(int) * var->map->res_width);
	while (++i < var->map->res_width)
	{
		len[0] = ray_distance(var, i);
		set_pixel_limits(var, len);
		var->map->wall_linelength[i] = (int)len[4] - (int)len[3];
		var->map->wall_start[i] = (int)len[3];
		j = -1;
		while (++j < (int)len[2])
			put_pixel_solid(img, i, j, var->map->ceiling_color);
		while (j < (int)len[1])
			put_pixel_textures(img, i, j++, var);
		while (j < var->map->res_height - 1)
			put_pixel_solid(img, i, j++, var->map->floor_color);
	}
	mlx_put_image_to_window(var->mlx, var->win, img[0].img, 0, 0);
	if (var->must_save == 1)
		save_img(var, img[0].img);
	i = -1;
	while (++i < 5 + SPRITE_NUMBER)
		mlx_destroy_image(var->win, img[i].img);
	free(var->ray_hit);
	free(var->map->wall_start);
	free(var->map->wall_linelength);
	return (0);
}
