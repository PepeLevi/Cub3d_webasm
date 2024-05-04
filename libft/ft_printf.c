/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:24:01 by cestevez          #+#    #+#             */
/*   Updated: 2023/07/03 17:16:29 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	type_print(const char c, va_list arg_list);

int	ft_printf(const char *format, ...)
{
	va_list	arg_list;
	int		len;
	int		i;

	len = 0;
	i = 0;
	va_start(arg_list, format);
	if (format == 0)
		return (-1);
	while (format[i] != 0)
	{
		if (format[i] == '%')
		{
			len += type_print(format[i + 1], arg_list);
			i++;
		}
		else
			len += write(1, &format[i], 1);
		i++;
	}
	va_end(arg_list);
	return (len);
}

int	type_print(const char c, va_list arg_list)
{
	char	*converted;

	if (c == '%')
		return (write(1, "%", 1));
	if (c == 'c')
		return (print_char(va_arg(arg_list, int)));
	if (c == 's')
		return (print_string(va_arg(arg_list, char *), c));
	if (c == 'd' || c == 'i')
		return (print_nbr(va_arg(arg_list, int)));
	if (c == 'u')
		return (print_unsigned(va_arg(arg_list, unsigned int)));
	if (c == 'x' || c == 'X')
		converted = print_hex(va_arg(arg_list, unsigned int), c);
	if (c == 'p')
		converted = print_address(va_arg(arg_list, size_t));
	if (c == 'x' || c == 'X' || c == 'p')
		return (print_string(converted, c));
	else
		return (-1);
}
