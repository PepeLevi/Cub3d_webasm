/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:14:19 by cestevez          #+#    #+#             */
/*   Updated: 2022/12/18 00:05:57 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>
#include <string.h>*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t						i;
	const unsigned char			*str1;
	const unsigned char			*str2;
	unsigned char				dif1;
	unsigned char				dif2;

	str1 = s1;
	str2 = s2;
	i = 0;
	if (n == 0)
		return (0);
	while (str1[i] == str2[i] && i < (n - 1))
		i++;
	dif1 = str1[i];
	dif2 = str2[i];
	return (dif1 - dif2);
}

/*int main()
{
	char str1[] = "Guachita liNda";
	char str2[] = "Guachita Linda";

	printf("%d\n", ft_memcmp(str1, str2, 1));
}*/
