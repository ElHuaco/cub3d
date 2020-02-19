/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 19:22:53 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/18 16:24:20 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			camera_update(int key, t_vars *var)
{
	if (key == ESC)
		return (x_close(var));
	else if (key == RIGHT)
		var->sigma += 0.05;
	else if (key == LEFT)
		var->sigma -= 0.05;
	else if (key == UP || key == W || key == S || key == DOWN
		|| key == A || key == D)
	{
		var->y -= sin(var->sigma + PI * (key == S || key == DOWN)
			+ PI2 * (key == D) - PI2 * (key == A)) * CAM_VEL;
		var->x += cos(var->sigma + PI * (key == S || key == DOWN)
			+ PI2 * (key == D) - PI2 * (key == A)) * CAM_VEL;
		//printf("Nuevas coord serian %f %f\n", var->x, var->y);
		//printf("\tDe celda %d %d: %c\n", (int)var->x, (int)var->y,
		//	var->map->val[(int)var->y][(int)var->x]);
	}
//	printf("Antes update: %f\n", var->sigma * 180.0 / PI);
	if (fabs(var->sigma) > _2PI)
		var->sigma += (var->sigma < 0.0) ? _2PI : -1* _2PI;
//	printf("Despues udpate: %f\n", var->sigma * 180.0 / PI);
	if (var->map->val[(int)var->y][(int)var->x] == '0')
	{
		//printf("Nuevo frame para %f %f\n", var->x, var->y);
		ray_caster(var);
	}
	else
	{
		var->y += sin(var->sigma + PI * (key == S || key == DOWN)
			+ PI2 * (key == D) - PI2 * (key == A)) * CAM_VEL;
		var->x -= cos(var->sigma + PI * (key == S || key == DOWN)
			+ PI2 * (key == D) - PI2 * (key == A)) * CAM_VEL;
		//printf("Volvemos a coord %f %f\n", var->x, var->y);
	}
	return (0);
}

int			x_close(t_vars *var)
{
	full_free((void **)var->map->textures, 4 + SPRITE_NUMBER);
	full_free((void **)var->map->val, var->map->height);
	full_free((void **)var->ray_hit, var->map->res_width);
	exit(0);
	return (0);
}
