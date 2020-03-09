/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_caster.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:39:48 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/03/09 13:09:05 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_map_sprites(t_vars *var)
{
	t_sprites	*sprites;
	int			n;
	int			i;
	int			j;

	n = 0;
	i = -1;
	while (++i < var->map->height)
	{
		j = -1;
		while (var->map[i][++j])
		{
			if (var->map[i][j] == '2')
				n++;
		}
	}
	sprites = malloc(sizeof(struct s_sprites) * n);
	var->map->sprites = sprites;
	return (n);
}

static void	find_sprite_pos_and_dist(t_vars *var)
{
	int		i;
	int		j;
	int		k;

	k = -1;
	i = -1;
	while (++i < var->map->height)
	{
		j = -1;
		while (var->map[i][++j])
		{
			if (var->map[i][j] == '2')
			{
				var->map->sprites[++k].x = j + 0.5;
				var->map->sprites[k].y = i + 0.5;
				var->map->sprites[k].distance =
					pow(var->x - j - 0.5, 2) + pow(var->y - i - 0.5, 2);
			}
		}
	}
}

static void	sort_sprites_by_distance(t_vars *var)
{
	int			i;
	int			j;
	int			k;
	t_sprites	temp;

	k = 0;
	i = -1;
	while (++i < var->map->sprite_number - 1)
	{
		j = -1;
		while (++j < var->map->sprite_number - 1)
		{
			if ((var->map->sprites[j].distance
				> var->map->sprites[i].distance) && (j < i))
			{
				temp = var->map->sprites[i];
				var->map->sprites[j] = var->map->sprites[i];
				var->map->sprites[i] = temp;
			}
		}
	}
}

static void	put_sprite_img(t_vars *var, int *len, double *pr, t_imgs *img)
{
	char	*dst;
	int		corresp_sprel_coord[2];
	int		col;
	int		row;

	col = len[0] - 1;
	while (++col < len[1])
	{
		corresp_sprel_coord[0] = (col - len[0]) * img[5].img_w
			/ fabs(var->map->res_height / pr[1]);
	 	if (pr[1] > 0 && col > 0 && col < var->map->res_width
				&& pr[1] < var->ray_distance[col])
		{
			row = len[2] - 1;
			while (++row < len[3])
			{
				corresp_sprel_coord[1] = (row - len[2]) * img[5].img_h
					/ fabs(var->map->res_height / pr[1]);
				dst = img[0].addr + corresp_sprel_coord[1] * img[0].ll
					+ corresp_sprel_coord[0] * (img[0].bpp / 8);
	*(unsigned int *)dst = *(unsigned int *)(img[5].addr
		+ corresp_sprel_coord[1] * img[5].ll
		+ corresp_sprel_coord[0] * (img[5].bpp / 8));
}

void		sprite_caster(t_vars *var, t_imgs *img)
{
	int		i;
	double	project[2];
	int		len[4];

	var->map->sprite_number = count_map_sprites(var);
	find_sprite_pos_and_dist(var);
	sort_sprites_by_distance(var);
	i = -1;
	while (++i < var->map->sprite_number - 1)
	{
		var->map->sprites[i].x -= var->x;
		var->map->sprites[i].y -= var->y;
		project[0] = sin(var->sigma) * var->map->sprites[i].x
			- cos(var->sigma) * var->map->sprites[i].y;
		project[1] = cos(var->sigma) * var->map->sprites[i].x
			+ sin(var->sigma) * var->map->sprites[i].y;
		calc_sprite_bounds(var, i, len);
		put_sprite_img(var, len, project, img);
		while (++col < len[1])
		{
					put_sprite_img(var, len, project, img);
		}
	}
}
