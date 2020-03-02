/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 20:00:13 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/03/02 13:10:49 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_pixel_textures(t_imgs *img, int i, int j, t_vars *var)
{
	char	*dst;
	int		side;
	int		corresp_texel_coord[2];

	//printf("text %s usada\n", var->map->textures[0 * (var->side == 'n') + 1 * (var->side == 's') + 2 * (var->side == 'w')
//		+ 3 * (var->side == 'e')]);
	side = 1 * (var->side == 'n') + 2 * (var->side == 's')
		+ 3 * (var->side == 'w') + 4 * (var->side == 'e');
	corresp_texel_coord[0] = img[side].img_w * var->ray_hit[i];
	corresp_texel_coord[1] = img[side].img_h * (j - var->map->wall_start[i]) / var->map->wall_linelength[i]; 
	printf("\timg dim %d %d\n", img[side].img_w, img[side].img_h);
	printf("\twall_linelength: %d\n", var->map->wall_linelength[i]);
	printf("\tCol relat: %f Row relat: %f\n", var->ray_hit[i], (double)((j - var->map->wall_start[i])) / var->map->wall_linelength[i]);
	printf("\tintentamos asignar texel %d %d a pixel %d %d\n", corresp_texel_coord[0], corresp_texel_coord[1], i, j);
	dst = img[0].addr + j * img[0].ll + i * (img[0].bpp / 8);
	*(unsigned int*)dst = *(unsigned int*)(img[side].addr
		+ corresp_texel_coord[1] * img[side].ll
		+ corresp_texel_coord[0] * (img[side].bpp / 8));
	printf("\tasignamos texel %d %d a pixel %d %d\n", corresp_texel_coord[0], corresp_texel_coord[1], i, j);
}

static void	put_pixel_solid(t_imgs *img, int i, int j, unsigned int color)
{
	char	*dst;

	printf("pixel solid called for %d %d\n", i, j);
	dst = img[0].addr + j * img[0].ll + i * (img[0].bpp / 8);
	*(unsigned int *)dst = color;
	printf("\tPixel %d, %d asignado color %u\n", i, j, color);
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
	printf("\tPixeles cota: %d, %d\n", (int)len[2], (int)len[1]);
}

int			ray_caster(t_vars *var)
{
	int		i;
	int		j;
	double	len[5]; //Al introducir var->ray_len, len[2]
	t_imgs	img[1 + 4 + SPRITE_NUMBER];

	img[0].img = mlx_new_image(var->mlx,
		var->map->res_width, var->map->res_height);
	create_textures_mlx_img(var, img);
	i = -1;
	while (++i < 5 + SPRITE_NUMBER)
	{
		if (img[i].img)
			img[i].addr = mlx_get_data_addr(img[i].img, &img[i].bpp,
				&img[i].ll, &img[i].endian);
	}
	i = -1;
	var->ray_hit = malloc(sizeof(double) * var->map->res_width);
	var->map->wall_linelength = malloc(sizeof(int) * var->map->res_width);
	var->map->wall_start = malloc(sizeof(int) * var->map->res_width);
	while (++i < var->map->res_width)
	{
		printf("Ray Distance called\n");
		len[0] = ray_distance(var, i);
		set_pixel_limits(var, len);
		var->map->wall_linelength[i] = (int)len[4] - (int)len[3];
		var->map->wall_start[i] = (int)len[3];
		j = -1;
		//printf("\tPutting ceiling till %d\n", (int)len[2]);
		//printf("\tPutting wall till %d\n", (int)len[1]);
		//printf("\tPutting floor till %d\n", var->map->res_height - 1);
		while (++j < (int)len[2])
			put_pixel_solid(img, i, j, 0xaaaaaa);
		while (j < (int)len[1])
		{
			printf("put_pixel_textures called\n");
			put_pixel_textures(img, i, j++, var);
			printf("Iterator: %d Comparator: %d\n", j, (int)len[1]);
		}
		while (j < var->map->res_height - 1)
		{
			put_pixel_solid(img, i, j++, 0xaaaaaa);
			printf("Iterator: %d Comparator: %d\n", j, var->map->res_height - 1);
		}
	}
	printf("Pusheamos la imagen a la ventana\n");
	mlx_put_image_to_window(var->mlx, var->win, img[0].img, 0, 0);
	i = -1;
	while (++i < 5 + SPRITE_NUMBER)	
		mlx_destroy_image(var->win, img[i].img);
	free(var->ray_hit);
	free(var->map->wall_start);
	free(var->map->wall_linelength);
	//printf("sigma : %f\n", var->sigma * 180.0 / PI);
	if (var->must_save == 1)
		save_img(var, img[0].img);
	return (0);
}
