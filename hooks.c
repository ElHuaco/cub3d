/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 19:22:53 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/03/09 17:26:04 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			camera_update(int key, t_vars *var)
{
	if (key == ESC)
		return (x_close(var));
	else if ((key == RIGHT) || (key == LEFT))
		var->sigma += (key == RIGHT) ? -0.05 : 0.05;
	else if (key == UP || key == W || key == S || key == DOWN
		|| key == A || key == D)
	{
		var->y -= sin(var->sigma + PI * (key == S || key == DOWN)
			+ PI2 * (key == A) - PI2 * (key == D)) * CAM_VEL;
		var->x += cos(var->sigma + PI * (key == S || key == DOWN)
			+ PI2 * (key == A) - PI2 * (key == D)) * CAM_VEL;
	}
	if (fabs(var->sigma) > _2PI)
		var->sigma += (var->sigma < 0.0) ? _2PI : -1 * _2PI;
	if (((var->map->val[(int)var->y][(int)var->x] == '0')
		|| var->map->val[(int)var->y][(int)var->x] == '2')
		&& (var->map->val[(int)(var->y + 0.01)][(int)(var->x + 0.01)] != '1')
		&& (var->map->val[(int)(var->y - 0.01)][(int)(var->x + 0.01)] != '1')
		&& (var->map->val[(int)(var->y + 0.01)][(int)(var->x - 0.01)] != '1')
		&& (var->map->val[(int)(var->y - 0.01)][(int)(var->x - 0.01)] != '1'))
		ray_caster(var);
	else
	{
		var->y += sin(var->sigma + PI * (key == S || key == DOWN)
			+ PI2 * (key == D) - PI2 * (key == A)) * CAM_VEL;
		var->x -= cos(var->sigma + PI * (key == S || key == DOWN)
			+ PI2 * (key == D) - PI2 * (key == A)) * CAM_VEL;
	}
	return (0);
}

int			x_close(t_vars *var)
{
	free(var->map->north);
	free(var->map->south);
	free(var->map->west);
	free(var->map->east);
	free(var->map->sprite);
	full_free((void **)var->map->val, var->map->height);
	exit(0);
	return (0);
}

void		error_exit(char *errstr)
{
	ft_printf("Error\n%s", errstr);
	exit(1);
}
