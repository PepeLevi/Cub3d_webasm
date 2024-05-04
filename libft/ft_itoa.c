/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:20:05 by cestevez          #+#    #+#             */
/*   Updated: 2022/12/29 18:20:11 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*#include <stdio.h>
#include <stdlib.h>*/
#include "libft.h"

static char	*convert(char *s, int num, int len, int sign);
static int	get_length(int n);

char	*ft_itoa(int n)
{
	char	*str;
	int		length;
	int		isnegative;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	isnegative = 0;
	length = get_length(n);
	if (n < 0)
	{
		isnegative = 1;
		n = -n;
	}
	str = (char *)malloc(sizeof(char) * length + 1 + isnegative);
	if (!str)
		return (0);
	if (n >= 0)
		str = convert(str, n, length, isnegative);
	return (str);
}

static int	get_length(int n)
{
	int	i;

	i = 1;
	while (n / 10 != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*convert(char *s, int num, int len, int sign)
{
	if (sign != 0)
	{
		len += 1;
		s[len] = '\0';
		while (len > 0)
		{
			s[len - 1] = (num % 10) + '0';
			num = num / 10;
			len--;
		}
		s[0] = '-';
	}
	else
	{
		s[len] = '\0';
		while (len - 1 >= 0)
		{
			s[len - 1] = (num % 10) + '0';
			num = num / 10;
			len--;
		}
	}
	return (s);
}
/*int	main ()
{
	long long int n = 0;
	char *str;

	str = ft_itoa(n);
	printf("converted %lld into %s", n, str);
}*/
/*int main(void)
{
	char buffer[100];
	int test[] = {123, 234, 0, 17, -4, -7, -17, -27, INT_MAX, INT_MIN};
	size_t len = sizeof(test) / sizeof(*test);
	
	// give it a small buffer and see how it works
	for (int i=0, num; i < len; i++) {
		num = test[i];
		char* str = itoa(num, 2, buffer); 
		printf("%-10d <%s>\n", num, str);
	}
	
	// now give it the correctly-sized buffer
	for (int i=0, num; i < len; i++) {
		num = test[i];
		char* str = itoa(num, sizeof buffer / sizeof *buffer, buffer);
		printf("%-10d <%s>\n", num, str);
	}
}*/
