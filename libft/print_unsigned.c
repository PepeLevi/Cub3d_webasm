/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:11:33 by cestevez          #+#    #+#             */
/*   Updated: 2023/07/03 17:16:01 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_unsigned(unsigned int n)
{
	char	num;
	int		len;

	len = 0;
	if (n >= 10)
		len += print_unsigned(n / 10);
	num = (n % 10) + 48;
	len += write(1, &num, 1);
	return (len);
}
