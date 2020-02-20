/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 16:15:52 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/20 15:57:21 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char		*skip_spaces(char *str)
{
	int		i;
	int		count;
	char	*result;

	count = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ')
			count++;
	}
	result = malloc(sizeof(char) * (count + 1));
	result[count] = 0;
	count = -1;
	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ')
			result[++count] = str[i];
	}
	return (result);
}

int			is_cub_file_chr(int c)
{
	if ((c == 'W') || (c == 'E') || (c == 'N') || (c == 'S')
		|| (c == 'N') || (c == '0') || (c == '1') || (c == '2')
		|| (c == ' '))
		return (1);
	else
		return (0);
}

int			check_wall_error(char *line, int *i)
{
	if (((i[0] == i[4]) || (i[0] == i[2] - 1))
		&& ((line[i[3]] != '1') && (line[i[3]] != ' ')))
		return (1);
	else if (((i[0] != i[4]) && (i[0] != i[2] - 1))
		&& ((ft_strchr(line, '1') != line)
		|| (ft_strrchr(line, '1') != line + i[1] - 1)))
		return (1);
	else
		return (0);
}

int			check_player_pos_error(char **m, int i, int *count)
{
	if ((ft_strchr(m[i], 'N')) || (ft_strchr(m[i], 'S'))
		|| (ft_strchr(m[i], 'W')) || (ft_strchr(m[i], 'E')))
		*count += 1;
	if (!(m[i + 1]) && (*count != 1))
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
