/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_utils_calc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:39:16 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/07 16:55:47 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cast_till_wall(t_vars *var, int **map_cell, double **dist, char *s)
{
	while (var->map->val[*map_cell[1]][*map_cell[0]] != '1')
	{
		if (*dist[2] > *dist[3])
		{
			*dist[2] += fabs(*dist[0]);
			*map_cell[0] += *dist[5];
			*s = 'h';
		}
		else
		{
			*dist[3] += fabs(*dist[1]);
			map_cell[1] += *dist[6];
			*s = 'v';
		}
	}
}

double		ray_distance(t_vars *var, int col)
{
	double		phi;
	double		dist[7];
	int			map_cell[3];
	char		side;

	phi = var->sigma - FOV / 2 + (FOV / WIN_WIDTH) * i;
	dist[0] = 1.0 / cosf(phi);
	dist[1] = 1.0 / senf(phi);
	map_cell[0] = (int)var->x;
	map_cell[1] = (int)var->y;
	if (phi >= 360.0)
		phi -= 360.0;
	cuad_calc(var, phi, map_cell, &dist);
	cast_till_wall(var, &map_cell, &dist, &side);
	if (side == 'h')
		dist[4] = dist[0] * (map_cell[0] - var->x + (1.0 - step[0]) / 2.0);
	else if (side == 'v')
		dist[4] = dist[1] * (map_cell[1] - var->y + (1.0 - step[1]) / 2.0);
	return (dist[4]);
}

