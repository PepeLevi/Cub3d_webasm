/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:34:09 by lejimene          #+#    #+#             */
/*   Updated: 2024/05/14 20:00:54 by lejimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#include <stdint.h>



// Function to get the address of the pixel data buffer
uint32_t* mlx_get_data_addr(mlx_image2_t* img, int* bits_per_pixel, int* line_length, int* endian) {
    if (img == NULL) {
        return NULL;
    }

    if (bits_per_pixel != NULL) {
        *bits_per_pixel = img->bpp;
    }

    if (line_length != NULL) {
        *line_length = img->size_line;
    }

    if (endian != NULL) {
        *endian = img->endian;
    }

    return img->data;
}

void	ft_sprintf(char *relative_path, int current_anim_frame)
{
	char	*base_path;
	char	*num_str;
	int		j;
	int		k;

	base_path = ft_strdup("./images/bicho/bicho");
	if (current_anim_frame < 5)
		num_str = ft_itoa(current_anim_frame + 1);
	else
		num_str = ft_itoa(1);
	j = 0;
	k = -1;
	while (base_path[++k] != '\0')
		relative_path[j++] = base_path[k];
	k = -1;
	while (num_str[++k] != '\0')
		relative_path[j++] = num_str[k];
	relative_path[j++] = '.';
	relative_path[j++] = 'p';
	relative_path[j++] = 'n';
	relative_path[j++] = 'g';
	relative_path[j] = '\0';
	free(num_str);
	free(base_path);
}

void	draw_overlay_image(t_data *img, mlx_texture_t *overlay_img, int overlay_width,
		int overlay_height)
{
	unsigned int	color;
	int	x;
	int	y;

	y = 0;
	while (++y < overlay_img->height)
	{
		x = 0;
		while (++x < overlay_img->width)
		{
			color = ft_get_pixel(overlay_img, x, y);
			//printf("%i\n", color);
			if (color != -256 && color != 0)
				mlx_put_pixel(img->img, x, y, color);
		}
	}
}

void	*tumor_anim(t_data *img, int *img_width, int *img_height)
{
	mlx_texture_t	*image;
	char	relative_path[50];

	ft_sprintf(relative_path, img->current_anim_frame + 1);
	image = mlx_load_png(relative_path);
	return (image);
}

mlx_texture_t	*load_overlay_image(t_data *img, t_keys *keys, int *img_width,
		int *img_height)
{
	char	*relative_path;
	mlx_texture_t	*tmp;

	if (keys->q)
		relative_path = "./images/divine.png";
	else if (keys->w || keys->s)
		relative_path = "./images/headed2.png";
	else if (keys->a)
		relative_path = "./images/headedleft.png";
	else if (keys->d)
		relative_path = "./images/headedright.png";
	else
		relative_path = "./images/headed1.png";
	tmp = mlx_load_png(relative_path);
	return (tmp);
}

void	update_image(t_data *img, t_keys *keys)
{
	int				img_width;
	int				img_height;
	mlx_texture_t	*overlay_img[3];

	overlay_img[0] = load_overlay_image(img, keys, &img_width, &img_height);
	overlay_img[1] = mlx_load_png("./images/hbhbjhb.png");
	overlay_img[2] = tumor_anim(img, &img_width, &img_height);
	sync_overlay_images(img, overlay_img, img_width, img_height);
}
