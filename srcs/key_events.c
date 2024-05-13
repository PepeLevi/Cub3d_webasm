/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:11:37 by lejimene          #+#    #+#             */
/*   Updated: 2024/05/13 16:05:34 by lejimene         ###   ########.fr       */
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

void key_hook(void *param) {
    t_data *img = param;
    t_keys *keys = img->keys;

    handle_player_movement(keys, img);
    ////memset(img->addr, 0, WIDTH * HEIGHT * (img->bits_per_pixel / 8));
    if (cast_rays(img) == -1)
        return (free_all(img));
    update_image(img, keys);
    return;
}

void mouse_motion(double x, double y, void *param) {
    t_keys *keys = (t_keys *)param;

    double rotation_speed;
    double olddir_x;
    double oldplane_x;

    if (y != -1 && keys->space)
    {
        rotation_speed = 0.0002 * (x - WIDTH / 2);
        olddir_x = keys->img->player.dir_x;
        keys->img->player.dir_x = keys->img->player.dir_x * cos(rotation_speed)
            - keys->img->player.dir_y * sin(rotation_speed);
        keys->img->player.dir_y = olddir_x * sin(rotation_speed) + keys->img->player.dir_y
            * cos(rotation_speed);
        oldplane_x = keys->img->player.plane_x;
        keys->img->player.plane_x = keys->img->player.plane_x * cos(rotation_speed)
            - keys->img->player.plane_y * sin(rotation_speed);
        keys->img->player.plane_y = oldplane_x * sin(rotation_speed)
            + keys->img->player.plane_y * cos(rotation_speed);
        mlx_set_mouse_pos(keys->img->mlx_win, WIDTH / 2, HEIGHT / 2);
    }
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



void key_press_wrapper(mlx_key_data_t key_data, void *param) {
    int keycode = key_data.key;
    t_data *img = (t_data *)param;
    key_press(keycode, img);
}

// Adjust the signature of key_press to match mlx_keyfunc
void key_press(int keycode, t_data *img) {
    t_keys *keys = img->keys;
    
    keys->w = mlx_is_key_down(img->mlx_win, MLX_KEY_W);
    keys->s = mlx_is_key_down(img->mlx_win, MLX_KEY_S);
    keys->a = mlx_is_key_down(img->mlx_win, MLX_KEY_A);
    keys->d = mlx_is_key_down(img->mlx_win, MLX_KEY_D);
    keys->left = mlx_is_key_down(img->mlx_win, MLX_KEY_LEFT);
    keys->right = mlx_is_key_down(img->mlx_win, MLX_KEY_RIGHT);
    
    if (mlx_is_key_down(img->mlx_win, MLX_KEY_SPACE))
        key_space(keys);
    
    keys->q = mlx_is_key_down(img->mlx_win, MLX_KEY_Q);
    if (keys->q && img->world_map[(int)img->player.y][(int)img->player.x] != 2)
        img->doors.is_open = !img->doors.is_open;
    
    if (mlx_is_key_down(img->mlx_win, MLX_KEY_ESCAPE))
        close_program(img);
}

