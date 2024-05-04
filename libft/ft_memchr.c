/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:34:27 by cestevez          #+#    #+#             */
/*   Updated: 2022/12/18 00:00:29 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <string.h>
#include <stdio.h>*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t					i;
	unsigned char			*findhere;
	unsigned char			tofind;

	findhere = (unsigned char *)s;
	tofind = c;
	i = 0;
	if (c == 0 && n == 0)
		return (0);
	if (n == 0)
		return (0);
	while (i < n - 1 && findhere[i] != tofind)
		i++;
	if (findhere[i] == tofind)
		return (&findhere[i]);
	else
		return (0);
}
/*
int main()
{
	int	findme = 'O';
	char	strtoscan[50] = "Encuentra a Oli";

	ft_memchr(strtoscan, findme, 6);
//	printf("'O' found at position %d.\n", strtoscan); 
	printf("here: %s\n", strtoscan);
}*/
