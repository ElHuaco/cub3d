/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 12:52:52 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/04 17:23:30 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		check_map_error(char **map)
{
	int		player_pos;
	int		i[5];

	i[1] = ft_strlen(map[SPRITE_NUMBER + 7]);
	player_pos = 0;
	i[2] = ft_arrlen(map);
	i[4] = SPRITE_NUMBER + 7;
	i[0] = i[4] - 1;
	while (++i[0] < i[2])
	{
//ft_printf("\t\tCHECKEANDO LINEA %d\n", i[0]);
		if ((ft_strchr(map[i[0]], 'N')) || (ft_strchr(map[i[0]], 'S'))
			|| (ft_strchr(map[i[0]], 'W')) || (ft_strchr(map[i[0]], 'E')))
			player_pos++;
		if ((int)ft_strlen(map[i[0]]) != i[1])
			return (1);	
//ft_printf("Longitud línea %d correcta\n", i[0]);
		i[3] = 0;
		while (map[i[0]][i[3]])
		{
			if ((map[i[0]][i[3]] != 'W') && (map[i[0]][i[3]] != 'E')
				&& (map[i[0]][i[3]] != 'N') && (map[i[0]][i[3]] != 'S')
			   	&& (map[i[0]][i[3]] != '0') && (map[i[0]][i[3]] != '1')
				&& (map[i[0]][i[3]] != '2') && (map[i[0]][i[3]] != ' '))
			{
//ft_printf("%d, %d: El caracter %d es extraño\n", i[0], i[3], map[i[0]][i[3]]);
				return (1);
			}
			if (((i[0] == i[4]) || (i[0] == i[2] - 1))
					&& ((map[i[0]][i[3]] != '1') && (map[i[0]][i[3]] != ' ')))
			{
//ft_printf("Caracter mal en %d, %d: %c\n", i[0], i[3], map[i[0]][i[3]]);
				return (1);
			}
			else if (((i[0] != i[4]) && (i[0] != i[2] - 1)) && ((ft_strchr(map[i[0]], '1') != map[i[0]])
				|| (ft_strrchr(map[i[0]], '1') != map[i[0]] + i[1] - 1)))
			{
//int a = (ft_strchr(map[i[0]], '1') == map[i[0]]);
//int b = (ft_strrchr(map[i[0]], '1') == map[i[0]] + i[1] - 1);
//ft_printf("Muros mal: \n\tMuro Inicial: %d, Muro final: %d\n", a, b);
				return (1);
			}
			i[3] += 1;
		}
//ft_printf("Muros línea %d correctos\n", i[0]);
	}
	if (player_pos != 1)
		return (1);
//ft_printf("Solo un señalizador pos inicial\n");
	return (0);
}

static int		init_map_textures(t_maps *map, char **lines)
{
	char	**buff;
	int		i;

	buff = ft_split(lines[0], ' ');
	map->res_height = ft_atoi(buff[2]);
	map->res_width = ft_atoi(buff[1]);
ft_printf("Map res: %d, %d\n", map->res_width, map->res_height);
	free(buff);
	map->textures = malloc(sizeof(char *) * (4 + SPRITE_NUMBER + 1));
	i = 0;
	while ((*(*(buff = ft_split(lines[i + 1], ' ')))) != 'F')
	{
		map->textures[i] = buff[1];
ft_printf("Textura %d: %s\n", i, map->textures[i]);
		free(buff);
		i++;
	}
	map->textures[i] = 0;
	map->floor_color = ft_atoi(buff[1]) * 65536 + ft_atoi(ft_strchr(buff[1], ',')
		+ 1) * 256 + ft_atoi(ft_strrchr(buff[1], ','));
ft_printf("Color suelo: %d\n", map->floor_color);
	free(buff);
	buff = ft_split(lines[i + 2], ' ');
	map->ceiling_color = ft_atoi(buff[1]) * 65536 + ft_atoi(ft_strchr(buff[1], ',')
			+ 1) * 256 + ft_atoi(ft_strrchr(buff[1], ','));
ft_printf("Color techo: %d\n", map->ceiling_color);
	free(buff);
	return(i + 3);
}

static void		init_player_map_param(t_maps *map, t_vars *var, char **lines)
{
	int		n;
	int		i;
	int		j;

	n = ft_arrlen(lines);
	map->val = malloc(sizeof(char *) * (n + 1));
	i = -1;
	while (++i < n)
	{
		//Saltar espacios
		map->val[i] = skip_spaces(lines[i]);
ft_printf("map->val[%d]: %s\n", i, map->val[i]);
	}
	map->val[i] = 0;
	map->height = n;
	map->width = ft_strlen(map->val[0]);
ft_printf("Map dimensions: %d, %d\n", map->width, map->height);
	i = -1;
	while (++i < n)
	{
		j = -1;
		while (++j < map->width)
		{
			if (((map->val[i][j] == 'W')) || (map->val[i][j] == 'E')
				|| (map->val[i][j] == 'N') || (map->val[i][j] == 'S'))
			{
				var->x = (double)j;
				var->y = (double)i;
printf("var->x: %f var->y: %f\n", var->x, var->y);
				break;
			}
		}
	}
	j = (int)var->x;
	i = (int)var->y;
	var->sigma = 0.0 * (map->val[i][j] == 'E') + 90.0 * (map->val[i][j] == 'N')
		+ 180.0 * (map->val[i][j] == 'W')	+ 270.0 * (map->val[i][j] == 'S');
printf("Player initial var: %f, %f with %f degrees\n", var->x, var->y, var->sigma);
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
		map[++i] = line;
	map[++i] = 0;
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
	/*var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	mlx_loop_hook(var.mlx, ray_caster, &var);
	mlx_hook(var.win, 2, 1L<<0,ft_printf("%s\n", map[i[0]]); camera_update, &var);
	mlx_hook(var.win, 17, 0, x_close, &var);
	mlx_loop(var.mlx);*/
	return (0);
}
