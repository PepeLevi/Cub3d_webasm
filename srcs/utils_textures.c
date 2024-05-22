/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:08:54 by emollebr          #+#    #+#             */
/*   Updated: 2024/05/13 17:10:46 by lejimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_file_paths(t_data *img)
{
	img->textures[8].path = ft_strdup("./images/1c.png");
	img->textures[9].path = ft_strdup("./images/2c.png");
	img->textures[10].path = ft_strdup("./images/3c.png");
	img->textures[11].path = ft_strdup("./images/4c.png");
	img->textures[12].path = ft_strdup("./images/5c.png");
	img->textures[13].path = ft_strdup("./images/6c.png");
	img->textures[14].path = ft_strdup("./images/8c.png");
	img->textures[15].path = ft_strdup("./images/9c.png");
	img->textures[16].path = ft_strdup("./images/door1.png");
	img->textures[17].path = ft_strdup("./images/door2.png");
	img->textures[18].path = ft_strdup("./images/door3.png");
	img->textures[19].path = ft_strdup("./images/door4.png");
	img->textures[20].path = ft_strdup("./images/door5.png");
	img->textures[21].path = ft_strdup("./images/door6.png");
	img->textures[22].path = NULL;
}

void	load_sprites_and_doors(t_data *img)
{
	int	i;

	i = 0;
	while (i < 22)
	{
		if (img->textures[i].path != NULL && access(img->textures[i].path,
				O_RDONLY) == 0)
		{
			img->textures[i].img = mlx_load_png(img->textures[i].path);
		}
		i++;
	}
}

void	load_minimap_textures(t_data *img, t_texture *bg, t_texture *va)
{

	bg->addr = NULL;
	va->addr = NULL;
	if (access("./images/11.png", O_RDONLY) == 0)
	{
		bg->img = mlx_load_png("./images/11.png");
	}
	if (access("./images/4.png", O_RDONLY) == 0)
	{
		img->textures[l_F].img = mlx_load_png("./images/4.png");
		img->textures[l_C].img = mlx_load_png("./images/4.png");
		va->img = mlx_load_png("./images/4.png");
	}
}

void	load_textures(t_data *img)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (img->textures[i].path)
		{
			img->textures[i].img = mlx_load_png(img->textures[i].path);
		}
		i++;
	}
	load_minimap_textures(img, &img->textures[l_MMBG], &img->textures[l_MMVA]);
	get_file_paths(img);
	load_sprites_and_doors(img);
}

