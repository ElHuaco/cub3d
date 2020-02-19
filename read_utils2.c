/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:14:43 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/18 15:41:22 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		full_free(void **buff, int n)
{
	int i;

	if (buff)
	{
		i = -1;
		while (++i < n && buff[i])
		{
			if (buff[i])
				free(buff[i]);
		}
		free(buff);
	}
}

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
				var->x = (double)j + 0.5;
				var->y = (double)i + 0.5;
				break ;
			}
		}
	}
	j = (int)var->x;
	i = (int)var->y;
	var->sigma = 0.0 * (map->val[i][j] == 'E') + PI2 * (map->val[i][j] == 'N')
		+ PI * (map->val[i][j] == 'W') + _3PI2 * (map->val[i][j] == 'S');
	map->val[i][j] = '0';
}

void	save_img(t_vars *var, void *img)
{
	//Guarda la imagen en bpp
	var->must_save = 0;
	img = 0;
}
