/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:10:59 by lejimene          #+#    #+#             */
/*   Updated: 2024/01/26 17:46:28 by lejimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	handle_collision(t_data *img, double oldplayer_x, double oldplayer_y)
{
	if (img->world_map[(int)oldplayer_y][(int)img->player.x] == 1
		|| (img->world_map[(int)img->player.y][(int)img->player.x] == 2
			&& !img->doors.is_open))
		img->player.x = oldplayer_x;
	if (img->world_map[(int)img->player.y][(int)oldplayer_x] == 1
		|| (img->world_map[(int)img->player.y][(int)img->player.x] == 2
			&& !img->doors.is_open))
		img->player.y = oldplayer_y;
}

void	move_player(t_data *img, double mov_speed, int direction)
{
	double	oldplayer_x;
	double	oldplayer_y;

	oldplayer_x = img->player.x;
	oldplayer_y = img->player.y;
	if (direction == 'w')
	{
		img->player.x += img->player.dir_x * mov_speed;
		img->player.y += img->player.dir_y * mov_speed;
	}
	else if (direction == 's')
	{
		img->player.x -= img->player.dir_x * mov_speed;
		img->player.y -= img->player.dir_y * mov_speed;
	}
	handle_collision(img, oldplayer_x, oldplayer_y);
}

void	strafe_player(t_data *img, double mov_speed, int direction)
{
	img->player.old_player_x = img->player.x;
	img->player.old_player_y = img->player.y;
	if (direction == 'a')
	{
		img->player.x -= img->player.plane_x * mov_speed;
		img->player.y -= img->player.plane_y * mov_speed;
	}
	else if (direction == 'd')
	{
		img->player.x += img->player.plane_x * mov_speed;
		img->player.y += img->player.plane_y * mov_speed;
	}
	handle_collision(img, img->player.old_player_x, img->player.old_player_y);
}

void	rotate_player(t_data *img, double rot_speed, int direction)
{
	double	olddir_x;
	double	oldplane_x;
	double	cos_rot;
	double	sin_rot;

	olddir_x = img->player.dir_x;
	oldplane_x = img->player.plane_x;
	img->player.old_player_x = img->player.x;
	img->player.old_player_y = img->player.y;
	if (direction == 'a')
	{
		cos_rot = cos(-rot_speed);
		sin_rot = sin(-rot_speed);
	}
	else
	{
		cos_rot = cos(rot_speed);
		sin_rot = sin(rot_speed);
	}
	img->player.dir_x = olddir_x * cos_rot - img->player.dir_y * sin_rot;
	img->player.dir_y = olddir_x * sin_rot + img->player.dir_y * cos_rot;
	img->player.plane_x = oldplane_x * cos_rot - img->player.plane_y * sin_rot;
	img->player.plane_y = oldplane_x * sin_rot + img->player.plane_y * cos_rot;
	handle_collision(img, img->player.old_player_x, img->player.old_player_y);
}

void	handle_player_movement(t_keys *keys, t_data *img)
{
	double	mov_speed;
	double	rot_speed;

	mov_speed = MOV_SPEED;
	rot_speed = ROT_SPEED;
	if (keys->w)
		move_player(img, mov_speed, 'w');
	if (keys->s)
		move_player(img, mov_speed, 's');
	if (keys->a)
		strafe_player(img, mov_speed, 'a');
	if (keys->d)
		strafe_player(img, mov_speed, 'd');
	if (keys->left)
		rotate_player(img, rot_speed, 'a');
	if (keys->right)
		rotate_player(img, rot_speed, 'd');
}
