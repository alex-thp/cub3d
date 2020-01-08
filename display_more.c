/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_more.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 01:11:58 by thverney          #+#    #+#             */
/*   Updated: 2020/01/08 19:54:20 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_ray_gun(t_map *tab)
{
	int j;

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

t_sprite	*sort_sprites(t_sprite *copy)
{
	t_sprite *tmp;
	t_sprite *pre;

	pre = NULL;
	tmp = copy;
	while (tmp->next != NULL)
	{
		if (tmp->dist > tmp->next->dist)
		{
			pre ? pre->next = tmp->next : 0;
			!pre ? copy = tmp->next : 0;
			tmp->next = tmp->next->next;
			pre->next->next = tmp;
		}
		else
		{
			pre = tmp;
			tmp = tmp->next;
		}
	}
	return (copy);

}

void	display_sprites(t_map *tab)
{
	int i;
	t_sprite *tmp;

	tmp = tab->sp;
	i = -1;
	while (++i < tab->len.nbSP)
	{
		tmp->dist = ((tab->pos_x - tmp->x) *
		(tab->pos_x - tmp->x) + (tab->pos_y - tmp->y) *
		(tab->pos_y - tmp->y));
		tmp = tmp->next;
	}
	tab->sp = sort_sprites(tmp);
	print_sprite(tab);
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