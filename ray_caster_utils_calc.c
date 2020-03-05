/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_utils_calc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:39:16 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/03/05 12:56:12 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cast_till_wall(t_vars *var, int *cell, double *dist)
{
	while (var->map->val[cell[1]][cell[0]] != '1')
	{
		if (dist[2] < dist[3])
		{
			dist[2] += fabs(dist[0]);
			cell[0] += (int)dist[5];
			var->side = 'h';
		}
		else
		{
			dist[3] += fabs(dist[1]);
			cell[1] += (int)dist[6];
			var->side = 'v';
		}
	}
}

static void	choose_a_side(t_vars *var, double phi)
{
	if (var->side == 'h' && ((fabs(phi) < PI2 && fabs(phi) > 0.0)
		|| (fabs(phi) > _3PI2 && fabs(phi) < _2PI)))
		var->side = 'w';
	else if (var->side == 'h' && fabs(phi) > PI2 && fabs(phi) < _3PI2)
		var->side = 'e';
	else if (var->side == 'v' && fabs(phi) < PI && fabs(phi) > 0.0)
		var->side = 's';
	else if (var->side == 'v' && fabs(phi) < _2PI && fabs(phi) > PI)
		var->side = 'n';
	else if (var->side == 'h' && (fabs(phi - 0.0) < 10e-7))
		var->side = 'w';
	else if (var->side == 'h' && (fabs(phi - PI) < 10e-7))
		var->side = 'e';
	else if (var->side == 'v' && (fabs(phi - PI2) < 10e7))
		var->side = 's';
	else if (var->side == 'v' && (fabs(phi - _3PI2) < 10e-7))
		var->side = 'n';
}

double		ray_distance(t_vars *var, int col)
{
	double		phi;
	double		dist[7];
	int			map_cell[2];

	phi = var->sigma + atan(tan(FOV / 2.0)
		* (2.0 * col / var->map->res_width - 1.0));
	map_cell[0] = (int)var->x;
	map_cell[1] = (int)var->y;
	if (phi > _2PI || phi < 0.0)
		phi = phi + ((phi < 0) - (phi > 0)) * _2PI;
	if ((fabs(phi - PI2) < 10e-7) || (fabs(phi - _3PI2) < 10e-7))
		dist[0] = (fabs(phi - PI2) < 10e-7) ? INFINITY : -1 * INFINITY;
	else
		dist[0] = 1 / cos(phi);
	if ((fabs(phi - 0.0) < 10e-7) || (fabs(phi - PI) < 10e-7))
		dist[1] = (fabs(phi - 0.0) < 10e-7) ? -1 * INFINITY : INFINITY;
	else
		dist[1] = -1 / sin(phi);
	cuad_calc(var, phi, map_cell, dist);
	cast_till_wall(var, map_cell, dist);
	choose_a_side(var, phi);
	if (var->side == 'w' || var->side == 'e')
	{
		dist[4] = cos(phi - var->sigma) * dist[0] * (map_cell[0] - var->x
			+ (1.0 - dist[5]) / 2.0);
		var->ray_hit[col] = var->y - map_cell[1] - (map_cell[0] - var->x
			+ (1 - dist[5]) / 2.0) * tan(phi);
	}
	else
	{
		dist[4] = cos(phi - var->sigma) * dist[1] * (map_cell[1] - var->y
			+ (1.0 - dist[6]) / 2.0);
		var->ray_hit[col] = var->x - map_cell[0] - (map_cell[1] - var->y
			+ (1 - dist[6]) / 2.0) / tan(phi);
	}
	var->ray_hit[col] -= floor(var->ray_hit[col]);
	return (dist[4]);
}
