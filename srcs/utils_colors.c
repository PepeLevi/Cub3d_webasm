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
		return ((num * img->textures[minimap->wall_or_door].img->width) / (180
				/ minimap->vis_width));
	}
	else
	{
		return ((num * img->textures[minimap->wall_or_door].img->height) / (180
				/ minimap->vis_height));
	}
}


#include <stdint.h>

int darken_color(int color, double distance)
{
    int red;
    int green;
    int blue;
    int alpha;
    int darken_factor;
    int darkened_color;

    // Darken factor is scaled to ensure it doesn't overly darken the color
    darken_factor = (int)(distance * 20);

    // Extract red, green, blue, and alpha components from the color
    alpha = (color >> 24) & 0xFF;
    red = (color >> 16) & 0xFF;
    green = (color >> 8) & 0xFF;
    blue = color & 0xFF;

    // Apply the darkening factor uniformly
    red -= darken_factor;
    green -= darken_factor;
    blue -= darken_factor;

    // Ensure the color components are within the valid range
    if (red < 0) red = 0;
    if (green < 0) green = 0;
    if (blue < 0) blue = 0;

    // Combine the darkened components back into a single color value
    darkened_color = (alpha << 24) | (red << 16) | (green << 8) | blue;
    return darkened_color;
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
