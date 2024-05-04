/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:11:05 by cestevez          #+#    #+#             */
/*   Updated: 2023/07/03 17:15:44 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_nbr(int n)
{
	int	putme;
	int	len;

	len = 0;
	if (n == -2147483648)
		len += write (1, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			n *= -1;
			len += write (1, "-", 1);
		}
		if (n > 9)
			len += print_nbr(n / 10);
		putme = n % 10 + '0';
		len += write(1, &putme, 1);
	}
	return (len);
}
/*{
	char	num;
	int		len;

	len = 0;
	if (n > -10 && n < 0)
		len += write(1, "-", 1);
	if (n >= 10 || n <= -10)
		print_nbr(n / 10);
	if (n < 0)
	{
		n %= 10;
		n *= -1;
	}
	num = (n % 10) + 48;
	len += write(1, &num, 1);
	return (len);
}*/
