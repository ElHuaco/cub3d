/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_utils_calc2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:37:35 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/10 09:13:32 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	first_cuad_calc(t_vars *var, int *cell, double (*dist)[7])
{
	*dist[2] = fabs(*dist[0]) * (cell[0] + 1.0 - var->x);
	*dist[5] = 1;
	*dist[3] = fabs(*dist[1]) * (cell[1] + 1.0 - var->y);
	*dist[6] = 1;
}

static void	second_cuad_calc(t_vars *var, int *cell, double (*dist)[7])
{
	*dist[2] = fabs(*dist[0]) * ( -1 * cell[0] + var->x);
	*dist[5] = -1;
	*dist[3] = fabs(*dist[1]) * (cell[1] + 1.0 - var->y);
	*dist[6] = 1;	
}

static void	third_cuad_calc(t_vars *var, int *cell, double (*dist)[7])
{
	*dist[2] = fabs(*dist[0]) * ( -1 * cell[0] +  var->x);
	*dist[5] = -1;
	*dist[3] = fabs(*dist[1]) * (-1 * cell[1] + var->y);
	*dist[6] = -1;	
}

static void	fourth_cuad_calc(t_vars *var, int *cell, double (*dist)[7])
{
	*dist[2] = fabs(*dist[0]) * (cell[0] + 1.0 - var->x);
	*dist[5] = 1;
	*dist[3] = fabs(*dist[1]) * (-1 * cell[1] + var->y);
	*dist[6] = -1;	
}
void		cuad_calc(t_vars *var, double phi, int *map_cell, double (*dist)[7])
{
	if ((phi > 0.0) && (phi < 90.0))
		first_cuad_calc(var, map_cell, dist);
	else if ((phi > 90.0) && (phi < 180.0))
		second_cuad_calc(var, map_cell, dist);
	else if ((phi > 180.0) && (phi < 270.0))
		third_cuad_calc(var, map_cell, dist);
	else if ((phi > 270.0) && (phi < 360.0))
		fourth_cuad_calc(var, map_cell, dist);
	else if (phi == 0.0)
		phi_zero_calc(var, map_cell, dist);
	else if (phi == 90.0)
		phi_pi_half_calc(var, map_cell, dist);
	else if (phi == 180.0)
		phi_pi_calc(var, map_cell, dist);
	else if (phi == 270.0)
		phi_three_pi_half_calc(var, map_cell, dist);
}
