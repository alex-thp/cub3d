/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 04:26:19 by thverney          #+#    #+#             */
/*   Updated: 2019/12/12 04:28:26 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_mlx(t_map *tab)
{
	int		lol;

	tab->premierAffichage = 1;
	tab->mlx.mlx_ptr = mlx_init();
	tab->mlx.win = mlx_new_window(tab->mlx.mlx_ptr, tab->res_x, tab->res_y, "cub3d");
	tab->mlx.img = mlx_new_image(tab->mlx.mlx_ptr, tab->res_x, tab->res_x);
	tab->mlx.pix = (int *)mlx_get_data_addr(tab->mlx.img, &lol, &lol, &lol);

}

void	display_ray(t_map *tab)
{
	int i;
	int y; // ajouter des bordures noirs
	i = -1;

	while (++i <= (int)tab->len.ray_start)
		tab->mlx.pix[i * tab->res_x + tab->len.x] = 0x96ceb4;
	y = --i + 1; // ajouter des bordures noirs
	while(++i <= (int)tab->len.ray_end)
	{
		if (tab->len.side == 1 && tab->map_y < tab->pos_y)
			tab->mlx.pix[i * tab->res_x + tab->len.x] = 0xff0000;
		else if (tab->len.side == 1)
			tab->mlx.pix[i * tab->res_x + tab->len.x] = 0xbb9b49;
		if (tab->len.side == 0 && tab->map_x < tab->pos_x)
			tab->mlx.pix[i * tab->res_x + tab->len.x] = 0x400000;
		else if (tab->len.side == 0)
			tab->mlx.pix[i * tab->res_x + tab->len.x] = 0xffcc5c;
		(i == y ? tab->mlx.pix[i * tab->res_x + tab->len.x] = 0x000000 : 0); // ajouter des bordures noirs
		(i == tab->len.ray_end ? tab->mlx.pix[i * tab->res_x + tab->len.x] = 0x000000 : 0); // ajouter des bordures noirs
	}
	i--;
	while (++i < tab->res_y)
	{
		tab->mlx.pix[i * tab->res_x + tab->len.x] = 0xffeead;
	}
}
