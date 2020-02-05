/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:16:50 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/05 16:15:01 by aleon-ca         ###   ########.fr       */
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
	char		**val;
	int			height;
	int			width;
	int			res_height;
	int			res_width;
	char		**textures;
	int			floor_color;
	int			ceiling_color;
	int			must_save;
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

int		ray_caster(t_vars *var);
int		camera_update(int keycode, t_vars *var);
int		x_close(t_vars *var);

char	*skip_spaces(char *str);
int		is_cub_file_chr(int c);
int		is_player_pos(int c);
int		check_wall_error(char *line, int *param);
int		check_player_pos_error(char **m, int i, int *count);

void	find_player_pos(t_maps *map, t_vars *var);
void	full_free(void **buff, int arr_len);

# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define FOV 60.0
# define SPRITE_NUMBER 1
# define READ_SIZE 50
# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123
# define ESC 53
# define W 13
# define S 1
# define A 0
# define D 2

#endif
