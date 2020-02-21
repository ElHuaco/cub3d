/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 16:15:52 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/21 16:31:40 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			is_cub_file_chr(int c)
{
	if ((c == 'W') || (c == 'E') || (c == 'N') || (c == 'S')
		|| (c == 'N') || (c == '0') || (c == '1') || (c == '2')
		|| (c == ' '))
		return (1);
	else
		return (0);
}

int			is_player_pos(int c)
{
	if ((c == 'W') || (c == 'E') || (c == 'N') || (c == 'S')
		|| (c == 'N'))
		return (1);
	else
		return (0);
}

int			read_floor_ceil_color(t_maps *map, char *buff, int i)
{
	int		j;
	int		ceil_or_floor_bool;
	int		r;
	int		g;
	int		b;

	ceil_or_floor_bool = (buff[i] == 'F') ? 0 : 1;
	while (buff[++i] == ' ');
	r = ft_atoi(buff + i) * 65536;
	j = -1;
	while (ft_isnum(buff[i + ++j]));
	i += j + 1;
	g = ft_atoi(buff + i) * 256;
	j = 0;
	while (ft_isnum(buff[i + ++j]));
	i += j + 1;
	b = ft_atoi(buff + i);
	if ((r < 0) || (g < 0) || (b < 0))
		error_exit(EINFO);
	if (!ceil_or_floor_bool)
		map->floor_color = r + g + b;
	else
		map->ceiling_color = r + g + b;
	return (i + digit_number(b, 10));
}

int			read_res(t_maps *map, char *buff, int i)
{
	int		j;

	while (buff[++i] == ' ');
	j = -1;
	while (ft_isnum(buff[i + ++j]));
	map->res_height = ft_atoi(buff + i);
	i += j;
	while (buff[i++] == ' ');
	j = 0;
	while (ft_isnum(buff[i + j++]));
	map->res_width = ft_atoi(buff + i);
	if ((map->res_width <= 0) || (map->res_height <= 0))
		error_exit(EINFO);
	return (i + j);
}

int			read_text_path(t_maps *map, char *buff, int i)
{
	int		j;
	int		k;

	j = i;
	if ((buff[i] != 'S') && (buff[++i] != 'O'))
		error_exit(EINFO);
	while (buff[++i] == ' ');
	k = i;
	if ((buff[i] != '.') || (buff[i + 1] != '/'))
		error_exit(EINFO);
	while (buff[i++] != '\n');
	buff[i] = 0;
	if (buff[j] == 'N')
		map->north = ft_strdup(buff + k);
	else if ((buff[j] == 'S') && (buff[j + 1] == 'O'))
		map->south = ft_strdup(buff + k);
	else if (buff[j] == 'W')
		map->west = ft_strdup(buff + k);
	else if (buff[j] == 'E')
		map->east = ft_strdup(buff + k);
	else
		map->sprite = ft_strdup(buff + k);
	return (i + 1);
}
