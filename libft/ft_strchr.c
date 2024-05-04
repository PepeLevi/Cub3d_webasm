/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:15:16 by cestevez          #+#    #+#             */
/*   Updated: 2022/12/18 01:16:20 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <string.h>
#include <stdio.h>*/
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (0);
}
/*int main()
{
	int	findme = '\0';
	char strtoscan[] = "Encuentra a Oli";
	int result;

	char *found = ft_strchr(strtoscan, findme);
	result = found - strtoscan;
	if (found != 0)
	{
		printf("'%c' found at position %d.\n", findme, result + 1);
		printf("here: %s\n", found);
	}
	else
		printf("No coincidences");
}*/
