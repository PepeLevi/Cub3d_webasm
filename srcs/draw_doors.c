/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:13:28 by lejimene          #+#    #+#             */
/*   Updated: 2024/05/07 18:22:31 by lejimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculate_door_parameters(t_ray *ray, t_data *img, t_door *doors)
{
	doors->tex_num = 16 + doors->current_anim_frame;
	if (ray->side == 0)
		doors->wall_x = img->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		doors->wall_x = img->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	doors->wall_x -= floor(doors->wall_x);
	doors->tex_x = (int)(doors->wall_x
			* (double)img->textures[doors->tex_num].width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		doors->tex_x = img->textures[doors->tex_num].width - doors->tex_x - 1;
}

void	draw_door_lines(t_data *img, t_ray *ray, t_door *doors, int x)
{
	int				y;
	unsigned int	color;

	y = ray->draw_start;
	while (++y < ray->draw_end)
	{
		doors->tex_y = (int)(((long long)y * 256 - (long long)HEIGHT * 128
					+ (long long)ray->line_height * 128)
				* img->textures[doors->tex_num].height / ray->line_height)
			/ 256;
		color = *(unsigned int *)(img->textures[doors->tex_num].addr
				+ (doors->tex_y * img->textures[doors->tex_num].line_length
					+ doors->tex_x
					* (img->textures[doors->tex_num].bits_per_pixel / 8)));
		if (color != (unsigned int)0xFF000000)
		{
			color = darken_color(color, ray->perp_wall_dist);
			//if (ft_get_pixel(img->img, x, y) != 0)
				mlx_put_pixel(img->img, x, y, color);
		}
	}
}

void	update_door_animation(t_door *doors)
{
	if (doors->animationspeed > 0)
		doors->animationspeed--;
	if (doors->animationspeed == 0 && doors->current_anim_frame > 0)
	{
		doors->current_anim_frame--;
		doors->animationspeed = 4000;
	}
}

void	update_door_animation_open(t_door *doors)
{
	if (doors->animationspeed > 0)
		doors->animationspeed--;
	if (doors->animationspeed == 0 && !doors->open_)
	{
		doors->animationspeed = 3000;
		doors->current_anim_frame = (doors->current_anim_frame + 1) % 6;
	}
}

int	draw_doors(t_data *img, t_door *doors, int x, t_ray *ray)
{
	if (!doors->is_open)
	{
		calculate_door_parameters(ray, img, doors);
		draw_door_lines(img, ray, doors, x);
		update_door_animation(doors);
		doors->open_ = false;
	}
	else if (doors->is_open)
	{
		calculate_door_parameters(ray, img, doors);
		draw_door_lines(img, ray, doors, x);
		update_door_animation_open(doors);
		if (doors->current_anim_frame == 5)
			doors->open_ = true;
	}
	return (0);
}
