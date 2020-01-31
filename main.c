/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 12:52:52 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/01/31 15:20:25 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ray_caster(t_vars *var)
{
}

int				camera_update(int key, t_vars *var)
{
}

static int		x_close(t_vars *var)
{
	exit(0);
	return (0);
}

int				main(int argc, char **argv)
{
	t_vars	var;
	t_maps	map;

	if (argc != 2)
	{
		perror("Error: argument count must be 1.\n");
		exit(1);
	}
	map = read_cub_file(argv, &var);
	init_player_map_param(&map, &var);
	var.map = &map;
	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	mlx_loop_hook(var.mlx, ray_caster, &var);
	mlx_hook(var.win, 2, 1L<<0, camera_update, &var);
	mlx_hook(var.win, 17, 0, x_close, &var);
	mlx_loop(var.mlx);
	return (0);
}
