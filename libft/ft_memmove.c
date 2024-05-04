/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:46:10 by cestevez          #+#    #+#             */
/*   Updated: 2022/12/09 20:27:45 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>
#include <string.h>*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;

	if ((char *)dest < (const char *)src)
	{
		i = 0;
		while (i < n)
		{
			((char *)dest)[i] = ((const char *)src)[i];
			i++;
		}
	}
	else if ((char *)dest > (const char *)src && n > 0)
	{
		i = n;
		while (i > 0)
		{
			((char *)dest)[i - 1] = ((const char *)src)[i - 1];
			i--;
		}
	}
	return (dest);
}
/*int	main()
{
	char	strsrc[50] = "abcdefghijklmnopqrst";
	char	strdest[50] = "hey!, como estas?";
	
//segmentation fault w. my funct with this ex.if array size not given
	strcpy(strdest,"hey!, como estas?");
	strcpy(strsrc, "abcdefghijklmnopqrst");
	ft_memmove(strdest-4, strsrc, 18);
	puts(strdest);
	puts("\n");
	puts(strsrc);	
	puts("\n");
	strcpy(strdest,"hey!, como estas?");
	strcpy(strsrc, "abcdefghijklmnopqrst");
	memmove(strdest-4, strsrc, 18);
	puts(strdest);
	puts("\n");
	puts(strsrc);
}*/
