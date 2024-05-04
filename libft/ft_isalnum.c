/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:25:12 by cestevez          #+#    #+#             */
/*   Updated: 2022/12/02 17:35:17 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <unistd.h>*/
int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9')
		|| (c > 64 && c < 91)
		|| (c > 96 && c < 123))
		return (1);
	else
		return (0);
}
/*int	main(int argc, char **argv)
{
	if (argc > 1)
		ft_isalnum(argv[1][0]);
	else
		return(0);
}*/
