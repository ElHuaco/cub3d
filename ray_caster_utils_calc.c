/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_utils_calc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:39:16 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/05 17:46:08 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	first_cuad_calc(t_vars *var, int *cell, double **dist, int **step)
{
	*dist[2] = fabs(*dist[0]) * (cell[0] + 1.0 - var->x);
	*step[0] = 1;
	*dist[3] = fabs(*dist[1]) * (cell[1] + 1.0 - var->y);
	*step[1] = 1;	
}

static void	first_cuad_calc(t_vars *var, int *cell, double **dist, int **step)
{
	*dist[2] = fabs(*dist[0]) * ( -1 * cell[0] + var->x);
	*step[0] = -1;
	*dist[3] = fabs(*dist[1]) * (cell[1] + 1.0 - var->y);
	*step[1] = 1;	
}

static void	first_cuad_calc(t_vars *var, int *cell, double **dist, int **step)
{
	*dist[2] = fabs(*dist[0]) * ( -1 * cell[0] +  var->x);
	*step[0] = -1;
	*dist[3] = fabs(*dist[1]) * (-1 * cell[1] + var->y);
	*step[1] = -1;	
}

static void	first_cuad_calc(t_vars *var, int *cell, double **dist, int **step)
{
	*dist[2] = fabs(*dist[0]) * (cell[0] + 1.0 - var->x);
	*step[0] = 1;
	*dist[3] = fabs(*dist[1]) * (-1 * cell[1] + var->y);
	*step[1] = -1;	
}

double		ray_distance(t_vars *var, int col)
{
	double		phi;
	double		dist[5];
	int			step[2];
	int			map_cell[2];
	char		side;
	
	phi = var->sigma - FOV / 2 + (FOV / WIN_WIDTH) * i;
	dist[0] = 1.0 / cosf(phi);
	dist[1] = 1.0 / senf(phi);
	map_cell[0] = (int)var->x;
	map_cell[1] = (int)var->y;
	if (phi >= 360.0)
		phi -= 360.0;
	if ((phi > 0.0) && (phi < 90.0))
		first_cuad_calc(var, map_cell, &dist, &step);
	else if ((phi > 90.0) && (phi < 180.0))
		second_cuad_calc(var, map_cell, &dist, &step);
	else if ((phi > 180.0) && (phi < 270.0))
		third_cuad_calc(var, map_cell, &dist, &step);
	else if ((phi > 270.0) && (phi < 360.0))
		fourth_cuad_calc(var, map_cell, &dist, &step);
	while (var->map->val[map_cell[1]][map_cell[0]] != '1')
	{
		if (dist[2] > dist[3])
		{
			dist[2] += fabs(dist[0]);
			map_cell[0] += step[0];
			side = 'h';
		}
		else
		{
			dist[3] += fabs(dist[1]);
			map_cell[1] += step[1];
			side = 'v';
		}
	}
	if (side == 'h')
		dist[4] = dist[0] * (map_cell[0] - var->x + (1.0 - step[0]) / 2.0);
	else if (side == 'v')

	return (dist[4]);
}

