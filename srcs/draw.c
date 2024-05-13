/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:55:36 by emollebr          #+#    #+#             */
/*   Updated: 2024/05/13 17:53:45 by lejimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_textured_wall(t_data *img, t_ray *ray, int x)
{
	int				tex_num;
	double			wall_x;
	int				y;
	unsigned int	tex[2];
	unsigned int	color;

	tex[0] = calculate_wall_values(ray, img, &tex_num, &wall_x);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex[1] = (((y * 256 - HEIGHT * 128 + ray->line_height * 128)
					* img->textures[tex_num].img->height) / ray->line_height) / 256;
		tex[1] = fmin(fmax(tex[1], 0), img->textures[tex_num].img->height - 1);
		color = ft_get_pixel(img->textures[tex_num].img, (int)tex[0],
				(int)tex[1]);
		color = darken_color(color, ray->perp_wall_dist);
		if (color != 0)
			mlx_put_pixel(img->img, x, y, color);
		y++;
	}
}

void	initialize_floor_values(t_data *img, int y,
		t_floor_values *floor_values)
{
	floor_values->ray_dir_x0 = img->player.dir_x - img->player.plane_x;
	floor_values->ray_dir_y0 = img->player.dir_y - img->player.plane_y;
	floor_values->ray_dir_x1 = img->player.dir_x + img->player.plane_x;
	floor_values->ray_dir_y1 = img->player.dir_y + img->player.plane_y;
	floor_values->p = y - HEIGHT / 2;
	floor_values->pos_z = 0.5 * HEIGHT;
	floor_values->row_distance = floor_values->pos_z / floor_values->p;
	floor_values->floor_step_x = floor_values->row_distance
		* (floor_values->ray_dir_x1 - floor_values->ray_dir_x0) / WIDTH;
	floor_values->floor_step_y = floor_values->row_distance
		* (floor_values->ray_dir_y1 - floor_values->ray_dir_y0) / WIDTH;
	floor_values->floor_x = img->player.x + floor_values->row_distance
		* floor_values->ray_dir_x0;
	floor_values->floor_y = img->player.y + floor_values->row_distance
		* floor_values->ray_dir_y0;
	floor_values->tex_width_f = img->textures[l_F].img->width;
	floor_values->tex_height_f = img->textures[l_F].img->height;
	floor_values->ceil_tex_width_c = img->textures[l_C].img->width;
	floor_values->ceil_tex_height_c = img->textures[l_C].img->height;
	floor_values->x = 0;
}

void	calculate_floor_values(t_floor_values *floor_values)
{
	floor_values->cell_x = (int)floor_values->floor_x;
	floor_values->cell_y = (int)floor_values->floor_y;
	floor_values->tx = (int)((floor_values->floor_x - floor_values->cell_x)
			* floor_values->tex_width_f) & (floor_values->tex_width_f - 1);
	floor_values->ty = (int)((floor_values->floor_y - floor_values->cell_y)
			* floor_values->tex_height_f) & (floor_values->tex_height_f - 1);
	floor_values->ceil_tx = (int)((floor_values->floor_x - floor_values->cell_x)
			* floor_values->ceil_tex_width_c) & (floor_values->ceil_tex_width_c
			- 1);
	floor_values->ceil_ty = (int)((floor_values->floor_y - floor_values->cell_y)
			* floor_values->ceil_tex_height_c)
		& (floor_values->ceil_tex_height_c - 1);
	floor_values->floor_x += floor_values->floor_step_x;
	floor_values->floor_y += floor_values->floor_step_y;
}

void	draw_floor_pixel(t_data *img, t_floor_values *floor_values)
{
	if (ft_get_pixel(img->textures[l_F].img,
				floor_values->tx, floor_values->ty) != 0)
		floor_values->floor_color = ft_get_pixel(img->textures[l_F].img,
				floor_values->tx, floor_values->ty);
	if (ft_get_pixel(img->textures[l_C].img,
				floor_values->ceil_tx, floor_values->ceil_ty) != 0)
		floor_values->ceil_color = ft_get_pixel(img->textures[l_C].img,
				floor_values->ceil_tx, floor_values->ceil_ty);
	floor_values->floor_color = darken_color(floor_values->floor_color,
			(double)floor_values->row_distance);
	floor_values->ceil_color = darken_color(floor_values->ceil_color,
			(double)floor_values->row_distance);
}

void draw_textured_floor(t_data *param) {
    int y;
    t_floor_values floor_values;
	t_data *img = param;

    y = HEIGHT / 2 + 1;
    while (y < HEIGHT) {
        initialize_floor_values(img, y, &floor_values);
        while (floor_values.x < WIDTH) {
            calculate_floor_values(&floor_values);
            draw_floor_pixel(img, &floor_values);
    
            if (floor_values.floor_color != 0)
                mlx_put_pixel(img->img, floor_values.x, y, floor_values.floor_color);
            if (floor_values.ceil_color != 0)
                mlx_put_pixel(img->img, floor_values.x, HEIGHT - y - 1, floor_values.ceil_color);
            
            floor_values.x++;
        }
        y++;
    }
}

