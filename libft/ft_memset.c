/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:25:36 by cestevez          #+#    #+#             */
/*   Updated: 2022/12/17 21:36:35 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/*#include <stdio.h>*/
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = s;
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return ((void *)str);
}
/*int	main()
{
	char	introduce = 'A';
	char	string[100] = "";
	int	times = 42;

	printf("%s\n", string);
	ft_memset(string, introduce, times);
	printf("%s", string);
	return (0);
}*/
