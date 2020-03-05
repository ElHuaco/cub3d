/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_utils_calc3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:47:25 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/03/05 12:53:42 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		phi_zero_calc(t_vars *var, int *map_cell, double *dist)
{
	dist[2] = map_cell[0] + 1.0 - var->x;
	dist[5] = 1.0;
	dist[3] = INFINITY;
	dist[6] = 0.0;
}

void		phi_pi_half_calc(t_vars *var, int *map_cell, double *dist)
{
	dist[2] = INFINITY;
	dist[5] = 0.0;
	dist[3] = map_cell[1] + 1.0 - var->y;
	dist[6] = -1.0;
}

void		phi_pi_calc(t_vars *var, int *map_cell, double *dist)
{
	dist[2] = -1 * map_cell[0] + var->x;
	dist[5] = -1.0;
	dist[3] = INFINITY;
	dist[6] = 0.0;
}

void		phi_three_pi_half_calc(t_vars *var, int *map_cell, double *dist)
{
	dist[2] = INFINITY;
	dist[5] = 0.0;
	dist[3] = -1 * map_cell[1] + var->y;
	dist[6] = 1.0;
}
