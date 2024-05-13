/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_params.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:33:56 by lejimene          #+#    #+#             */
/*   Updated: 2024/05/07 19:28:25 by lejimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	initialize_ray(t_ray *ray, t_data *img, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = img->player.dir_x + img->player.plane_x * ray->camera_x;
	ray->ray_dir_y = img->player.dir_y + img->player.plane_y * ray->camera_x;
	ray->map_x = (int)img->player.x;
	ray->map_y = (int)img->player.y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->floor_x_step = ray->perp_wall_dist * (ray->ray_dir_y + ray->floor_y);
	ray->floor_y_step = ray->perp_wall_dist * (ray->ray_dir_x + ray->floor_x);
	ray->side = 0;
}

void	initialize_mlx_window(t_data *img)
{
	img->mlx_win = mlx_init(WIDTH, HEIGHT, "42_Yesod", false);
	img->img = mlx_new_image(img->mlx_win, WIDTH, HEIGHT);
}

void	initialize_doors(t_data *img)
{
	int	i;

	img->doors.animation_frame = 0;
	img->doors.open_ = false;
	img->current_anim_frame = 0;
	img->animationspeed = 6;
	img->doors.current_anim_frame = 0;
	img->doors.animationspeed = 3000;
	img->doors.is_open = 0;
	img->doors.door_bool = 0;
	img->num_sprites = 0;
	img->sprites = NULL;
	i = 0;
	while (i < 23)
	{
		img->textures[i].path = NULL;
		img->textures[i].img = NULL;
		i++;
	}
}

void	initialize_z_buffer(t_data *img)
{
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		img->z_buffer[i] = DBL_MAX;
		i++;
	}
}

