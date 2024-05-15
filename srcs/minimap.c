/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:02:13 by emollebr          #+#    #+#             */
/*   Updated: 2024/05/07 18:22:31 by lejimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_visible_area(t_data *img, t_minimap *minimap, int cell_x,
		int cell_y)
{
	int	og_x;
	int	og_y;
	int	color;
	int	i;
	int	j;

	i = -1;
	while (++i < 180 / minimap->vis_width)
	{
		j = -1;
		while (++j < 180 / minimap->vis_height)
		{
			if (!img->textures[minimap->wall_or_door].img)
				color = 0x9e1c1c;
			else
			{
				og_x = get_original_xy(img, minimap, 'x', i);
				og_y = get_original_xy(img, minimap, 'y', j);
				color = ft_get_pixel(img->textures[minimap->wall_or_door].img,
						og_x, og_y);
			}
			//if (ft_get_pixel(img->img, cell_x + i, cell_y + j) != 0)
				mlx_put_pixel(img->img, cell_x + i, cell_y + j, color);
		}
	}
}

void	draw_background(t_data *img, t_minimap *minimap)
{
	int				og_y;
	int				og_x;
	unsigned int	color;
	int				y;
	int				x;

	y = minimap->y;
	while (y < minimap->y + 180)
	{
		x = minimap->x;
		og_y = (y - minimap->y) * img->textures[l_MMBG].img->height / 180;
		while (x < minimap->x + 180)
		{
			og_x = (x - minimap->x) * img->textures[l_MMBG].img->width / 180;
			if (!img->textures[l_MMBG].img)
				color = 0xebe7c5;
			else
				color = ft_get_pixel(img->textures[l_MMBG].img, og_x, og_y);
			if (color != 0)
				mlx_put_pixel(img->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_data *img, t_minimap *minimap)
{
	double	player_angle;
	int		angle;
	int		x;
	int		y;

	minimap->player_x = minimap->x + (int)((img->player.x - minimap->vis_x)
			* (double)180 / minimap->vis_width);
	minimap->player_y = minimap->y + (int)((img->player.y - minimap->vis_y)
			* (double)180 / minimap->vis_height);
	player_angle = atan2(img->player.dir_y, img->player.dir_x);
	angle = 0;
	while (angle < 360)
	{
		x = minimap->player_x + 5 * cos(angle * M_PI / 180.0);
		y = minimap->player_y + 5 * sin(angle * M_PI / 180.0);
		//if (ft_get_pixel(img->img, x, y) != 0)
			mlx_put_pixel(img->img, x, y, 0xffff00);
		angle++;
	}
	minimap->line_end_x = minimap->player_x + 15 * cos(player_angle);
	minimap->line_end_y = minimap->player_y + 15 * sin(player_angle);
	draw_line(img, minimap);
}

void	scale_visible_area(t_data *img, t_minimap minimap, int x, int y)
{
	int		cell_x;
	int		cell_y;
	double	scale;

	scale = get_scale(minimap);
	cell_x = minimap.x + (int)(x * scale);
	cell_y = minimap.y + (int)(y * scale);
	if (minimap.vis_x + x >= 0 && minimap.vis_x + x < img->map_width)
	{
		if (minimap.vis_y + y >= 0 && minimap.vis_y + y < img->map_height)
		{
			if (img->world_map[minimap.vis_y + y][minimap.vis_x + x] == 1
				|| (img->world_map[minimap.vis_y + y][minimap.vis_x + x] == 2
					&& img->doors.is_open == 0))
			{
				if (img->world_map[minimap.vis_y + y][minimap.vis_x + x] == 1)
					minimap.wall_or_door = l_MMVA;
				if (img->world_map[minimap.vis_y + y][minimap.vis_x + x] == 2)
					minimap.wall_or_door = 16;
				draw_visible_area(img, &minimap, cell_x, cell_y);
			}
		}
	}
}

void	render_minimap(t_data *img)
{
	t_minimap	minimap;
	int			x;
	int			y;

	minimap.x = 36;
	minimap.y = HEIGHT - 185;
	calculate_visible_area(img, &minimap);
	draw_background(img, &minimap);
	draw_player(img, &minimap);
	y = 0;
	while (y < minimap.vis_height && minimap.vis_y + y < img->map_height)
	{
		x = 0;
		while (x < minimap.vis_width && minimap.vis_x + x < img->map_width)
		{
			scale_visible_area(img, minimap, x, y);
			x++;
		}
		y++;
	}
}
