/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 19:22:53 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/11 16:04:27 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			camera_update(int key, t_vars *var)
{
	//double	n_y;
	//double	n_x;

	//Modifica sigma, x, y, para llamar a ray_caster de nuevo
	if (key == ESC)
		return (x_close(var));
	else if (key == RIGHT || key == D)
		var->sigma += 0.05;
	else if (key == LEFT || key == A)
		var->sigma -= 0.05;
	else if (key == UP || key == W || key == S || key == DOWN)
	{
		var->y -= sin(var->sigma + PI * (key == S || key == DOWN)) * 0.05;
		var->x += cos(var->sigma + PI * (key == S || key == DOWN)) * 0.05;
	}
	if (var->sigma >= _2PI)
		var->sigma -= _2PI;
	else if (var->sigma <= -1* _2PI)
		var->sigma += _2PI;
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
