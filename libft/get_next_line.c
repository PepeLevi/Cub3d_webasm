/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:46:42 by cestevez          #+#    #+#             */
/*   Updated: 2023/10/16 16:51:51 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_temp(char **tmp)
{
	if (!(*tmp)[0])
	{
		free((*tmp));
		(*tmp) = NULL;
	}
}

char	*return_line(char *buffer, char *str, char **tmp)
{
	int		i;
	char	*final_str;

	free(buffer);
	buffer = NULL;
	i = search_newline(str);
	if (i == -1)
		i = (int) ft_strlen(str) - 1;
	final_str = malloc(sizeof(char) * (i + 2));
	if (!final_str)
		return (heaths_error(NULL, tmp));
	ft_strlcpy(final_str, str, i + 2);
	free(*tmp);
	*tmp = malloc(sizeof(char) * (ft_strlen(str) - i));
	if (!*tmp)
		return (heaths_error(&final_str, NULL));
	ft_strlcpy(*tmp, str + i + 1, ft_strlen(str) - i);
	free_temp(tmp);
	free(str);
	if (ft_strlen(final_str) == 0)
		return (heaths_error(&final_str, tmp));
	return (final_str);
}

char	*append_str(char *str, char *buffer)
{
	int		len;
	char	*str2;

	len = (int) ft_strlen(str);
	str2 = malloc(sizeof(char) * (len + ft_strlen(buffer) + 1));
	if (!str2)
		return (NULL);
	ft_strlcpy(str2, str, len + 1);
	ft_strlcpy(str2 + len, buffer, ft_strlen(buffer) + 1);
	free(str);
	return (str2);
}

char	*read_next_line(char **buffer, char **str, char **tmp, int fd)
{
	int	rd;

	while (1)
	{
		ft_bzero(*buffer, (BUFFER_SIZE + 1));
		rd = read(fd, *buffer, BUFFER_SIZE);
		if (rd < 0)
		{
			free(*str);
			if (*tmp)
			{
				free(*tmp);
				*tmp = NULL;
			}
			break ;
		}
		*str = append_str(*str, *buffer);
		if (!*str)
			break ;
		if (search_newline(*str) != -1 || rd < BUFFER_SIZE)
			return (return_line(*buffer, *str, &*tmp));
	}
	free(*buffer);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*tmp;
	char		*buffer;
	char		*str;

	str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	ft_bzero(str, (BUFFER_SIZE + 1));
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str || !buffer)
		return (NULL);
	if (tmp)
	{
		if (search_newline(tmp) != -1)
		{
			ft_strlcpy(str, tmp, ft_strlen(tmp) + 1);
			return (return_line(buffer, str, &tmp));
		}
		str = append_str(str, tmp);
		if (!str)
			return (NULL);
	}
	return (read_next_line(&buffer, &str, &tmp, fd));
}
