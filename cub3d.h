/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:16:50 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/03/02 13:11:01 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx_opengl_20191021/mlx.h"
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/get_next_line.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

# define FOV M_PI / 2.0
# define CAM_VEL 0.1
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
# define EOPEN "Error opening file\n"
# define EPLAPOS "Several starting positions\n"
# define ENONCHR "Found symbol outside cub file standard\n"
# define ENOTCLO "Map not enclosed by walls\n"
# define EINFO "Wrong information in cub file parameters\n"

typedef struct		s_maps
{
	char			**val;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*sprite;
	int				height;
	int				width;
	int				res_height;
	int				res_width;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	int				*wall_linelength;
	int				*wall_start;
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
	double			*ray_hit;
	int				must_save;
}					t_vars;

typedef struct		s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				ll;
	int				endian;
	int				img_w;
	int				img_h;
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
void	error_exit(char *errstr);

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

int		digit_number(int n, int basesize);
int		is_cub_file_chr(int c);
int		is_player_pos(int c);
int		read_floor_ceil_color(t_maps *map, char *buff, int i);
int		read_res(t_maps *map, char *buff, int i);

/*
 **		read_utils2
 */

int		read_text_path(t_maps *map, char *buff, int i);
void	find_player_pos(t_maps *map, t_vars *var);
void	full_free(void **buff, int arr_len);
char	**skip_spaces(char **lines);
void	create_textures_mlx_img(t_vars *var, t_imgs *img);

/*		save_utils
 *
 */

void	save_img(t_vars *var, void *img);
#endif
