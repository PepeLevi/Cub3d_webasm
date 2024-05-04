/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:18:43 by cestevez          #+#    #+#             */
/*   Updated: 2023/01/09 16:37:15 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*#include <stdio.h>*/
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	j = 0;
	ptr = (char *)big;
	if (little[j] == '\0')
		return (ptr);
	while (big[i] != '\0' && i < len)
	{
		while (big[i] == little[j] && i < len)
		{
			i++;
			j++;
			if (little[j] == '\0')
				return (&ptr[i - j]);
		}
		i = i - j;
		j = 0;
		i++;
	}
	return (0);
}
/*int	main(void)
{
	const char	strsrc[] = "do yoube b wannabe be my bf";
	const char	strto_find[] = "";

	printf("%s", ft_strnstr(strsrc, strto_find, 0));
}*/
