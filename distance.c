/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 04:24:48 by thverney          #+#    #+#             */
/*   Updated: 2019/12/12 04:25:39 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_distance(t_map *tab)
{
	if (tab->len.side == 0)
		tab->len.perpWallDist = fabs((((double)tab->map_x - tab->pos_x + (1 - tab->len.stepX) / 2) / tab->len.rayDirX));
	else
		tab->len.perpWallDist = fabs((((double)tab->map_y - tab->pos_y + (1 - tab->len.stepY) / 2) / tab->len.rayDirY));
	tab->len.heightline = (tab->key.sprint ? abs((int)((double)tab->len.h / tab->len.perpWallDist)) * 1.35 :
	abs((int)((double)tab->len.h / tab->len.perpWallDist)) * 1.7);
	tab->len.ray_start = (int)(-(tab->len.heightline / 2) + tab->len.h / 2);
	tab->len.ray_end = (int)((tab->len.heightline / 2) + tab->len.h / 2);
	
	if (tab->len.ray_start < 0)
		tab->len.ray_start = 0;
	if (tab->len.ray_end >= tab->len.h)
		tab->len.ray_end = tab->len.h - 1;
}

void		calc_dist_xy(t_map *tab)
{
	if (tab->len.rayDirX < 0)
	{
		tab->len.stepX = -1;
		tab->len.sideDistX = (tab->pos_x - tab->map_x) * tab->len.deltaDistX; 
	}
	else
	{
		tab->len.stepX = 1;
		tab->len.sideDistX = (tab->map_x + 1.0 - tab->pos_x) * tab->len.deltaDistX;
	}
	if (tab->len.rayDirY < 0)
	{
		tab->len.stepY = -1;
		tab->len.sideDistY = (tab->pos_y - tab->map_y) * tab->len.deltaDistY; 
	}
	else
	{
		tab->len.stepY = 1;
		tab->len.sideDistY = (tab->map_y + 1.0 - tab->pos_y) * tab->len.deltaDistY;
	}
}
void		ft_init_ray(t_map *tab)
{
	(tab->angle < 0 ? tab->angle += 360 : 0);
	(tab->angle > 360 ? tab->angle -= 360 : 0);
	tab->len.w = tab->res_x;
	tab->len.h = tab->res_y;
	tab->len.cameraX = (2 * (double)tab->len.x / (double)tab->len.w) - 1;
	if (tab->key.sprint)
	{
		tab->len.rayDirX = cos((tab->angle + (40 * tab->len.cameraX)) * (M_PI / 180));
		tab->len.rayDirY = sin((tab->angle + (40 * tab->len.cameraX)) * (M_PI / 180));
	}
	else if (tab->key.fovgod)
	{
		tab->len.rayDirX = cos((tab->angle + (180 * tab->len.cameraX)) * (M_PI / 180));
		tab->len.rayDirY = sin((tab->angle + (180 * tab->len.cameraX)) * (M_PI / 180));
	}
	else
	{
		tab->len.rayDirX = cos((tab->angle + (30 * tab->len.cameraX)) * (M_PI / 180));
		tab->len.rayDirY = sin((tab->angle + (30 * tab->len.cameraX)) * (M_PI / 180));
	}
	tab->len.deltaDistX = sqrt(1 + (tab->len.rayDirY * tab->len.rayDirY) / (tab->len.rayDirX * tab->len.rayDirX));
	tab->len.deltaDistY = sqrt(1 + (tab->len.rayDirX * tab->len.rayDirX) / (tab->len.rayDirY * tab->len.rayDirY));
	tab->len.hit = 0;
	tab->map_x = (int)tab->pos_x;
	tab->map_y = (int)tab->pos_y;
}

void		calc_dist(t_map *tab)
{
	ft_init_ray(tab);
	calc_dist_xy(tab);
	while (tab->len.hit == 0) 
	{
		if (tab->len.sideDistX < tab->len.sideDistY) 
		{
			tab->len.sideDistX += tab->len.deltaDistX;
			tab->map_x += tab->len.stepX;
			tab->len.side = 0;
		}
		else
		{
			tab->len.sideDistY += tab->len.deltaDistY;
			tab->map_y += tab->len.stepY;
			tab->len.side = 1;
		}
		if (tab->map[tab->map_x][tab->map_y] > '0')
			tab->len.hit = 1;
	}
	wall_distance(tab);
}