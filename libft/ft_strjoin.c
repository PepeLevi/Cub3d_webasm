/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:16:50 by cestevez          #+#    #+#             */
/*   Updated: 2023/01/03 23:09:22 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joint_str;
	size_t	i;

	i = ft_strlen(s1) + ft_strlen(s2);
	joint_str = (char *)malloc(i + 1);
	if (!joint_str)
		return (0);
	ft_strlcpy(joint_str, s1, i + 1);
	ft_strlcat(joint_str, s2, i + 1);
	return (joint_str);
}
/*int	main()
{
	char	s1[] = "lorem ipsum";
	char	s2[] = "dolor sit amet";
	char	*strjoin;

	strjoin = ft_strjoin(s1, s2);
	printf("%s\n", strjoin);
}*/