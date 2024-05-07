/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:58:08 by emollebr          #+#    #+#             */
/*   Updated: 2024/05/07 18:22:31 by lejimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_line_values(t_minimap *minimap, int *d, int *s)
{
	d[0] = abs(minimap->line_end_x - minimap->player_x);
	d[1] = abs(minimap->line_end_y - minimap->player_y);
	if (minimap->player_x < minimap->line_end_x)
		s[0] = 1;
	else
		s[0] = -1;
	if (minimap->player_y < minimap->line_end_y)
		s[1] = 1;
	else
		s[1] = -1;
}

void	draw_line(t_data *img, t_minimap *minimap)
{
	int	d[2];
	int	s[2];
	int	err;
	int	err2;

	get_line_values(minimap, d, s);
	err = d[0] - d[1];
	while (1)
	{
		//if (ft_get_pixel(img->img, minimap->player_x, minimap->player_y) != 0)
			mlx_put_pixel(img->img, minimap->player_x, minimap->player_y, 0xffff00);
		if (minimap->player_x == minimap->line_end_x
			&& minimap->player_y == minimap->line_end_y)
			break ;
		err2 = 2 * err;
		if (err2 > -d[1])
		{
			err -= d[1];
			minimap->player_x += s[0];
		}
		if (err2 < d[0])
		{
			err += d[0];
			minimap->player_y += s[1];
		}
	}
}

void	calculate_visible_area(t_data *img, t_minimap *minimap)
{
	if (img->map_height < 10 || img->map_width < 10)
	{
		minimap->vis_width = img->map_width;
		minimap->vis_height = img->map_height;
	}
	else
	{
		minimap->vis_width = 10;
		minimap->vis_height = 10;
	}
	minimap->vis_x = img->player.x - minimap->vis_width / 2;
	minimap->vis_y = img->player.y - minimap->vis_height / 2;
	if (minimap->vis_x < 0)
		minimap->vis_x = 0;
	if (minimap->vis_y < 0)
		minimap->vis_y = 0;
	if (minimap->vis_x + minimap->vis_width > img->map_width)
		minimap->vis_x = img->map_width - minimap->vis_width;
	if (minimap->vis_y + minimap->vis_height > img->map_height)
		minimap->vis_y = img->map_height - minimap->vis_height;
}
