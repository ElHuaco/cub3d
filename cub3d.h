/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:16:50 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/11 15:34:51 by aleon-ca         ###   ########.fr       */
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

# define FOV M_PI / 5.5
# define SPRITE_NUMBER 1
# define READ_SIZE 50
# define PI M_PI
# define PI2 PI / 2.0
# define _3PI2 (3.0 / 2.0) * PI
# define _2PI 2.0 * PI
# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123
# define ESC 53
# define W 13
# define S 1
# define A 0
# define D 2
# define EPLAPOS "Wrong starting position number\n"
# define ELINELEN "Different map line sizes\n"
# define ENONCHR "Non cub file symbol found\n"
# define ENOTCLO "Map not closed by walls\n"

typedef struct		s_maps
{
	char			**val;
	int				height;
	int				width;
	int				res_height;
	int				res_width;
	char			**textures;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
}					t_maps;

typedef struct		s_vars
{
	void			*win;
	void			*mlx;
	t_maps			*map;
	double			sigma;
	double			x;
	double			y;
	char			side;
	int				must_save;
}					t_vars;

typedef struct		s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				ll;
	int				endian;
}					t_imgs;

/*
 **		ray_caster
 */

int		ray_caster(t_vars *var);

/*
 **		hooks
 */

int		camera_update(int keycode, t_vars *var);
int		x_close(t_vars *var);

/*
 **		ray_caster_utils_calc
 */

double	ray_distance(t_vars *var, int col_number);

/*
 **		ray_caster_utils_calc2
 */

void	cuad_calc(t_vars *var, double phi, int *map_cell, double *dist);

/*
 **		ray_caster_utils_calc3
 */

void	phi_zero_calc(t_vars *var, int *map_cell, double *dist);
void	phi_pi_half_calc(t_vars *var, int *map_cell, double *dist);
void	phi_pi_calc(t_vars *var, int *map_cell, double *dist);
void	phi_three_pi_half_calc(t_vars *var, int *map_cell, double *dist);

/*
 **		read_utils
 */

char	*skip_spaces(char *str);
int		is_cub_file_chr(int c);
int		is_player_pos(int c);
int		check_wall_error(char *line, int *param);
int		check_player_pos_error(char **m, int i, int *count);

/*
 **		read_utils2
 */

void	find_player_pos(t_maps *map, t_vars *var);
void	full_free(void **buff, int arr_len);

#endif
