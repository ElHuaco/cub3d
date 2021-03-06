/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 12:52:52 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/03/06 14:37:16 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		read_map_params(t_maps *map, char *buff)
{
	int		i;

	map->res_width = 0;
	map->res_height = 0;
	map->ceiling_color = 0;
	map->floor_color = 0;
	i = 0;
	while (!(map->north) || !(map->south) || !(map->west) || !(map->east)
		|| !(map->sprite) || !(map->res_width) || !(map->res_height)
		|| !(map->ceiling_color) || !(map->floor_color))
	{
		if (buff[i] == 'R')
			i = read_res(map, buff, i);
		else if ((buff[i] == 'F') || (buff[i] == 'C'))
			i = read_floor_ceil_color(map, buff, i);
		else if ((buff[i] == 'N') || (buff[i] == 'S') || (buff[i] == 'W')
			|| (buff[i] == 'E'))
			i = read_text_path(map, buff, i);
		else if (buff[i] == '\n')
			i++;
		else
			error_exit(EINFO);
	}
	while (buff[i++] == '\n')
	{
	}
	return (i - 1);
}

static void		read_map_values(t_vars *var, t_maps *map, char *buff)
{
	int		i;
	int		j;
	int		pla_pos_count;
	char	**vals_without_sp_squaring;

	pla_pos_count = 0;
	vals_without_sp_squaring = ft_split(buff, '\n');
	map->val = space_squaring(vals_without_sp_squaring);
	map->height = ft_arrlen(map->val);
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (map->val[i][++j])
		{
			if ((is_cub_file_chr(map->val[i][j])) == 0)
				error_exit(ENONCHR);
			if (map_val_topology_err(map->val, i, j, map->height - 1))
				error_exit(ENOTCLO);
			pla_pos_count += set_pla_pos_camera(var, map, i, j);
		}
	}
	if ((pla_pos_count > 1) || (pla_pos_count == 0))
		error_exit(EPLAPOS);
}

static t_maps	read_cub_file(char **argv, t_vars *var)
{
	t_maps	map;
	char	*buff;
	int		fd;
	int		i;

	if ((fd = open(argv[1], O_RDONLY)) < 0)
		error_exit(EOPEN);
	i = 0;
	buff = malloc(sizeof(char) * 1);
	while ((read(fd, buff, 1)) == 1)
		i++;
	free(buff);
	close(fd);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		error_exit(EOPEN);
	buff = malloc(sizeof(char) * (i + 1));
	buff[i] = 0;
	read(fd, buff, i);
	i = read_map_params(&map, buff);
	read_map_values(var, &map, buff + i);
	free(buff);
	return (map);
}

int				main(int argc, char **argv)
{
	t_vars	var;
	t_maps	map;

	if (((argc == 3) && (ft_strcmp(argv[2], "--save")))
		|| (argc == 1) || (argc > 3))
		error_exit(EARG);
	map = read_cub_file(argv, &var);
	var.map = &map;
	if (argc == 3)
		var.must_save = 1;
	var.mlx = mlx_init();
	if (!var.mlx)
		error_exit(EMLX);
	var.win = mlx_new_window(var.mlx,
		var.map->res_width, var.map->res_height, "cub3d");
	if (!var.win)
		error_exit(EWIN);
	mlx_hook(var.win, 1, 0, ray_caster, &var);
	mlx_hook(var.win, 2, 1L << 1, camera_update, &var);
	mlx_hook(var.win, 17, 0, x_close, &var);
	mlx_loop(var.mlx);
	return (0);
}
