/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:14:43 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/03/04 19:14:07 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			digit_number(int n, int basesize)
{
	int i;

	if (n < 0)
		n *= -1;
	i = 1;
	while ((n / basesize) > 0)
	{printf("EH");
		n = n / basesize;
		i++;
	}
	return (i);
}

void		full_free(void **buff, int n)
{
	int i;

	if (buff)
	{
		i = -1;
		while (++i < n && buff[i])
		{
			if (buff[i])
				free(buff[i]);
		}
		free(buff);
	}
}

int		map_val_topology_err(char **val, int i, int j, int arr_size)
{
	int len;
	int k;
	int l;

	len = ft_strlen(val[i]) - 1;
	k = -1;
	while (val[i][++k] == ' ') ;
	l = len + 1;
	while (val[i][--l] == ' ') ;
	if ((val[i][k] != '1') || (val[i][l] != '1'))
		return (1);
	else if ((!i || (i == arr_size))
		&& ((val[i][j] != '1') && (val[i][j] != ' ')))
		return (1);
	else if ((((i != 0) && (val[i - 1][j] == ' '))
		|| (((i != 0) && (j != 0)) && (val[i - 1][j - 1] == ' '))
		|| (((i != 0) && (j != len)) && (val[i - 1][j + 1] == ' '))
		|| ((j != 0) && (val[i][j - 1] == ' '))
		|| ((j != len) && (val[i][j + 1] == ' '))
		|| ((i != arr_size) && (val[i + 1][j] == ' '))
		|| (((i != arr_size) && (j != len)) && (val[i + 1][j + 1] == ' '))
		|| (((i != arr_size) && (j != 0)) && (val[i + 1][j - 1] == ' ')))
		&& ((val[i][j] != '1') && (val[i][j] != ' ')))
	{printf("due to SPACES\n");
		printf("checked %d %d, with ->%c<-\n", i, j, val[i][j]);
		return (1);
	}
	else
		return (0);
}

void	create_textures_mlx_img(t_vars *var, t_imgs *img)
{
	int		i;

	img[0].img = mlx_new_image(var->mlx, var->map->res_width, var->map->res_height);
	img[1].img = mlx_xpm_file_to_image(var->mlx, var->map->north, &img[1].img_w, &img[1].img_h);
	img[2].img = mlx_xpm_file_to_image(var->mlx, var->map->south, &img[2].img_w, &img[2].img_h);
	img[3].img = mlx_xpm_file_to_image(var->mlx, var->map->west, &img[3].img_w, &img[3].img_h);
	img[4].img = mlx_xpm_file_to_image(var->mlx, var->map->east, &img[4].img_w, &img[4].img_h);
	img[5].img = mlx_xpm_file_to_image(var->mlx, var->map->sprite, &img[5].img_w, &img[5].img_h);
	i = -1;
	while (++i < 5 + SPRITE_NUMBER)
	{
		if (img[i].img)
			img[i].addr = mlx_get_data_addr(img[i].img, &img[i].bpp,
				&img[i].ll, &img[i].endian);
		else
			error_exit(ETEXPATH);
	}
}
