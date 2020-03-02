/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:14:43 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/03/02 12:44:59 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			digit_number(int n, int basesize)
{
	int i;

	if (n < 0)
		n *= -1;
	i = 1;
	while ((n / basesize) > 0)
		i++;
	return (i);
}

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

char	**skip_spaces(char **lines)
{
	char	**lines_skiped_sp;
	int		arr_size;
	int		str_size;
	int		i;
	int		j;

	arr_size = ft_arrlen(lines);
	str_size = ft_strlen(lines[0]);
	lines_skiped_sp = malloc(sizeof(char *) * (arr_size + 1));
	lines_skiped_sp[arr_size] = 0;
	i = -1;
	while (i++ < arr_size)
	{
		lines_skiped_sp[i] = malloc(sizeof(char) * (str_size / 2));
		lines_skiped_sp[i][str_size / 2] = 0;
		j = -1;
		while (j++ < str_size)
		{
			if (lines[i][j] != ' ')
				lines_skipped_sp[i][j / 2] = lines[i][j];
		}
	}
	full_free(lines);
	return(lines_skiped_sp);
}
