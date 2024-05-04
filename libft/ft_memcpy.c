/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:48:17 by cestevez          #+#    #+#             */
/*   Updated: 2022/12/07 20:15:44 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	const char	*s1;
	char		*s2;

	s1 = src;
	s2 = dest;
	i = 0;
	if (!s1 && !s2)
		return (0);
	while (i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}
/*int	main()
{
	char	str1[] = "hola";
	char	str2[] = "hey!, como estas?";
	
	ft_memcpy(str2, str1, 4);
	printf("%s", str2);
}*/
