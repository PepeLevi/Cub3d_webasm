/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:20:55 by cestevez          #+#    #+#             */
/*   Updated: 2022/12/29 18:20:57 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>*/
#include "libft.h"

static char			*write_new_str(char *s2, char *s, size_t start, size_t end);
static unsigned int	search_in_set(const char *set, const char c);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*new_str;

	start = 0;
	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	while (s1[start] != '\0' && search_in_set(set, s1[start]) != 0)
		start++;
	end = ft_strlen(s1);
	while (end > start && search_in_set(set, s1[end - 1]) != 0)
		end--;
	new_str = (char *)malloc(end - start + 1);
	if (!new_str)
		return (0);
	return (write_new_str(new_str, (char *)s1, start, end));
}

static char	*write_new_str(char *s2, char *s, size_t start, size_t end)
{
	size_t	i;

	i = 0;
	while (start < end)
		s2[i++] = s[start++];
	s2[i] = '\0';
	return (s2);
}

static unsigned int	search_in_set(const char *set, const char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}
/*int main()
{
	char *str;
	char *trim_set;

	str = "acrcr";
	trim_set = "acb";
	printf("string before trimming: %s\n", str);
	str = ft_strtrim(str, trim_set);
	printf("string after trimming: %s\n", str);
}*/
