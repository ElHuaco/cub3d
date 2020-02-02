/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 12:52:52 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/02 23:01:15 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		check_map_error(char **map)
{
	//Error si no hay un N,S,W,E ó más de uno
	//Error si no hay R && NO && SO && WE && EA
	//Erro si no está rodeado de muros
	//Error si hay un elemento distinto de 0,1,2,N,S,E,W
	//Error si filas no del mismo tamaño
}

static int		init_map_textures(t_maps *map, char **lines)
{
	char	**buff;
	int		i;

	buff = ft_split(lines[0], ' ');
	map->res_height = ft_atoi(buff[2]);
	map->res_width = ft_atoi(buff[1]);
	free(buff);
	map->textures = malloc(sizeof(char *) * (5 + SPRITE_NUMBER));
	i = 0;
	while (*(*(buff = ft_split(lines[i + 1], ' '))) != 'F')
	{
		map->textures[i] = buff[1];
		free(buff);
		i++;
	}
	map->textures[i] = 0;
	map->floor_color = ft_atoi(buff[1]) * 65536 + ft_atoi(ft_strchr(buff[1]) + 1)
		* 256 + ft_atoi(strrchr(buff[1]));
	free(buff);
	buff = ft_split(lines[i++], ' ');
	map->ceiling_color = ft_atoi(buff[1]) * 65536 + ft_atoi(ft_strchr(buff[1]) + 1)
		* 256 + ft_atoi(strrchr(buff[1]));
	free(buff);
	return(i + 2);
}

static void		init_player_map_param(t_maps *map, t_vars *var, char **lines)
{
	char	*p;
	int		n;
	int		i;

	n = ft_arrlen(lines);
	map->val = malloc(sizeof(char *) * (n + 1));
	i = -1;
	while (i++ < n)
		map->val[i] = lines[i];
	map->val[i] = 0;
	map->height = n;
	map->width = ft_strlen(map[0]);
	i = -1;
	while ((i++ < n) && !p)
	{
		if((p = ft_strchr(map->val[i], 'W') || (p = ft_strchr(map->val[i], 'E'))
			|| (p = ft_strchr(map->val[i], 'N'))
			|| (p = ft_strchr(map->val[i], 'S'))))
		{
			var->y = i;
			var->x = p - map->val[i];
		}
	}
	var->sigma = (*p == 'E') + 180 * (*p == 'W')
		+ 90 * (*p == 'N') + 270 * (*p == 'S');
}

static t_maps	read_cub_file(char **argv, t_vars *var)
{
	int		fd;
	char	*line;
	char	**map;
	t_maps	result;
	int		i;

	if ((fd = open("./map.cub", O_RDONLY)) == -1)
	{
		perror("Error: open function call failed.");
		exit(1);
	}
	i = -1;
	while ((get_next_line(fd, &line)) > 0)
		map[i++] = line;
	if (check_map_error(map))
	{
		perror("Error: wrong cub file format.\n");
		exit (1);
	}
	i = init_map_textures(&result, map);
	init_player_map_param(&result, var, map + i);
	return (result);
}

int				main(int argc, char **argv)
{
	t_vars	var;
	t_maps	map;

	if (((argc == 3) && (argv[2] != "--save")) || (argc == 1) || (argc > 3))
	{
		perror("Error: wrong argument format.\n");
		exit(1);
	}
	map = read_cub_file(argv, &var);
	var.map = &map;
	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	mlx_loop_hook(var.mlx, ray_caster, &var);
	mlx_hook(var.win, 2, 1L<<0, camera_update, &var);
	mlx_hook(var.win, 17, 0, x_close, &var);
	mlx_loop(var.mlx);
	return (0);
}
