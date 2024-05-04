/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:52:54 by cestevez          #+#    #+#             */
/*   Updated: 2023/10/16 16:53:00 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*heaths_error(char **str, char **tmp)
{
	if (*str != NULL)
		free (*str);
	if (*tmp != NULL)
	{
		free (*tmp);
		*tmp = NULL;
	}
	return (NULL);
}

int	search_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
