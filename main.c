/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 12:52:52 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/07 17:08:37 by aleon-ca         ###   ########.fr       */
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
		if (check_player_pos_error(map, i[0], &player_pos))
			return (1);
		if ((int)ft_strlen(map[i[0]]) != i[1])
			return (1);
		i[3] = 0;
		while (map[i[0]][i[3]])
		{
			if (!(is_cub_file_chr(map[i[0]][i[3]])))
				return (1);
			if (check_wall_error(map[i[0]], i))
				return (1);
			i[3] += 1;
		}
	}
	return (0);
}

static int		init_map_textures(t_maps *map, char **lines)
{
	char	**buff;
	int		i;

	buff = ft_split(lines[0], ' ');
	map->res_height = ft_atoi(buff[2]);
	map->res_width = ft_atoi(buff[1]);
	full_free((void **)buff, 3);
	map->textures = malloc(sizeof(char *) * (4 + SPRITE_NUMBER + 1));
	i = 0;
	while ((*(*(buff = ft_split(lines[++i], ' ')))) != 'F')
	{
		map->textures[i] = buff[1];
		free(buff[0]);
		free(buff);
	}
	map->textures[i] = 0;
	map->floor_color = ft_atoi(buff[1]) * 65536 +
		ft_atoi(ft_strchr(buff[1], ',') + 1)
		* 256 + ft_atoi(ft_strrchr(buff[1], ','));
	full_free((void **)buff, 2);
	buff = ft_split(lines[i + 1], ' ');
	map->ceiling_color = ft_atoi(buff[1]) * 65536 +
		ft_atoi(ft_strchr(buff[1], ',') + 1)
		* 256 + ft_atoi(ft_strrchr(buff[1], ','));
	full_free((void **)buff, 2);
	return (i + 2);
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
		map->val[i] = skip_spaces(lines[i]);
	map->val[i] = 0;
	map->height = n;
	map->width = ft_strlen(map->val[0]);
	find_player_pos(map, var);
	j = (int)var->x;
	i = (int)var->y;
	var->sigma = 0.0 * (map->val[i][j] == 'E') + 90.0 * (map->val[i][j] == 'N')
		+ 180.0 * (map->val[i][j] == 'W') + 270.0 * (map->val[i][j] == 'S');
}

static t_maps	read_cub_file(char **argv, t_vars *var)
{
	int		fd;
	char	*line;
	char	**map;
	t_maps	result;
	int		i;

	if (((fd = open(argv[1], O_RDONLY)) == -1)
		|| !(map = malloc(sizeof(char *) * READ_SIZE)))
		exit(1);
	i = -1;
	while ((get_next_line(fd, &line)) > 0)
		map[++i] = line;
	free(line);
	map[++i] = 0;
	if (check_map_error(map))
	{
		perror("Error: wrong cub file format.\n");
		exit(1);
	}
	i = init_map_textures(&result, map);
	init_player_map_param(&result, var, map + i);
	full_free((void **)map, READ_SIZE);
	return (result);
}

int				main(int argc, char **argv)
{
	t_vars	var;
	t_maps	map;

	if (((argc == 3) && (ft_strcmp(argv[2], "--save")))
		|| (argc == 1) || (argc > 3))
	{
		perror("Error: wrong argument format.\n");
		exit(1);
	}
	map = read_cub_file(argv, &var);
	var.map = &map;
	if (argc == 3)
		var.must_save = 1;
	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx,
		var->map->res_width, var->map->res_height, "cub3d");
	mlx_loop_hook(var.mlx, ray_caster, &var);
	mlx_hook(var.win, 2, 1L<<0, camera_update, &var);
	mlx_hook(var.win, 17, 0, x_close, &var);
	mlx_loop(var.mlx);
	return (0);
}
