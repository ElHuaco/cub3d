/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_utils_calc2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:37:35 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/03/05 12:54:34 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	first_cuad_calc(t_vars *var, int *cell, double *dist)
{
	dist[2] = fabs(dist[0]) * (cell[0] + 1.0 - var->x);
	dist[5] = 1;
	dist[3] = fabs(dist[1]) * (-1 * cell[1] + var->y);
	dist[6] = -1;
}

static void	second_cuad_calc(t_vars *var, int *cell, double *dist)
{
	dist[2] = fabs(dist[0]) * (-1 * cell[0] + var->x);
	dist[5] = -1;
	dist[3] = fabs(dist[1]) * (-1 * cell[1] + var->y);
	dist[6] = -1;
}

static void	third_cuad_calc(t_vars *var, int *cell, double *dist)
{
	dist[2] = fabs(dist[0]) * (-1 * cell[0] + var->x);
	dist[5] = -1;
	dist[3] = fabs(dist[1]) * (cell[1] + 1.0 - var->y);
	dist[6] = 1;
}

static void	fourth_cuad_calc(t_vars *var, int *cell, double *dist)
{
	dist[2] = fabs(dist[0]) * (cell[0] + 1.0 - var->x);
	dist[5] = 1;
	dist[3] = fabs(dist[1]) * (cell[1] + 1.0 - var->y);
	dist[6] = 1;
}

void		cuad_calc(t_vars *var, double phi, int *map_cell, double *dist)
{
	if ((phi > 0.0) && (phi < PI2))
		first_cuad_calc(var, map_cell, dist);
	else if ((phi > PI2) && (phi < PI))
		second_cuad_calc(var, map_cell, dist);
	else if ((phi > PI) && (phi < _3PI2))
		third_cuad_calc(var, map_cell, dist);
	else if ((phi > _3PI2) && (phi < _2PI))
		fourth_cuad_calc(var, map_cell, dist);
	else if ((phi - 0.0) < 10e-7)
		phi_zero_calc(var, map_cell, dist);
	else if (fabs(phi - PI2) < 10e-7)
		phi_pi_half_calc(var, map_cell, dist);
	else if (fabs(phi - PI) < 10e-7)
		phi_pi_calc(var, map_cell, dist);
	else if (fabs(phi - _3PI2) < 10e-7)
		phi_three_pi_half_calc(var, map_cell, dist);
}
