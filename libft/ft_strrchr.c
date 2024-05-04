/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:19:22 by cestevez          #+#    #+#             */
/*   Updated: 2022/12/18 01:18:40 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*#include <string.h>
#include <stdio.h>*/
char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			j = i;
		i++;
	}
	if (j >= 0)
		return ((char *)(s + j));
	if ((char)c == '\0')
		return ((char *)(s + i));
	return (0);
}
/*int main()
{
	int	findme = '\0';
	char strtoscan[] = "";
	int result;

	char *found = ft_strrchr(strtoscan, findme);
	result = found - strtoscan;
	if (found != 0)
	{
		printf("'%c' found at position %d.\n", findme, result + 1); 
		printf("here: %s\n", found);
	}
	else
		printf("No coincidences");
}*/
