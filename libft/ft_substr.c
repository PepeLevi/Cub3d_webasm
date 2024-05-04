/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:20:03 by cestevez          #+#    #+#             */
/*   Updated: 2023/01/03 19:34:24 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (ft_strlen(s) < start)
	{
		ptr = (char *)malloc(sizeof(char));
		if (!ptr)
			return (0);
		*ptr = '\0';
		return (ptr);
	}
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (0);
	while (s[start] != 0 && i < len)
		ptr[i++] = s[start++];
	ptr[i] = '\0';
	return (ptr);
}
/*int		main(void)
{
	char	str[] = "lorem ipsum dolor sit amet";
	char    *new_str;
	
	new_str = ft_substr(str, 7, 10);
	printf("%s\n", new_str);
	return (0);
}*/
