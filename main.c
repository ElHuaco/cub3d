/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 12:52:52 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/03/02 13:01:58 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		read_map_params(t_maps *map, char *buff)
{
	int		i;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == 'R')
			i = read_res(map, buff, i);
		else if ((buff[i] == 'F') || (buff[i] == 'C'))
			i = read_floor_ceil_color(map, buff, i);
		else if ((buff[i] == 'N') || (buff[i] == 'S') || (buff[i] == 'W')
			|| (buff[i] == 'E'))
			i = read_text_path(map, buff, i);
		else
			error_exit(EINFO);
	}
	if (!(map->north) || !(map->south)
		|| !(map->west) || !(map->east) || !(map->sprite))
		error_exit(EINFO);
	return (i);
}

static void		read_map_values(t_maps *map, char *buff)
{
	int		i;
	int		j;
	char	**vals_with_spaces;
	int		pla_pos_count;

	pla_pos_count = 0;
	vals_with_spaces = ft_split(buff, '\n');
	map->val = skip_spaces(vals_with_spaces);
	map->height = ft_arrlen(map->val);
	map->width = ft_strlen(map->val[0]);
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if ((is_cub_file_chr(map->val[i][j])) == 0)
				error_exit(ENONCHR);
			if (((map->val[i][0] != '1')
				|| (map->val[i][map->height - 1] != '1'))
				|| ((!i || (i == map->height)) && (map->val[i][j] != '1')))
				error_exit(ENOTCLO);
			pla_pos_count += is_player_pos(map->val[i][j]) ? 1 : 0;
			if (pla_pos_count > 1)
				error_exit(EPLAPOS);
		}
	}
}

static void		read_cub_file(char **argv, t_vars *var)
{
	t_maps	map;
	char	*buff;
	int		fd;
	int		i;

	if ((fd = open(argv[1], O_RDONLY) < 0))
		error_exit(EOPEN);
	i = 0;
	buff = malloc(sizeof(char) * 1);
	while ((read(fd, buff, 1)) > 0)
	{
		free(buff);
		i++;
	}
	free(buff);
	close(fd);
	if ((fd = open(argv[1], O_RDONLY) < 0))
		error_exit(EOPEN);
	buff = malloc(sizeof(char) * (i + 1));
	buff[i] = 0;
	read(fd, buff, i);
	i = read_map_params(&map, buff);
	read_map_values(&map, buff + i);
	var->map = &map;
}

int				main(int argc, char **argv)
{
	t_vars	var;

	if (((argc == 3) && (ft_strcmp(argv[2], "--save")))
		|| (argc == 1) || (argc > 3))
	{
		perror("Error: wrong argument format.\n");
		return(1);
	}
	read_cub_file(argv, &var);
	printf("Mapa leido y asignado\n");
	printf("--------Mapa-------\n");
	int i = -1;
	while (++i < ft_arrlen(var.map->val))
		printf("%s\n", var.map->val[i]);
	printf("Map dim: %d %d /t Map res: %d %d\n", var.map->width, var.map->height, var.map->res_width, var.map->res_height);
	printf("Map ceil color: %d, Map floor color: %d\n", var.map->ceiling_color, var.map->floor_color);
	printf("----------Texturas-----\n");
	printf("NO %s SO %s WE %s EA %s S %s\n", var.map->north, var.map->south, var.map->west, var.map->east, var.map->sprite);
	if (argc == 3)
		var.must_save = 1;
	var.mlx = mlx_init();
	if (!var.mlx)
		return (1);
	var.win = mlx_new_window(var.mlx,
		var.map->res_width, var.map->res_height, "cub3d");
	if (!var.win)
		return (1);
	//printf("Instancia mlx iniciada\n");
	mlx_hook(var.win, 1, 0, ray_caster, &var);
	mlx_hook(var.win, 2, 1L<<1, camera_update, &var);
	mlx_hook(var.win, 17, 0, x_close, &var);
	mlx_loop(var.mlx);
	//printf("Se entró al loop\n");
	return (0);
}
