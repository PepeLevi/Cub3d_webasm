/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:11:37 by lejimene          #+#    #+#             */
/*   Updated: 2024/05/14 19:48:39 by lejimene         ###   ########.fr       */
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
    img->tmp_img = img->img;
   img->img = mlx_new_image(img->mlx_win, WIDTH, HEIGHT);
    handle_player_movement(keys, img);
    ////memset(img->addr, 0, WIDTH * HEIGHT * (img->bits_per_pixel / 8));
    if (cast_rays(img) == -1)
        return (free_all(img));
    update_image(img, keys);
    mlx_delete_image(img->mlx_win, img->tmp_img);
    mlx_image_to_window(img->mlx_win, img->img, 0, 0);
    return;
}

int mouse_motion(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData) {
    t_keys *keys = (t_keys *)userData;

    double rotation_speed;
    double olddir_x;
    double oldplane_x;

    if (mouseEvent->clientY != -1 && keys->space) {
        rotation_speed = 0.0002 * (mouseEvent->clientX - WIDTH / 2);
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
    return EM_TRUE;
}
void	key_space(t_keys *keys, t_data *img)
{
	keys->space = !keys->space;
	if (keys->space)
	{
		mlx_set_cursor_mode(img->mlx_win, MLX_MOUSE_DISABLED);
		mlx_set_mouse_pos(img->mlx_win, WIDTH / 2, HEIGHT / 2);
	}
	else
		mlx_set_cursor_mode(img->mlx_win, MLX_MOUSE_NORMAL);
}


void key_press_wrapper(mlx_key_data_t keydata, void *userData) {
    t_data *img = (t_data *)userData;
    key_press(4, img);
    //return EM_TRUE;
}
// Adjust the signature of key_press to match mlx_keyfunc
void key_press(int keycode, t_data *img) {
    t_keys *keys = img->keys;
    keys->img = img;
    
    keys->w = mlx_is_key_down(img->mlx_win, MLX_KEY_W);
    keys->s = mlx_is_key_down(img->mlx_win, MLX_KEY_S);
    keys->a = mlx_is_key_down(img->mlx_win, MLX_KEY_A);
    keys->d = mlx_is_key_down(img->mlx_win, MLX_KEY_D);
    keys->left = mlx_is_key_down(img->mlx_win, MLX_KEY_LEFT);
    keys->right = mlx_is_key_down(img->mlx_win, MLX_KEY_RIGHT); 
    
    keys->q = mlx_is_key_down(img->mlx_win, MLX_KEY_Q);
    if (keys->q && img->world_map[(int)img->player.y][(int)img->player.x] != 2)
        img->doors.is_open = !img->doors.is_open;
    
}
