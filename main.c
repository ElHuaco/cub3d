/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 12:52:52 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/03/03 12:48:48 by aleon-ca         ###   ########.fr       */
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
	while (buff[i++] == '\n');
	return (i - 1);
}

static void		read_map_values(t_vars *var, t_maps *map, char *buff)
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
	/*printf("Mapa leido y asignado\n");
	printf("Map dim: %d %d Map res: %d %d\n", map->width, map->height, map->res_width, map->res_height);
	printf("Map ceil color: %d, Map floor color: %d\n", map->ceiling_color, map->floor_color);
	printf("----------Texturas-----\n");
	printf("NO: %s SO: %s WE: %s EA: %s S: %s\n", map->north, map->south, map->west, map->east, map->sprite);
	printf("------------Mapa-------\n");
	int k = -1;
	while (++k < ft_arrlen(map->val))
		printf("%s\n", map->val[k]);*/
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if ((is_cub_file_chr(map->val[i][j])) == 0)
				error_exit(ENONCHR);
			if (((map->val[i][0] != '1')
				|| (map->val[i][map->width - 1] != '1'))
				|| ((!i || (i == map->height - 1)) && (map->val[i][j] != '1')))
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
	{
		perror("Error: wrong argument format.\n");
		return(1);
	}
	map = read_cub_file(argv, &var);
	var.map = &map;
	if (argc == 3)
		var.must_save = 1;
	//printf("mlx init call\n");
	var.mlx = mlx_init();
	if (!var.mlx)
		return (1);
	//printf("new window call\n");
	var.win = mlx_new_window(var.mlx,
		var.map->res_width, var.map->res_height, "cub3d");
	if (!var.win)
		return (1);
	//printf("Instancia mlx iniciada\n");
	mlx_hook(var.win, 1, 0, ray_caster, &var);
	mlx_hook(var.win, 2, 1L<<1, camera_update, &var);
	mlx_hook(var.win, 17, 0, x_close, &var);
	//printf("Se entró al loop\n");
	mlx_loop(var.mlx);
	return (0);
}
