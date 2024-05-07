/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:21:29 by emollebr          #+#    #+#             */
/*   Updated: 2024/05/07 17:22:47 by lejimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	get_scale(t_minimap minimap)
{
	if (minimap.vis_width < minimap.vis_height)
		return (180.0 / minimap.vis_width);
	else
		return (180.0 / minimap.vis_height);
}

int	get_original_xy(t_data *img, t_minimap *minimap, int xy, int num)
{
	if (xy == 'x')
	{
		return ((num * img->textures[minimap->wall_or_door].width) / (180
				/ minimap->vis_width));
	}
	else
	{
		return ((num * img->textures[minimap->wall_or_door].height) / (180
				/ minimap->vis_height));
	}
}

int get_texture_color(t_texture texture, int x, int y)
{

	    if (texture.img == NULL) {
        // Handle the case where texture.img is NULL
        // For example, return a default color or report an error
        return 0; // Replace DEFAULT_COLOR with your desired default color
    }
    // Access the mlx_texture_t structure within texture.img and retrieve the color
    mlx_texture_t mlx_texture = *texture.img;

    // Calculate the index of the pixel in the pixel array
    int index = (y * mlx_texture.width + x) * mlx_texture.bytes_per_pixel;

    // Ensure that the index is within the bounds of the pixel array
    if (index < 0 || index >= mlx_texture.width * mlx_texture.height * mlx_texture.bytes_per_pixel) {
        // Handle out-of-bounds access
        // For example, return a default color or report an error
        return 0; // Replace DEFAULT_COLOR with your desired default color
    }

    // Access the pixel data at the calculated index
    uint8_t* pixel = &(mlx_texture.pixels[index]);

    // Assuming RGBA pixel format (4 bytes per pixel), construct the color
    // You may need to adjust this based on the actual pixel format
    uint32_t color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | (pixel[3]);

    return color;
}


int	darken_color(int color, double distance)
{
	int	red;
	int	green;
	int	blue;
	int	darken_factor;
	int	darkened_color;

	darken_factor = (int)(distance * 10);
	red = ((color >> 16) & 0xFF) - darken_factor;
	green = ((color >> 8) & 0xFF) - darken_factor;
	blue = (color & 0xFF) - darken_factor;
	if (red < 0)
		red = 0;
	else if (red > 255)
		red = 255;
	if (green < 0)
		green = 0;
	else if (green > 255)
		green = 255;
	if (blue < 0)
		blue = 0;
	else if (blue > 255)
		blue = 255;
	darkened_color = (red << 16) | (green << 8) | blue;
	return (darkened_color);
}

t_color	apply_light(t_color color, double distance)
{
	double	attenuation_factor;

	attenuation_factor = 1.0 / distance;
	color.r *= attenuation_factor;
	color.g *= attenuation_factor;
	color.b *= attenuation_factor;
	color.r = fmax(0.0, fmin(1.0, color.r));
	color.g = fmax(0.0, fmin(1.0, color.g));
	color.b = fmax(0.0, fmin(1.0, color.b));
	return (color);
}
