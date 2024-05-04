/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:06:50 by emollebr          #+#    #+#             */
/*   Updated: 2024/01/29 16:06:52 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

unsigned int	rgb_to_unsigned_int(char *color)
{
	int	rgb[3];
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < 3)
	{
		rgb[j] = 0;
		while (color[i] != '\0' && color[i] != ',')
		{
			if (ft_isdigit(color[i]) != 1 && color[i] != ',')
				return (ft_printf("%s %s\n", RGB_ERROR_1, color), 0);
			rgb[j] = rgb[j] * 10 + (color[i] - '0');
			i++;
		}
		if (rgb[j] < 0 || rgb[j] > 255)
			return (ft_printf("%s %d\n", RGB_ERROR_2, rgb[j]), 0);
		i++;
		j++;
	}
	return (((unsigned int)rgb[0] << 16) | ((unsigned int)rgb[1] << 8)
		| (unsigned int)rgb[2]);
}

int	copy_texture_element(t_texture *element, char *line)
{
	int	i;

	i = 0;
	while (line[i] != ' ')
		i++;
	while (line[i] == ' ')
		i++;
	element->path = ft_substr(line, i, ft_strlen(line) - i - 1);
	if ((line[0] == 'F' || line[0] == 'C') && ft_isdigit(element->path[0]) == 1)
	{
		element->rgb = rgb_to_unsigned_int(element->path);
		if (element->rgb == 0)
			return (-1);
	}
	else if (ft_strchr("NSWEFC", line[0]) != 0)
	{
		element->rgb = 0;
		if (access(element->path, O_RDONLY) < 0)
			return (ft_printf("Error: Couldn't access texture file: %s\n",
					element->path), -1);
	}
	else
		return (ft_printf("Error: Invalid line in .cub file: %s\n", line), -1);
	return (0);
}

int	check_for_map_start(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]))
		return (free(line), 1);
	return (0);
}

int	iterate_texture_element(char *line, t_data *img)
{
	int	index;

	if (line[0] == 'N')
		index = l_N;
	if (line[0] == 'S')
		index = l_S;
	if (line[0] == 'W')
		index = l_W;
	if (line[0] == 'E')
		index = l_E;
	if (line[0] == 'F')
		index = l_F;
	if (line[0] == 'C')
		index = l_C;
	if (copy_texture_element(&img->textures[index], line) == -1)
		return (free(line), -1);
	return (0);
}

int	parse_textures(int file, t_data *img)
{
	char	*line;
	int		elems;

	elems = 0;
	while (elems < 6)
	{
		line = get_next_line(file);
		if (line == NULL || check_for_map_start(line) == 1)
			break ;
		if (ft_strlen(line) != 0 && line[0] != '\n')
		{
			if (iterate_texture_element(line, img) == -1)
				return (-1);
			elems++;
		}
		free(line);
	}
	if (!validate_textures(img, elems))
		return (-1);
	return (0);
}
