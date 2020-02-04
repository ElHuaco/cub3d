/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 12:52:52 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/04 12:53:27 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		check_map_error(char **map)
{
	int		player_pos;
	int		i[4];

	i[1] = ft_strlen(map[SPRITE_NUMBER + 7]);
	player_pos = 0;
	i[2] = ft_arrlen(map);
	i[0] = SPRITE_NUMBER + 6;
	while (++i[0] < i[2])
	{
ft_printf("\t\tCHECKEANDO LINEA %d\n", i[0]);
		if ((ft_strchr(map[i[0]], 'N')) || (ft_strchr(map[i[0]], 'S'))
			|| (ft_strchr(map[i[0]], 'W')) || (ft_strchr(map[i[0]], 'E')))
			player_pos++;
		if ((int)ft_strlen(map[i[0]]) != i[1])
			return (1);	
ft_printf("Longitud línea %d correcta\n", i[0]);
		i[3] = -1;
		while (map[i[0]][i[3]++])
		{
			if ((map[i[0]][i[3]] != 'W') && (map[i[0]][i[3]] != 'E')
				&& (map[i[0]][i[3]] != 'N') && (map[i[0]][i[3]] != 'S')
			   	&& (map[i[0]][i[3]] != '0') && (map[i[0]][i[3]] != '1')
				&& (map[i[0]][i[3]] != '2'))
				return (1);
ft_printf("No hay caracteres extraños en línea %d\n", i[0]);
			if (((i[0] == 0) || (i[0] == i[2] - 1)) && (map[i[0]][i[3]] != '1'))
			{
				ft_printf("Caracter mal en %d, %d: %c\n", i[0], i[3], map[i[0]][i[3]]);
				return (1);
			}
			else if (((i[0] != 0) && (i[0] != i[2] - 1)) && ((ft_strchr(map[i[0]], '1') != map[i[0]])
				|| (ft_strrchr(map[i[0]], '1') != map[i[0]] + i[1] - 1)
				|| (ft_strchr(map[i[0]] + 1, '1') != ft_strrchr(map[i[0]], '1'))))
			{
				ft_printf("Muros mal: \n\tMuro Inicial: %p, Muro final: %p, Muro a mitad %p\n", (ft_strchr(map[i[0]], '1')),  (ft_strrchr(map[i[0]], '1')) , (ft_strchr(map[i[0]] + 1, '1')));
				return (1);
			}
		}
ft_printf("Muros línea %d correctos\n", i[0]);
	}
	if (player_pos != 1)
		return (1);
	ft_printf("Solo un señalizador pos inicial\n");
	return (0);
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
	map->floor_color = ft_atoi(buff[1]) * 65536 + ft_atoi(ft_strchr(buff[1], ',')
		+ 1) * 256 + ft_atoi(ft_strrchr(buff[1], ','));
	free(buff);
	buff = ft_split(lines[i++], ' ');
	map->ceiling_color = ft_atoi(buff[1]) * 65536 + ft_atoi(ft_strchr(buff[1], ',')
			+ 1) * 256 + ft_atoi(ft_strrchr(buff[1], ','));
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
	map->width = ft_strlen(map->val[0]);
	i = -1;
	while ((i++ < n) && !p)
	{
		if (((p = ft_strchr(map->val[i], 'W')) || (p = ft_strchr(map->val[i], 'E'))
			|| (p = ft_strchr(map->val[i], 'N'))
			|| (p = ft_strchr(map->val[i], 'S'))))
		{
			var->y = i;
			var->x = p - map->val[i];
		}
	}
	var->sigma = 0 * (*p == 'E') + 90 * (*p == 'N')
		+ 180 * (*p == 'W') + 270 * (*p == 'S');
}

static t_maps	read_cub_file(char **argv, t_vars *var)
{
	int		fd;
	char	*line;
	char	**map;
	t_maps	result;
	int		i;

	if (((fd = open(argv[1], O_RDONLY)) == -1) || !(map = malloc(sizeof(char *) * 30)))
		exit(1);
	i = -1;
	while ((get_next_line(fd, &line)) > 0)
	{
		map[++i] = line;
		//Quitar lo espacios de los map[i]
	}
	map[i] = 0;
	close(fd);
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

	if (((argc == 3) && !(ft_strcmp(argv[2], "--save"))) || (argc == 1) || (argc > 3))
	{
		perror("Error: wrong argument format.\n");
		exit(1);
	}
	map = read_cub_file(argv, &var);
	var.map = &map;
	ft_printf("map res: %d %d; map height: %d; map width: %d\n", var.map->res_height, var.map->res_width
		,  var.map->height, var.map->width);
	int i = -1;
	while (var.map->val[i++])
		ft_printf("%s\n", var.map->val[i]);
	ft_printf("map floor color: %d; map ceiling color: %d\n", var.map->floor_color,  var.map->ceiling_color);
	i = -1;
	while (var.map->textures[i++])
		ft_printf("%s\n", var.map->textures[i]);
	/*var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	mlx_loop_hook(var.mlx, ray_caster, &var);
	mlx_hook(var.win, 2, 1L<<0,ft_printf("%s\n", map[i[0]]); camera_update, &var);
	mlx_hook(var.win, 17, 0, x_close, &var);
	mlx_loop(var.mlx);*/
	return (0);
}
