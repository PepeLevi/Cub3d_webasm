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
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

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

void initialize(t_data **img, t_keys **keys){

    *img = malloc(sizeof(t_data));
	*keys = malloc(sizeof(t_keys));

    if (!(*img) || !(*keys)) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    (*keys)->is_mouse_locked = 0;
    (*keys)->img = *img;
    (*keys)->w = (*keys)->s = (*keys)->a = (*keys)->d = (*keys)->left = (*keys)->right = (*keys)->q = false;
    (*img)->world_map = NULL;

    initialize_doors(*img);
    if (parse_cub_file("test.cub", *img) == -1) {
        fprintf(stderr, "Failed to parse cub file\n");
        free(*img);
        free(*keys);
        exit(EXIT_FAILURE);
    }

    initialize_mlx_window(*img);
    load_textures(*img);;
    (*img)->player.old_player_x = (*img)->player.x;
    (*img)->player.old_player_y = (*img)->player.y;
    initialize_z_buffer(*img);
    (*keys)->img = *img;
    (*img)->keys = *keys;

    // Set up event handlers
    //emscripten_set_keydown_callback("#canvas", img, true, (em_key_callback_func)key_press_wrapper);
    //emscripten_set_mousemove_callback("#canvas", &keys, true, (em_mouse_callback_func)mouse_motion);
    mlx_key_hook((*img)->mlx_win, &key_press_wrapper, *img);
    //mlx_cursor_hook((*img)->mlx_win, &mouse_motion, *img);
    mlx_loop_hook((*img)->mlx_win, &key_hook, *img);

}
// Function to run the main loop
void emscripten_main_loop() {
    static t_data *img = NULL;
    static t_keys *keys = NULL;

    if (!img || !keys) {
        initialize(&img, &keys);
    }

    //key_hook(img);

    mlx_loop(img->mlx_win);
}


int	main(int argc, char **argv)
{

    // Set up the main loop
    emscripten_set_main_loop(emscripten_main_loop, 0, true);

    // Clean up
    //free_all(img);
}
