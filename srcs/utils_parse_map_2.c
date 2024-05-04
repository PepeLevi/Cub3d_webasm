/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_map_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:02:43 by emollebr          #+#    #+#             */
/*   Updated: 2024/01/25 18:02:44 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*find_first_line(int file)
{
	int			i;
	char		*line;

	line = get_next_line(file);
	while (line[0] == '\n' || line[0] == ' ')
	{
		i = 0;
		while (line[i] == ' ')
			i++;
		if (ft_isdigit(line[i]) == 1)
			break ;
		free(line);
		line = get_next_line(file);
	}
	return (line);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ' || c == '5' || c == '2');
}

static void	assign_north_or_south(t_data *img, float a, float b)
{
	img->player.dir_x = 0.0;
	img->player.dir_y = a;
	img->player.plane_x = b;
	img->player.plane_y = 0.0;
}

static void	assign_east_or_west(t_data *img, float a, float b)
{
	img->player.dir_x = a;
	img->player.dir_y = 0.0;
	img->player.plane_x = 0.0;
	img->player.plane_y = b;
}

void	parse_player_pos(t_data *img, char dir, int row, int col)
{
	img->world_map[row][col] = 0;
	img->player.x = col + 0.5;
	img->player.y = row + 0.5;
	if (dir == 'N')
		assign_north_or_south(img, -1.0, 0.66);
	if (dir == 'S')
		assign_north_or_south(img, -0.66, 1.0);
	if (dir == 'E')
		assign_east_or_west(img, 1.0, 0.66);
	if (dir == 'W')
		assign_east_or_west(img, -1.0, -0.66);
	return ;
}
