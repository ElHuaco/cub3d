/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 19:22:53 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/11 12:05:42 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			camera_update(int key, t_vars *var)
{
	//Modifica sigma, x, y, para llamar a ray_caster de nuevo
	if (key == ESC)
		return (x_close(var));
	else if (key == RIGHT || key == D)
		var->sigma -= 0.1;
	else if (key == LEFT || key == A)
		var->sigma += 0.1;
	else if (key == UP || key == W || key == S || key == DOWN)
	{
		var->x += cosf(var->sigma + 180.0 * (key == S || key == DOWN)) * 0.1;
		var->y += sinf(var->sigma + 180.0 * (key == S || key == DOWN)) * 0.1;
	}
	if (var->sigma >= 360.0)
		var->sigma -= 360.0;
	else if (var->sigma <= -360.0)
		var->sigma += 360.0;
	ray_caster(var);
	return (0);
}

int			x_close(t_vars *var)
{
	full_free((void **)var->map->textures, 4 + SPRITE_NUMBER);
	full_free((void **)var->map->val, var->map->height);
	exit(0);
	return (0);
}
