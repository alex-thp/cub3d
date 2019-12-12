/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 04:27:49 by thverney          #+#    #+#             */
/*   Updated: 2019/12/12 04:29:38 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_angle(t_map *tab)
{
	if (tab->key.respawn)
	{
		tab->pos_x = tab->len.spawnX;
		tab->pos_y = tab->len.spawnY;
		tab->angle = tab->len.spawnAngle;
	}
	if (tab->key.tournerG)
		tab->angle -= 2.5;
	if (tab->key.tournerD)
		tab->angle += 2.5;
}

void	handle_mouv(t_map *tab)
{
	tab->key.vitMarche = (tab->key.sprint == 1 ? 0.3: 0.15);
	if (tab->key.avancer)
	{
		if (tab->map[(int)(tab->pos_x + cos(tab->angle * (M_PI / 180)) * tab->key.vitMarche)][(int)tab->pos_y] == '0')
			tab->pos_x += cos(tab->angle * (M_PI / 180)) * tab->key.vitMarche;
		if (tab->map[(int)tab->pos_x][(int)(tab->pos_y + sin(tab->angle * (M_PI / 180)) * tab->key.vitMarche)] == '0')
			tab->pos_y += sin(tab->angle * (M_PI / 180)) * tab->key.vitMarche;
	}
	if (tab->key.reculer)
	{
		if (tab->map[(int)(tab->pos_x - cos(tab->angle * (M_PI / 180)) * tab->key.vitMarche)][(int)tab->pos_y] == '0')
			tab->pos_x -= cos(tab->angle * (M_PI / 180)) * tab->key.vitMarche;
		if (tab->map[(int)tab->pos_x][(int)(tab->pos_y - sin(tab->angle * (M_PI / 180)) * tab->key.vitMarche)] == '0')
			tab->pos_y -= sin(tab->angle * (M_PI / 180)) * tab->key.vitMarche;
	}
	if (tab->key.gauche)
	{
		tab->len.planx = cos((tab->angle + 90) * M_PI / 180) * 0.66;
		if (tab->map[(int)(tab->pos_x - tab->len.planx * tab->key.vitMarche)][(int)tab->pos_y] == '0')
			tab->pos_x -= tab->len.planx * tab->key.vitMarche;
		tab->len.plany = sin((tab->angle + 90) * M_PI / 180) * 0.66;
		if (tab->map[(int)tab->pos_x][(int)(tab->pos_y - tab->len.plany * tab->key.vitMarche)] == '0')
			tab->pos_y -= tab->len.plany * tab->key.vitMarche;
	}
	if (tab->key.droite)
	{
		tab->len.planx = cos((tab->angle + 90) * M_PI / 180) * 0.66;
		if (tab->map[(int)(tab->pos_x + tab->len.planx * tab->key.vitMarche)][(int)tab->pos_y] == '0')
			tab->pos_x += tab->len.planx * tab->key.vitMarche;
		tab->len.plany = sin((tab->angle + 90) * M_PI / 180) * 0.66;
		if (tab->map[(int)tab->pos_x][(int)(tab->pos_y + tab->len.plany * tab->key.vitMarche)] == '0')
			tab->pos_y += tab->len.plany * tab->key.vitMarche;
	}

}

int key_press(int keycode, t_map *tab)
{
	tab->key.tournerG = (keycode == 123 ? 1 : tab->key.tournerG);
	tab->key.tournerD = (keycode == 124 ? 1 : tab->key.tournerD);
	tab->key.avancer = (keycode == 13 ? 1 : tab->key.avancer);
	tab->key.reculer = (keycode == 1 ? 1 : tab->key.reculer);
	tab->key.gauche = (keycode == 0 ? 1 : tab->key.gauche);
	tab->key.droite = (keycode == 2 ? 1 : tab->key.droite);
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

int	key_release(int keycode, t_map *tab)
{

	(keycode == 123 ? tab->key.tournerG-- : 0);
	(keycode == 124 ? tab->key.tournerD-- : 0);
	(keycode == 13 ? tab->key.avancer-- : 0);
	(keycode == 1 ? tab->key.reculer-- : 0);
	(keycode == 0 ? tab->key.gauche-- : 0);
	(keycode == 2 ? tab->key.droite-- : 0);
	(keycode == 257 ? tab->key.sprint-- : 0);
	(keycode == 15 ? tab->key.respawn-- : 0);
	(keycode == 3 ? tab->key.fovgod-- : 0);
	
	return (0);
}
