/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_utils_calc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:39:16 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/07 20:20:18 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cast_till_wall(t_vars *var, int **map_cell, double **dist)
{
	while (var->map->val[*map_cell[1]][*map_cell[0]] != '1')
	{
		if (*dist[2] > *dist[3])
		{
			*dist[2] += fabs(*dist[0]);
			*map_cell[0] += *dist[5];
			var->side = 'h';
		}
		else
		{
			*dist[3] += fabs(*dist[1]);
			map_cell[1] += *dist[6];
			var->side = 'v';
		}
	}
}

static void	choose_a_side(t_vars *var, double phi)
{
	if (var->side == 'h' && fabs(phi) < 90.0 && fabs(phi) > 270.0)
		var->side == 'w';
	else if (var->side == 'h' && fabs(phi) > 90.0 && fabs(phi) < 270.0)
		var->side == 'e';
	else if (var->side == 'v' && fabs(phi) < 180.0 && fabs(phi) > 0.0)
		var->side == 's';
	else if (var->side == 'v' && fabs(phi) < 360.0 && fabs(phi) > 180.0)
		var->side == 'n';
}

double		ray_distance(t_vars *var, int col)
{
	double		phi;
	double		dist[7];
	int			map_cell[3];

	phi = var->sigma - FOV / 2 + (FOV / (double)var->map->res_width) * i;
	dist[0] = 1.0 / cosf(phi);
	dist[1] = 1.0 / senf(phi);
	map_cell[0] = (int)var->x;
	map_cell[1] = (int)var->y;
	if (phi >= 360.0)
		phi -= 360.0;
	else if (phi <= -360.0)
		phi += 360.0;
	cuad_calc(var, phi, map_cell, &dist);
	cast_till_wall(var, &map_cell, &dist);
	choose_a_side(var, phi);
	if (var->side == 'w' || var->side == 'e')
		dist[4] = dist[0] * (map_cell[0] - var->x + (1.0 - dist[5]) / 2.0);
	else if (var->side == 'n' || var->side == 's')
		dist[4] = dist[1] * (map_cell[1] - var->y + (1.0 - dist[6]) / 2.0);
	return (dist[4]);
}

