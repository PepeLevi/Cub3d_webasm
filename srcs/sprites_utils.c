/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:42:28 by lejimene          #+#    #+#             */
/*   Updated: 2024/01/29 16:44:22 by lejimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	compare_sprite_distance(const void *a, const void *b)
{
	double	distance_a;
	double	distance_b;

	distance_a = ((t_sprite_info *)a)->distance;
	distance_b = ((t_sprite_info *)b)->distance;
	if (distance_a < distance_b)
		return (-1);
	else if (distance_a > distance_b)
		return (1);
	else
		return (0);
}

void	sort_sprites(int *order, double *dist, int amount)
{
	int		i;
	double	**sprites;

	i = -1;
	sprites = ft_calloc(sizeof(double), amount);
	while (++i < amount)
		sprites[i] = ft_calloc(sizeof(double), 2);
	i = -1;
	while (++i < amount)
	{
		sprites[i][0] = dist[i];
		sprites[i][1] = order[i];
	}
	qsort(sprites, amount, sizeof(sprites[0]), compare_sprite_distance);
	i = -1;
	while (++i < amount)
	{
		dist[i] = sprites[amount - i - 1][0];
		order[i] = (int)sprites[amount - i - 1][1];
	}
	i = -1;
	while (++i < amount)
		free(sprites[i]);
	free(sprites);
}

void	initialize_sprite_data(t_sprite_data *s, t_sprite *sprite, t_data *img)
{
	s->sprite_x = sprite->x - img->player.x;
	s->sprite_y = sprite->y - img->player.y;
	s->inv_det = 1.0 / (img->player.plane_x * img->player.dir_y
			- img->player.dir_x * img->player.plane_y);
	s->transform_x = s->inv_det * (img->player.dir_y * s->sprite_x
			- img->player.dir_x * s->sprite_y);
	s->transform_y = s->inv_det * (-img->player.plane_y * s->sprite_x
			+ img->player.plane_x * s->sprite_y);
	s->sprite_screen_x = (int)((WIDTH / 2) * (1 + s->transform_x
				/ s->transform_y));
	s->sprite_height = abs((int)(HEIGHT / s->transform_y));
	s->sprite_width = abs((int)(WIDTH / s->transform_y));
	s->draw_start_y = -s->sprite_height / 2 + HEIGHT / 2;
	if (s->draw_start_y < 0)
		s->draw_start_y = 0;
	s->draw_end_y = s->sprite_height / 2 + HEIGHT / 2;
	if (s->draw_end_y >= HEIGHT)
		s->draw_end_y = HEIGHT - 1;
	s->draw_start_x = -s->sprite_width / 2 + s->sprite_screen_x;
	if (s->draw_start_x < 0)
		s->draw_start_x = 0;
	s->draw_end_x = s->sprite_width / 2 + s->sprite_screen_x;
	if (s->draw_end_x > WIDTH)
		s->draw_end_x = WIDTH;
}
