/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_more.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 01:11:58 by thverney          #+#    #+#             */
/*   Updated: 2020/01/08 14:34:51 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_ray_gun(t_map *tab)
{
	int j;

	display_sprites(tab);
	j = tab->res_y / 2 - 25;
	if (tab->len.x >= (tab->res_x / 2) - 1 && tab->len.x <= (tab->res_x / 2) + 1)
	{
		while (j <= tab->res_y / 2 + 25)  
		{
			tab->mlx.pix[j * tab->res_x + tab->len.x] = 0xff0000;
			j++;
		}
	}
	j = tab->res_y / 2 - 1;
	if (tab->len.x >= (tab->res_x / 2) - 25 && tab->len.x <= (tab->res_x / 2) + 25)
	{
		while (j <= tab->res_y / 2 + 1)  
		{
			tab->mlx.pix[j * tab->res_x + tab->len.x] = 0xff0000;
			j++;
		}
	}
}

void	display_sprites(t_map *tab)
{
	int i;
	
	i = -1;
	if (tab->map[tab->map_x][tab->map_y] == '2')
	{
		tab->len.textXSP = (int)(tab->len.wallX * tab->dst_SP.width);
		while (++i <= (int)tab->len.ray_start)
		{
			tab->mlx.pix[i * tab->res_x + tab->len.x] = tab->doc.C.hex;
		}
		while(++i <= (int)tab->len.ray_end)
		{
			tab->len.textY = (((double)i * 2. - (double)tab->res_y + (double)tab->len.heightline) * (tab->dst_SP.width/ 2) / (double)tab->len.heightline);
			// if (tab->len.side == 1 && tab->map_y < tab->pos_y)
			tab->mlx.pix[i * tab->res_x + tab->len.x] = tab->dst_SP.pix[(int)tab->len.textY * tab->dst_SP.width + tab->len.textXSP];
			// else if (tab->len.side == 1)
			// {
			// 	tab->len.textY = (((double)i * 2. - (double)tab->res_y + (double)tab->len.heightline) * (tab->dst_SP.width/ 2) / (double)tab->len.heightline);
			// 	tab->mlx.pix[i * tab->res_x + tab->len.x] = tab->dst_SP.pix[(int)tab->len.textY * tab->dst_SP.width + tab->len.textXSP]; //0xff000000;
			// }
			// if (tab->len.side == 0 && tab->map_x < tab->pos_x)
			// {
			// 	tab->len.textY = (((double)i * 2. - (double)tab->res_y + (double)tab->len.heightline) * (tab->dst_SP.width/ 2) / (double)tab->len.heightline);
			// 	tab->mlx.pix[i * tab->res_x + tab->len.x] = tab->dst_SP.pix[(int)tab->len.textY * tab->dst_SP.width + tab->len.textXSP]; //0xff000000;
			// }
			// else if (tab->len.side == 0)
			// {
			// 	tab->len.textY = (((double)i * 2. - (double)tab->res_y + (double)tab->len.heightline) * (tab->dst_SP.width/ 2) / (double)tab->len.heightline);
			// 	tab->mlx.pix[i * tab->res_x + tab->len.x] = tab->dst_SP.pix[(int)tab->len.textY * tab->dst_SP.width + tab->len.textXSP]; //0xff000000;
			// }
		}
		i--;
		while (++i < tab->res_y)
		{
			tab->mlx.pix[i * tab->res_x + tab->len.x] = tab->doc.F.hex;
		}
	}
	else
		return ;
}

void	print_sprite(t_map *tab)
{
	t_sprite *tmp;
	
	tmp = tab->sp;
	while (tmp)
	{
		printf("x = %f", tmp->x);
		printf("y = %f\n", tmp->y);
		tmp = tmp->next;
	}
}

void	ft_sprites_stock(double x, double y, t_map *tab)
{
	t_sprite	*new;
	t_sprite	*tmp;

	new = NULL;
	tmp = NULL;
	if (tab->sp == NULL)
	{
		printf("\nBITe1\n");
		if (!(tab->sp = (t_sprite*)malloc(sizeof(t_sprite))))
			return ;
		tab->sp->x = x;
		tab->sp->y = y;
		
		tab->sp->next = NULL;

		printf("\nBITe2\n");
	}
	else
	{
		printf("\nBITe3\n");
		if (!(new = (t_sprite*)malloc(sizeof(t_sprite))))
			return ;
		tmp = tab->sp;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;

		new->x = x;
		new->y = y;
		new->next = NULL;
		printf("\nBITe4\n");
	}
}
