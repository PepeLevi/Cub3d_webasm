/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:09:33 by emollebr          #+#    #+#             */
/*   Updated: 2024/01/25 17:09:35 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_map_rules(char *line, int row, int col, t_data *img)
{
	if (row == 0 || row == img->map_height - 1)
	{
		if (line[col] != '1' && line[col] != ' ')
			return (ft_printf("%s %c\n", MAP_ERROR_2, line[col]), -1);
	}
	else
	{
		if (col == 0 || col == img->map_width - 1)
		{
			if (line[col] != '1')
				return (ft_printf("%s %c\n", MAP_ERROR_3, line[col]), -1);
		}
		else
		{
			if (line[col] == ' ' && line[col - 1] != ' ' && line[col - 1] != '1'
				&& line[col + 1] != '1' && line[col + 1] != ' ')
			{
				ft_printf("%s '%c' at row %d, column %d\n", MAP_ERROR_3,
					line[col], row, col);
				return (-1);
			}
		}
	}
	return (1);
}

int	check_more_map_rules(char *line, int row, int col, int prevRowLength)
{
	if (row > 0 && (int)ft_strlen(line) > prevRowLength && col > prevRowLength)
	{
		if (line[col] != '1')
		{
			ft_printf("%s '%c' at row %d, column %d\n", MAP_ERROR_3, line[col],
				row, col);
			return (-1);
		}
	}
	return (1);
}

int	assign_character_to_map(t_data *img, char c, int row, int col)
{
	if (c == ' ' || c == '\n')
		img->world_map[row][col] = 3;
	else if (ft_isalpha(c))
		parse_player_pos(img, c, row, col);
	else if (c == '5')
	{
		add_sprite(img, row, col);
		if (img->num_sprites == 1)
			img->sprite_head = img->sprites;
	}
	else
		img->world_map[row][col] = c - 48;
	if (c == '2' && img->doors.door_bool == 0)
		img->doors.door_bool = 1;
	return (0);
}

int	parse_loop(t_data *img, char *line, int row, int prev_row_length)
{
	int	col;

	col = 0;
	while (line[col] == ' ')
	{
		img->world_map[row][col] = 3;
		col++;
	}
	while (col < img->map_width && line[col] != 10)
	{
		if (!is_valid_map_char(line[col]))
			return (ft_printf("%s %c\n", MAP_ERROR_1, line[col]), -1);
		if (check_map_rules(line, row, col, img) == -1
			|| check_more_map_rules(line,
				row, col, prev_row_length) == -1)
			return (-1);
		assign_character_to_map(img, line[col], row, col);
		col++;
	}
	while (col < img->map_width && row < img->map_height)
	{
		img->world_map[row][col] = 3;
		col++;
	}
	return (0);
}

int	parse_map(int file, char *start_of_map, t_data *img)
{
	int		row;
	int		prev_row_length;
	char	*line;

	line = allocate_map(file, start_of_map, img);
	row = 0;
	prev_row_length = 0;
	while (row < img->map_height && line != NULL)
	{
		if (parse_loop(img, line, row, prev_row_length) == -1)
			return (-1);
		prev_row_length = ft_strlen(line);
		row++;
		free(line);
		line = get_next_line(file);
	}
	free(line);
	if (img->num_sprites > 0)
		img->sprites = img->sprite_head;
	return (0);
}
