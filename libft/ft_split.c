/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 20:45:51 by cestevez          #+#    #+#             */
/*   Updated: 2023/01/09 23:09:35 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdlib.h>
#include <stdio.h>
#include <string.h>*/
#include "libft.h"

static size_t	count_words(const char *str, char c);
static size_t	wordsize(const char *s, char c, size_t i);
static void		my_free(char **string, int i);

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	word;
	char	**array_of_pointers;

	i = 0;
	j = -1;
	word = count_words(s, c);
	array_of_pointers = (char **)malloc(sizeof(char *) * (word + 1));
	if (!array_of_pointers)
		return (0);
	while (++j < word)
	{
		while (s[i] == c)
			i++;
		array_of_pointers[j] = ft_substr(s, i, wordsize(s, c, i));
		if (!array_of_pointers[j])
		{
			my_free(array_of_pointers, j);
			return (0);
		}
		i += wordsize(s, c, i);
	}
	array_of_pointers[j] = 0;
	return (array_of_pointers);
}

static size_t	count_words(const char *str, char c)
{
	int	trigger;
	int	count;

	trigger = 0;
	count = 0;
	while (str && *str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			count++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (count);
}

static size_t	wordsize(const char *s, char c, size_t i)
{
	size_t	size;

	size = 0;
	while (s[i] != 0 && s[i] != c)
	{
		i++;
		size++;
	}
	return (size);
}

static void	my_free(char **string, int i)
{
	while (i >= 0)
	{
		free(string[i]);
		i--;
	}
	free(string);
	return ;
}
