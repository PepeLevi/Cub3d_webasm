/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:11:37 by lejimene          #+#    #+#             */
/*   Updated: 2024/05/04 19:46:57 by lejimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_release(int keycode, t_keys *keys)
{
	if (keycode == 119)
		keys->w = false;
	if (keycode == 115)
		keys->s = false;
	if (keycode == 97)
		keys->a = false;
	if (keycode == 100)
		keys->d = false;
	if (keycode == 65361)
		keys->left = false;
	if (keycode == 65363)
		keys->right = false;
	if (keycode == 113)
		keys->q = false;
	return (0);
}

int	key_hook(t_keys *keys)
{
	t_data	*img;

	img = keys->img;
	handle_player_movement(keys, img);
	memset(img->addr, 0, WIDTH * HEIGHT * (img->bits_per_pixel / 8));
	if (cast_rays(img) == -1)
		return (free_all(img), -1);
	update_image(img, keys);
	return (0);
}

int	mouse_motion(int x, int y, t_keys *keys)
{
	t_data	*img;
	double	rotation_speed;
	double	olddir_x;
	double	oldplane_x;

	img = keys->img;
	if (y != -1 && keys->space)
	{
		rotation_speed = 0.0002 * (x - WIDTH / 2);
		olddir_x = img->player.dir_x;
		img->player.dir_x = img->player.dir_x * cos(rotation_speed)
			- img->player.dir_y * sin(rotation_speed);
		img->player.dir_y = olddir_x * sin(rotation_speed) + img->player.dir_y
			* cos(rotation_speed);
		oldplane_x = img->player.plane_x;
		img->player.plane_x = img->player.plane_x * cos(rotation_speed)
			- img->player.plane_y * sin(rotation_speed);
		img->player.plane_y = oldplane_x * sin(rotation_speed)
			+ img->player.plane_y * cos(rotation_speed);
		mlx_set_mouse_pos(keys->img->mlx, WIDTH / 2, HEIGHT / 2);
	}
	return (0);
}

void	key_space(t_keys *keys)
{
	keys->space = !keys->space;
	if (keys->space)
	{
		mlx_set_cursor_mode(keys->img->mlx, MLX_MOUSE_DISABLED);
		mlx_set_mouse_pos(keys->img->mlx, WIDTH / 2, HEIGHT / 2);
	}
	else
		mlx_set_cursor_mode(keys->img->mlx, MLX_MOUSE_NORMAL);
}

int	key_press(int keycode, t_keys *keys)
{
	if (keycode == 119)
		keys->w = true;
	if (keycode == 115)
		keys->s = true;
	if (keycode == 97)
		keys->a = true;
	if (keycode == 100)
		keys->d = true;
	if (keycode == 65361)
		keys->left = true;
	if (keycode == 65363)
		keys->right = true;
	if (keycode == 32)
		key_space(keys);
	if (keycode == 113)
	{
		keys->q = true;
		if (keys->img->world_map[(int)keys->img->player.y]
			[(int)keys->img->player.x] != 2)
			keys->img->doors.is_open = !keys->img->doors.is_open;
	}
	if (keycode == 65307)
        close_program(keys->img);
	return (0);
}
