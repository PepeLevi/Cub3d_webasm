/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:13:20 by lejimene          #+#    #+#             */
/*   Updated: 2024/01/26 15:18:34 by lejimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	perform_dda_doors(t_ray *ray, t_data *img)
{
	ray->hit = 0;
	while (ray->hit == 0 && ray->map_x > 0 && ray->map_y > 0)
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
		if (img->world_map[ray->map_y][ray->map_x] == 2)
			ray->hit = 2;
	}
	return (0);
}

void	draw_textured_walls_and_update_doors(t_data *img, t_ray *ray, int x)
{
	if (ray->hit == 2)
		if (draw_doors(img, &img->doors, x, ray) == -1)
			exit(EXIT_FAILURE);
	ray->hit = 0;
	img->z_buffer[x] = ray->perp_wall_dist;
	x++;
}

int	cast_rays_doors(t_data *img)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		initialize_ray(&ray, img, x);
		calculate_side_distances(&ray, img);
		perform_dda_doors(&ray, img);
		calculate_perp_wall_dist(&ray, img);
		draw_textured_walls_and_update_doors(img, &ray, x);
		x++;
	}
	return (0);
}
