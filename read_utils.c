/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 16:15:52 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/02/04 16:24:02 by aleon-ca         ###   ########.fr       */
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
		if (str[i] == ' ')
			count++;
	}
	result = malloc(sizeof(char) * (count + 2));
	result[count + 1] = 0;
	count = -1;
	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ')
			result[++count] = str[i];			
	}
	return (result);
}

