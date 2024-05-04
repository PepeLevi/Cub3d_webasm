/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:17:29 by cestevez          #+#    #+#             */
/*   Updated: 2022/12/17 22:23:33 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*#include <stdio.h>
#include <string.h>*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	length;
	size_t	i;
	size_t	dstlen;

	length = 0;
	i = 0;
	while (dst[length] != '\0')
		length++;
	dstlen = length;
	while (size > (length + 1) && src[i] != '\0')
	{
		dst[length] = src[i];
		length++;
		i++;
	}
	dst[length] = '\0';
	while (src[i] != '\0')
		i++;
	if (size < dstlen)
		return (i + size);
	return (dstlen + i);
}
/*int	main(void)
{
	char	dest[25]= "None";
	char	src[25]= "What the?";
	size_t length;
	
	length = ft_strlcat(dest, src, 25);
	printf("Length: %zu, srcstr: %s dest: %s", length, src, dest);
}*/
