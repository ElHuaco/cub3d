/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_utils_calc3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:47:25 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/06 14:54:00 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		phi_zero_calc(t_vars *var, int *map_cell, double **dist)
{
	*dist[2] = fabs(*dist[0]) * (cell[0] + 1.0 - var->x);
	*dist[5] = 1;
	*dist[3] = INFINITY;
	*dist[6] = 0;
}

void		phi_pi_half_calc(t_vars *var, int *map_cell, double **dist)
{
	*dist[2] = INFINITY;
	*dist[5] = 0;
	*dist[3] = fabs(*dist[1]) * (cell[1] + 1.0 - var->y);
	*dist[6] = 1;	
}

void		phi_pi_calc(t_vars *var, int *map_cell, double **dist)
{
	*dist[2] = fabs(*dist[0]) * ( -1 * cell[0] +  var->x);
	*dist[5] = -1;
	*dist[3] = INFINITY;
	*dist[6] = 0;	
}

void		phi_three_pi_half_calc(t_vars *var, int *map_cell, double **dist)
{
	*dist[2] = INFINITY;;
	*dist[5] = 0;
	*dist[3] = fabs(*dist[1]) * (-1 * cell[1] + var->y);
	*dist[6] = -1;	
}
