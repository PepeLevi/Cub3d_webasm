/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:16:13 by cestevez          #+#    #+#             */
/*   Updated: 2022/12/29 20:18:19 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	length;
	char	*ptr;

	length = 0;
	while (s[length] != '\0')
		length++;
	ptr = (char *)malloc(sizeof(char) * length + 1);
	if (ptr)
	{
		length = 0;
		while (s[length] != '\0')
		{
			ptr[length] = s[length];
			length++;
		}
		ptr[length] = '\0';
		return (ptr);
	}
	return (0);
}
