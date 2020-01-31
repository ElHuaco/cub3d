/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:33:35 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/01/31 15:46:48 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		check_map_error(char **map)
{
}

static void		init_map_param(t_maps *map, char **lines)
{
}

t_maps			read_cub_file(char **argv, t_vars *var)
{
	int		fd;
	char	*line;
	char	**map;
	t_maps	result;
	int		i;

	if ((fd = open("./map.cub", O_RDONLY)) == -1);
	{
		perror();
		exit(1);
	}
	i = -1;
	while ((get_next_line(fd, &line)) > 0)
		map[i++] = line;
	if (check_map_error(map))
	{
		perror("Error: cub file format"); //cambiar por el personalizado
		exit (1);
	}
	init_map_param(&result, map); //Meter **values, h, w, texturas.
	return (result);
}

void			init_player_map_param(t_maps *map, t_vars *var)
{
	//sigma, x, y iniciales y quitar letras.
}


