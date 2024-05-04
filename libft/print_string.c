/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:11:19 by cestevez          #+#    #+#             */
/*   Updated: 2023/07/03 17:15:51 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_string(char *s, const char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (s == 0 && c == 's')
	{
		len = write (1, "(null)", 6);
		return (len);
	}
	if (s == 0 && c == 'p')
	{
		len = write (1, "(nil)", 5);
		return (len);
	}
	while (s[i] != 0)
	{
		len += write (1, &s[i], 1);
		i++;
	}
	if (c != 's' && s)
		free(s);
	return (len);
}
