/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:10:50 by cestevez          #+#    #+#             */
/*   Updated: 2023/07/03 17:15:39 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*hex_ptr(char *ptr, int i, int j, unsigned int num);

char	*print_hex(unsigned int num, const char c)
{
	int				i;
	int				j;
	char			*ptr;
	unsigned int	temp;

	i = 0;
	j = 0;
	temp = num;
	while (temp != 0)
	{
		i++;
		temp /= 16;
	}
	if (temp == 0)
		j = 1;
	ptr = (char *)malloc(sizeof(char) * (i + j) + 1);
	if (ptr == 0)
		return (0);
	ptr = hex_ptr(ptr, i, j, num);
	if (c == 'X')
		ptr = toupper_printf(ptr);
	return (ptr);
}

char	*hex_ptr(char *ptr, int i, int j, unsigned int num)
{
	char	*str;

	str = "0123456789abcdef";
	if (num == 0)
	{
		ptr[j] = 0;
		ptr[j - 1] = num + 48;
	}
	if (num != 0)
	{
		ptr[i] = 0;
		while (i > 0)
		{
			ptr[i - 1] = str[num % 16];
			num /= 16;
			i--;
		}
	}
	return (ptr);
}
