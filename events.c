/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 04:27:49 by thverney          #+#    #+#             */
/*   Updated: 2019/12/17 01:37:44 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_move(t_map *tab)
{
	tab->key.speed = (tab->key.sprint == 1 ? 1 : 0.15);
	tab->key.speed = (tab->key.fovgod == 1 ? 0.4 : tab->key.speed);
	if (tab->key.respawn)
	{
		tab->pos_x = tab->len.spawnX;
		tab->pos_y = tab->len.spawnY;
		tab->angle = tab->len.spawnAngle;
	}
	if (tab->key.rotL)
		tab->angle -= (tab->key.fovgod == 1 ? 5 : 2.5);
	if (tab->key.rotR)
		tab->angle += (tab->key.fovgod == 1 ? 5 : 2.5);
	(tab->angle < 0 ? tab->angle += 360 : 0);
	(tab->angle > 360 ? tab->angle -= 360 : 0);
	if (tab->key.front || tab->key.back)
		back_front(tab);
	if (tab->key.moveL || tab->key.moveR)
		left_right(tab);
}

void	back_front(t_map *tab)
{
	if (tab->key.front)
	{
		if (tab->map[(int)(tab->pos_x + cos(tab->angle * (M_PI / 180))
		* tab->key.speed)][(int)tab->pos_y] == '0')
			tab->pos_x += cos(tab->angle * (M_PI / 180)) * tab->key.speed;
		if (tab->map[(int)tab->pos_x][(int)(tab->pos_y + sin(tab->angle
		* (M_PI / 180)) * tab->key.speed)] == '0')
			tab->pos_y += sin(tab->angle * (M_PI / 180)) * tab->key.speed;
	}
	if (tab->key.back)
	{
		if (tab->map[(int)(tab->pos_x - cos(tab->angle * (M_PI / 180))
		* tab->key.speed)][(int)tab->pos_y] == '0')
			tab->pos_x -= cos(tab->angle * (M_PI / 180)) * tab->key.speed;
		if (tab->map[(int)tab->pos_x][(int)(tab->pos_y - sin(tab->angle
		* (M_PI / 180)) * tab->key.speed)] == '0')
			tab->pos_y -= sin(tab->angle * (M_PI / 180)) * tab->key.speed;
	}
}

void	left_right(t_map *tab)
{
	if (tab->key.moveL)
	{
		tab->len.planx = cos((tab->angle + 90) * M_PI / 180) * 0.66;
		tab->len.plany = sin((tab->angle + 90) * M_PI / 180) * 0.66;
		if (tab->map[(int)(tab->pos_x - tab->len.planx
		* tab->key.speed)][(int)tab->pos_y] == '0')
			tab->pos_x -= tab->len.planx * tab->key.speed;
		if (tab->map[(int)tab->pos_x][(int)(tab->pos_y - tab->len.plany
		* tab->key.speed)] == '0')
			tab->pos_y -= tab->len.plany * tab->key.speed;
	}
	if (tab->key.moveR)
	{
		tab->len.planx = cos((tab->angle + 90) * M_PI / 180) * 0.66;
		tab->len.plany = sin((tab->angle + 90) * M_PI / 180) * 0.66;
		if (tab->map[(int)(tab->pos_x + tab->len.planx
		* tab->key.speed)][(int)tab->pos_y] == '0')
			tab->pos_x += tab->len.planx * tab->key.speed;
		if (tab->map[(int)tab->pos_x][(int)(tab->pos_y + tab->len.plany
		* tab->key.speed)] == '0')
			tab->pos_y += tab->len.plany * tab->key.speed;
	}
}

int		key_press(int keycode, t_map *tab)
{
	tab->key.rotL = (keycode == 123 ? 1 : tab->key.rotL);
	tab->key.rotR = (keycode == 124 ? 1 : tab->key.rotR);
	tab->key.front = (keycode == 13 ? 1 : tab->key.front);
	tab->key.back = (keycode == 1 ? 1 : tab->key.back);
	tab->key.moveL = (keycode == 0 ? 1 : tab->key.moveL);
	tab->key.moveR = (keycode == 2 ? 1 : tab->key.moveR);
	tab->key.sprint = (keycode == 257 ? 1 : tab->key.sprint);
	tab->key.respawn = (keycode == 15 ? 1 : tab->key.respawn);
	tab->key.fovgod = (keycode == 3 ? 1 : tab->key.fovgod);
	if (keycode == 53)
	{
		mlx_destroy_window(tab->mlx.mlx_ptr, tab->mlx.win);
		exit(0);
	}
	return (0);
}

int		key_release(int keycode, t_map *tab)
{
	(keycode == 123 ? tab->key.rotL-- : 0);
	(keycode == 124 ? tab->key.rotR-- : 0);
	(keycode == 13 ? tab->key.front-- : 0);
	(keycode == 1 ? tab->key.back-- : 0);
	(keycode == 0 ? tab->key.moveL-- : 0);
	(keycode == 2 ? tab->key.moveR-- : 0);
	(keycode == 257 ? tab->key.sprint-- : 0);
	(keycode == 15 ? tab->key.respawn-- : 0);
	(keycode == 3 ? tab->key.fovgod-- : 0);
	return (0);
}
