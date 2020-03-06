/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_caster.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:39:48 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/03/06 15:20:05 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_map_sprites(t_vars *var)
{
	t_sprites	*sprites;
	int			n;
	int			i;
	int			j;

	n = 0;
	i = -1;
	while (++i < var->map->height)
	{
		j = -1;
		while (var->map[i][++j])
		{
			if (var->map[i][j] == '2')
				n++;
		}
	}
	sprites = malloc(sizeof(struct s_sprites) * n);
	var->map->sprites = sprites;
	return (n);
}

static void	find_sprite_pos_and_dist(t_vars *var)
{
	int		i;
	int		j;
	int		k;

	k = -1;
	i = -1;
	while (++i < var->map->height)
	{
		j = -1;
		while (var->map[i][++j])
		{
			if (var->map[i][j] == '2')
			{
				var->map->sprites[++k].x = j + 0.5;
				var->map->sprites[++k].y = i + 0.5;
				var->map->sprites[k].distance =
					pow(var->x - j - 0.5, 2) + pow(var->y - i - 0.5, 2);
			}
		}
	}
	i = -1;
	k = -1;//BUbble sort sprites segun distancia
	while (++i < var->map->sprite_number - 1)
	{
		if (var->map->sprites[++k].distance > var->map->sprites[k + 1].distance)
			j = var->map->(sprites + k);
			var->map->(sprite + k + 1)
	}
}

void		sprite_caster(t_vars *var, t_imgs *img)
{
	var->map->sprite_number = count_map_sprites(var);
	find_sprite_pos_and_dist(var);
}
