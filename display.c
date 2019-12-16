/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 04:26:19 by thverney          #+#    #+#             */
/*   Updated: 2019/12/17 00:50:26 by thverney         ###   ########.fr       */
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
	get_texture(tab);
}

void	display_ray(t_map *tab)
{
	int i;
	int y; // ajouter des bordures noirs
	i = -1;



	while (++i <= (int)tab->len.ray_start)
		tab->mlx.pix[i * tab->res_x + tab->len.x] = tab->doc.C.hex;
	y = --i + 1; // ajouter des bordures noirs
	while(++i <= (int)tab->len.ray_end)
	{
		tab->len.textY = (((double)i * 2. - (double)tab->res_y + (double)tab->len.heightline) * (tab->dst_N.width/ 2) / (double)tab->len.heightline);
		if (tab->len.side == 1 && tab->map_y < tab->pos_y)
		{
			tab->mlx.pix[i * tab->res_x + tab->len.x] = tab->dst_N.pix[(int)tab->len.textY * tab->dst_N.width + tab->len.textXN]; //0xff000000;
		}
		else if (tab->len.side == 1)
		{
			tab->len.textY = (((double)i * 2. - (double)tab->res_y + (double)tab->len.heightline) * (tab->dst_S.width/ 2) / (double)tab->len.heightline);
			tab->mlx.pix[i * tab->res_x + tab->len.x] = tab->dst_S.pix[(int)tab->len.textY * tab->dst_S.width + tab->len.textXS]; //0xff000000;
		}
		if (tab->len.side == 0 && tab->map_x < tab->pos_x)
		{
			tab->len.textY = (((double)i * 2. - (double)tab->res_y + (double)tab->len.heightline) * (tab->dst_W.width/ 2) / (double)tab->len.heightline);
			tab->mlx.pix[i * tab->res_x + tab->len.x] = tab->dst_W.pix[(int)tab->len.textY * tab->dst_W.width + tab->len.textXW]; //0xff000000;
		}
		else if (tab->len.side == 0)
		{
			tab->len.textY = (((double)i * 2. - (double)tab->res_y + (double)tab->len.heightline) * (tab->dst_E.width/ 2) / (double)tab->len.heightline);
			tab->mlx.pix[i * tab->res_x + tab->len.x] = tab->dst_E.pix[(int)tab->len.textY * tab->dst_E.width + tab->len.textXE]; //0xff000000;
		}
		(i == y ? tab->mlx.pix[i * tab->res_x + tab->len.x] = 0x000000 : 0); // ajouter des bordures noirs
		(i == tab->len.ray_end ? tab->mlx.pix[i * tab->res_x + tab->len.x] = 0x000000 : 0); // ajouter des bordures noirs
	}
	i--;
	while (++i < tab->res_y)
	{
		tab->mlx.pix[i * tab->res_x + tab->len.x] = tab->doc.F.hex;
	}
}
