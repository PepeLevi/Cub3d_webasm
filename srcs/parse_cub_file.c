/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:08:36 by emollebr          #+#    #+#             */
/*   Updated: 2024/05/04 20:22:02 by lejimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	validate_textures(t_data *img, int elems)
{
	while (--elems >= 0)
	{
		if (!img->textures->path && img->textures->rgb == 0)
		{
			ft_printf("Error: Missing texture info in .cub file\n");
			return (-1);
		}
	}
	return (1);
}

unsigned int	calculate_wall_values(t_ray *ray, t_data *img, int *tex_num,
		double *wall_x)
{
	unsigned int	tex_x;

	if (ray->side == 0)
	{
		*wall_x = img->player.y + ray->perp_wall_dist * ray->ray_dir_y;
		*tex_num = (ray->ray_dir_x > 0) * 2 + (ray->ray_dir_x <= 0) * 3;
	}
	else
	{
		*wall_x = img->player.x + ray->perp_wall_dist * ray->ray_dir_x;
		*tex_num = (ray->ray_dir_y > 0) * 0 + (ray->ray_dir_y <= 0) * 1;
	}
	*wall_x -= floor(*wall_x);
	tex_x = (unsigned int)(*wall_x * img->textures[*tex_num].width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		tex_x = img->textures[*tex_num].width - tex_x - 1;
	return (tex_x);
}

void	sync_overlay_images(t_data *img, void **overlay_img, int img_width,
		int img_height)
{
	mlx_image_to_window(img->mlx_win, img->img, 0, 0);
	render_minimap(img);
	draw_overlay_image(img, overlay_img[0], img_width, img_height);
	draw_overlay_image(img, overlay_img[1], img_width, img_height);
	draw_overlay_image(img, overlay_img[2], img_width, img_height);
	mlx_delete_image(img->mlx_win, overlay_img[0]);
	mlx_delete_image(img->mlx_win, overlay_img[1]);
	mlx_delete_image(img->mlx_win, overlay_img[2]);
}


int	parse_cub_file(const char *filename, t_data *img)
{
	int		file;
	char	*start_of_map;

	file = open(filename, O_RDONLY);
	if (!file)
		return (ft_printf("Error: Couldn't open file: %s\n", filename), -1);
	if (parse_textures(file, img) == -1)
		return (-1);
	if (img->textures == NULL)
		return (-1);
	start_of_map = get_map_dimensions(file, img);
	close(file);
	file = open(filename, O_RDONLY);
	if (!file)
		return (ft_printf("Error: Couldn't open file: %s\n", filename), -1);
	if (parse_map(file, start_of_map, img) == -1)
		return (-1);
	if (!validate_map(img))
		return (-1);
	close(file);
	return (0);
}
