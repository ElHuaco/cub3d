/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_calc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:13:34 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/06/30 12:47:18 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		calc_sprite_bounds(t_vars *var, int *len, double *project)
{
	double		trans;

	trans = fabs(var->map->res_height / project[1]);
	len[2] = (int)(0.5 * (var->map->res_height - trans));
	if (len[2] < 0)
		len[2] = 0;
	len[3] = (int)(0.5 * (var->map->res_height + trans));
	if (len[3] >= var->map->res_height)
		len[3] = var->map->res_height - 1;
	len[0] = (int)(0.5 * (var->map->res_width * (1 + project[0] / project[1])
		- trans));
	if (len[0] < 0)
		len[0] = 0;
	len[1] = (int)(0.5 * (var->map->res_width * (1 + project[0] / project[1])
		+ trans));
	if (len[1] >= var->map->res_width)
		len[1] = var->map->res_width - 1;
}

t_sprites	duplicate_sprite(t_sprites src)
{
	t_sprites	dup;

	dup.x = src.x;
	dup.y = src.y;
	dup.dist = src.dist;
	return (dup);
}

void		replace_sprite(t_sprites *dst, t_sprites *src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->dist = src->dist;
}
