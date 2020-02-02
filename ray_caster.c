/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 20:00:13 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/02 22:54:21 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ray_caster(t_vars *var)
{
	//Crea la imagen según sigma, x, y, map values, map textures
}

int				camera_update(int key, t_vars *var)
{
	//Modifica sigma, x, y, para llamar a ray_caster de nuevo
}

int		x_close(t_vars *var)
{
	if (var->map->textures)
		free(var->map->textures);
	if (var->map->val)
		free(var->map->val);
	exit(0);
	return (0);
}
