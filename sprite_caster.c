/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_caster.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:39:48 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/06/30 13:21:57 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_map_sprites(t_vars *var)
{
	t_sprites	*sprites;
	int			n;
	int			i;
	int			j;

	n = 0;
	i = -1;
	while (++i < var->map->height)
	{
		j = -1;
		while (var->map->val[i][++j])
		{
			if (var->map->val[i][j] == '2')
				n++;
		}
	}
	sprites = malloc(sizeof(struct s_sprites) * n);
	var->map->sprites = sprites;
	return (n);
}

static void	find_sprite_pos_and_dist(t_vars *var)
{
	int		i;
	int		j;
	int		k;

	k = -1;
	i = -1;
	while (++i < var->map->height)
	{
		j = -1;
		while (var->map->val[i][++j])
		{
			if (var->map->val[i][j] == '2')
			{
				var->map->sprites[++k].x = j + 0.5;
				var->map->sprites[k].y = i + 0.5;
				var->map->sprites[k].dist =
					pow(var->x - j - 0.5, 2) + pow(var->y - i - 0.5, 2);
			}
		}
	}
}

static void	sort_sprites_by_distance(t_vars *var)
{
	int			i;
	int			j;
	t_sprites	temp;

	i = -1;
	while (++i < var->map->sprite_num)
	{
		j = -1;
		while (++j < var->map->sprite_num)
		{
			if ((var->map->sprites[j].dist > var->map->sprites[i].dist)
				&& (j > i))
			{ 
				temp = duplicate_sprite(var->map->sprites[i]);
				replace_sprite(var->map->sprites + i,
					var->map->sprites + j);
				replace_sprite(var->map->sprites + j, &temp);
			}
		}
	}
}

static void	put_sprite_img(t_vars *v, int *l, double *p, t_imgs *i)
{
	char	*dst;
	char	*src;
	int		s[2];
	int		c;
	int		r;

	c = l[0] - 1;
	while (++c < l[1])
	{
printf("===========Pintando columna %d==========\n", c);
		s[0] = (c - l[0]) * i[5].img_w / fabs(v->map->res_height / p[1]);
	 	if ((p[1] > 0) && (c > 0) && (c < v->map->res_width)
				&& (p[1] < v->ray_distance[c]))
		{
			r = l[2] - 1;
			while (++r < l[3])
			{
printf("Bounds: Xstart: %d Xend: %d Ystart: %d Yend: %d\n", l[0], l[1], l[2], l[3]);
printf("Projections: Xpro: %f Ypro: %f\n", p[0], p[1]);
				s[1] = (r - l[2]) * i[5].img_h
					/ fabs(v->map->res_height / p[1]);
printf("\tTrying to assign sprexel %d %d\n", s[0], s[1]);
				dst = i[0].addr + r * i[0].ll + c * (i[0].bpp / 8);
				src = i[5].addr + s[1] * i[5].ll + s[0] * (i[5].bpp / 8);
				if (*(unsigned int *)src != 0)
				{
					printf("\tAssigned sprel %d %d to %d %d\n", s[0], s[1], c, r);
					*(unsigned int *)dst = *(unsigned int *)src;
				}
			//	else
				//	printf("\tSprel %d %d for %d %d was black\n", s[0], s[1], c, r);
			}
		}
	}
}
//Xq proyectar distinto a los muros? Xq sigue al player en proyeccion 2D
void		sprite_caster(t_vars *var, t_imgs *img)
{
	int		i;
	double	proyect[2];
	int		len[4];
//printf("sprite caster called\n");
	var->map->sprite_num = count_map_sprites(var);
//printf("Found %d sprites\n", var->map->sprite_num);
	find_sprite_pos_and_dist(var);
	sort_sprites_by_distance(var);
//printf("Sprites sorted\n");
	i = -1;
	while (++i < var->map->sprite_num)
	{
		var->map->sprites[i].x -= var->x;
		var->map->sprites[i].y -= var->y;
		proyect[0] = sin(var->sigma) * var->map->sprites[i].x
			+ cos(var->sigma) * var->map->sprites[i].y;
		proyect[1] = cos(var->sigma) * var->map->sprites[i].x
			- sin(var->sigma) * var->map->sprites[i].y;
		if (fabs(proyect[1]) > 10e-7)
		{
//printf("Proyections for sprite %d: Xpro: %f Ypro: %f\n", i, proyect[0], proyect[1]);
			calc_sprite_bounds(var, len, proyect);
//printf("Bounds for sprite %d: Xstart: %d Xend: %d Ystart: %d Yend: %d\n", i, len[0], len[1], len[2], len[3]);
			put_sprite_img(var, len, proyect, img);
		}
	}
}
