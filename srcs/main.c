/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:15:39 by lejimene          #+#    #+#             */
/*   Updated: 2024/05/14 19:30:32 by lejimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

int	close_program(t_data *img)
{
	free_all(img);
	mlx_delete_image(img->mlx_win, img->img);
	mlx_terminate(img->mlx_win);
	exit(0);
}

void	free_sprites(t_sprite *sprites)
{
	t_sprite	*tmp;

	while (sprites != NULL)
	{
		tmp = sprites;
		sprites = sprites->next;
		free(tmp);
	}
	free(sprites);
}

void free_all(t_data *img)
{
    int i;

    // Free world_map if it is not NULL
    if (img->world_map != NULL)
    {
        for (i = 0; i < img->map_height; i++)
        {
            free(img->world_map[i]);
        }
        free(img->world_map);
    }

    // Free textures
    for (i = 0; i < 23; i++)
    {
        if (img->textures[i].img)
        {
            mlx_delete_texture(img->textures[i].img);
            img->textures[i].img = NULL; // Set to NULL to avoid dangling pointers
        }
        if (img->textures[i].path)
        {
            free(img->textures[i].path);
            img->textures[i].path = NULL; // Set to NULL to avoid dangling pointers
        }
    }

    // Free sprites if applicable
    free_sprites(img->sprites);

	    if (img->textures[l_F].img)
    {
        mlx_delete_texture(img->textures[l_F].img);
        img->textures[l_F].img = NULL;
    }
    if (img->textures[l_C].img)
    {
        mlx_delete_texture(img->textures[l_C].img);
        img->textures[l_C].img = NULL;
    }
    if (img->textures[l_MMBG].img)
    {
        mlx_delete_texture(img->textures[l_MMBG].img);
        img->textures[l_MMBG].img = NULL;
    }
    if (img->textures[l_MMVA].img)
    {
        mlx_delete_texture(img->textures[l_MMVA].img);
        img->textures[l_MMVA].img = NULL;
    }
	
    return;
}


int	main(int argc, char **argv)
{
	t_data	*img = malloc(sizeof(t_data));
	t_keys	keys;

	if (argc != 2)
		return (ft_printf("Enter .cub file as argument\n"), -1);
	keys.is_mouse_locked = 0;
	keys.img = img;
	 keys.w = keys.s = keys.a = keys.d = keys.left = keys.right = keys.q = false;
	img->world_map = NULL;
	initialize_doors(img);
	if (parse_cub_file("test.cub", img) == -1)
		return (free_all(img), -1);
	initialize_mlx_window(img);
	load_textures(img);
	img->player.old_player_x = img->player.x;
	img->player.old_player_y = img->player.y;
	initialize_z_buffer(img);
	keys.img = img;
	img->keys = &keys;
	mlx_key_hook(img->mlx_win, &key_press_wrapper, img); // Equivalent to mlx_hook(img->mlx_win, 2, 1L << 0, key_press, keys); // Equivalent to mlx_hook(img->mlx_win, 3, 1L << 1, key_release, keys);
    mlx_cursor_hook(img->mlx_win, &mouse_motion, &keys); // Equivalent to mlx_hook(img->mlx_win, 6, 1L << 6, mouse_motion, keys);
    mlx_loop_hook(img->mlx_win, &key_hook, img);
	mlx_loop(img->mlx_win);
	free_all(img);
	mlx_terminate(img->mlx_win);
	mlx_delete_image(img->mlx_win, img->img);
	return (0);
}
