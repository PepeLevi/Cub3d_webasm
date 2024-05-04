/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:38:15 by emollebr          #+#    #+#             */
/*   Updated: 2024/02/02 13:38:17 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculate_side_distances(t_ray *ray, t_data *img)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (img->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - img->player.x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (img->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - img->player.y)
			* ray->delta_dist_y;
	}
}

void	perform_dda(t_ray *ray, t_data *img)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (img->world_map[ray->map_y][ray->map_x] == 1)
			ray->hit = 1;
	}
}

void	calculate_perp_wall_dist(t_ray *ray, t_data *img)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - img->player.x + (1 - ray->step_x)
				/ 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - img->player.y + (1 - ray->step_y)
				/ 2) / ray->ray_dir_y;
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	draw_textured_walls_and_update(t_data *img, t_ray *ray, int x)
{
	draw_textured_wall(img, ray, x);
	ray->hit = 0;
	img->z_buffer[x] = ray->perp_wall_dist;
	x++;
}

int	cast_rays(t_data *img)
{
	int		x;
	t_ray	ray;

	x = 0;
	draw_textured_floor(img);
	while (x < WIDTH)
	{
		initialize_ray(&ray, img, x);
		calculate_side_distances(&ray, img);
		perform_dda(&ray, img);
		calculate_perp_wall_dist(&ray, img);
		draw_textured_walls_and_update(img, &ray, x);
		x++;
	}
	if (img->doors.door_bool == 1)
	{
		if (cast_rays_doors(img) == -1)
			return (-1);
	}
	if (img->sprites)
	{
		if (draw_sprites(img) == -1)
			return (-1);
	}
	return (0);
}
