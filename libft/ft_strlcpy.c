/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:18:03 by cestevez          #+#    #+#             */
/*   Updated: 2024/01/06 17:01:36 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*#include <stdio.h>
#include <string.h>*/
size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t size)
{
	size_t	i;
	size_t	length;

	i = 0;
	length = 0;
	while (src[length] != '\0')
		length++;
	if (size < 1)
		return (length);
	while (src[i] != '\0' && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (length);
}
/*int	main(void)
{
	char	dest[25]= "No";
	char	src[25]= "What the fuck?";
	
	printf("Length:%zu, srcstr:%s dest:%s", ft_strlcpy(dest, src, 3), src, dest);
}*/
