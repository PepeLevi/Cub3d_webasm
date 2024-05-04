/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:15:39 by lejimene          #+#    #+#             */
/*   Updated: 2024/05/04 19:51:45 by lejimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

int	close_program(t_data *img)
{
	free_all(img);
	mlx_delete_image(img->mlx_win, img->img);
	mlx_terminate(img->mlx_win);
	mlx_close_window(img->mlx_win);
	free(img->mlx_win);
	exit(0);
}

int	render_frame(t_data *img)
{
	memset(img->addr, 0, WIDTH * HEIGHT * (img->bits_per_pixel / 8));
	if (cast_rays(img) == -1)
		return (free_all(img), -1);
	update_image(img, &img->keys);
	key_hook(&img->keys);
	return (0);
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

void	free_all(t_data *img)
{
	int			i;

	i = -1;
	if (img->world_map != NULL)
	{
		while (++i < img->map_height)
			free(img->world_map[i]);
		free(img->world_map);
	}
	i = -1;
	while (++i < 23)
	{
		if (img->textures[i].img != NULL)
		{
			mlx_delete_image(img->mlx_win, img->textures[i].img);
			free(img->textures[i].path);
		}
	}
	free_sprites(img->sprites);
	return ;
}

int	main(int argc, char **argv)
{
	t_data	img;
	t_keys	keys;

	if (argc != 2)
		return (ft_printf("Enter .cub file as argument\n"), -1);
	keys.is_mouse_locked = 0;
	keys.img = &img;
	img.world_map = NULL;
	initialize_doors(&img);
	if (parse_cub_file(argv[1], &img) == -1)
		return (free_all(&img), -1);
	initialize_mlx_window(&img);
	load_textures(&img);
	img.player.old_player_x = img.player.x;
	img.player.old_player_y = img.player.y;
	initialize_z_buffer(&img);
	setup_mlx_hooks(&img, &keys);
	mlx_loop(img.mlx_win);
	free_all(&img);
	mlx_terminate(img.mlx_win);
	mlx_delete_image(img.mlx_win, img.img);
	return (0);
}
