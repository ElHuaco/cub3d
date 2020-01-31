/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:16:50 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/01/31 15:37:44 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx_opengl_20191021/mlx.h"
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/get_next_line.h"
# include <math.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct	s_maps
{
	char		**values;
	int			height;
	int			width;
	//Texturas y sprites
}				t_maps;

typedef struct	s_vars
{
	void		*win;
	void		*mlx;
	t_maps		*map;
	double		sigma;
	double		x;
	double		y;
}				t_vars;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			ll;
	int			endian;
}				t_img;

t_maps		read_cub_file(char **argv, t_vars *var);
void		init_player_map_param(t_maps *map, t_vars *var);

# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123
# define ESC 53
# define W 13
# define S 1
# define A 0
# define D 2
# define FOV 60.0
#endif
