/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 20:00:13 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/05 17:20:14 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ray_caster(t_vars *var)
{
	//Crea la imagen según sigma, x, y, map values, map textures
	//	Para cada columna de la ventana x, calcular distancia hasta chocar muro
	//	lanzando un rayo con phi(x), qué lado toca.
	int		i;
	double	phi;
	double	dist[4];
	int		step[2];
	double	len[3];
	//No declaramos mapX, mapY, posX, posY
	i = -1;
	while (++i < WIN_WIDTH)
	{
		len = ray_distance(t_vars *var, i)
	}
	//Si must_save == 1 guarda la imagen y pone must_save == 0
}

int				camera_update(int key, t_vars *var)
{
	//Modifica sigma, x, y, para llamar a ray_caster de nuevo
}

int		x_close(t_vars *var)
{
	if (var->map->textures)
		full_free((void **)var->map->textures, 4 + SPRITE_NUMBER);
	if (var->map->val)
		full_free((void **)var->map->val, var->map->height);
	exit(0);
	return (0);
}

