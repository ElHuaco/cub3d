/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:14:43 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/04 18:27:42 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		find_player_pos(t_maps *map, t_vars *var)
{
	int i;
	int	j;
	int n;

	n = ft_arrlen(map->val);
	i = -1;
	while (++i < n)
	{
		j = -1;
		while (++j < map->width)
		{
			if (is_player_pos(map->val[i][j]))
			{
				var->x = (double)j;
				var->y = (double)i;
				break ;
			}
		}
	}
}
