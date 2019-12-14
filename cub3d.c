/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:54:42 by ade-temm          #+#    #+#             */
/*   Updated: 2019/12/14 09:01:29 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		loop_game(t_map *tab)
{
	tab->len.x = -1;
	handle_angle(tab);
	handle_mouv(tab);
	if (tab->premierAffichage-- == 1 || tab->key.tournerG || tab->key.tournerD
	|| tab->key.avancer || tab->key.reculer || tab->key.gauche || tab->key.droite
	|| tab->key.respawn)
	{
		while (++tab->len.x <= tab->res_x)
		{
			calc_dist(tab);
			display_ray(tab);

			if (tab->len.x == tab->res_x /2)
			{
				// printf("\ntab->len.wallX = %f\n",tab->len.wallX);
				// printf("\nresYY = %d\n",tab->res_y);				
				printf("\nH = %d et W = %d\n", tab->dst_N.height, tab->dst_N.width);
				printf("\nresX %d et resY %d\n", tab->res_x, tab->res_y);
			}
		}
		mlx_put_image_to_window(tab->mlx.mlx_ptr, tab->mlx.win, tab->mlx.img, 0, 0);

	}
	return (0);
}

int		main(int ac, char **av)
{
	t_map	*tab;
	t_len	*dist;	
	
	(void)ac;
	if (!(tab = (t_map*)malloc(sizeof(t_map))))
		return (-1);
	if (!(dist = (t_len*)malloc(sizeof(t_len))))
		return (-1);
	parse_map(av, tab);
	tab->map = ft_split(tab->doc.map, '.');
	clean_map(tab);
	position(tab);
	ft_init_mlx(tab);
	mlx_hook (tab->mlx.win, 2, 0, key_press, tab);
	mlx_hook (tab->mlx.win, 3, 0, key_release, tab);
	mlx_loop_hook (tab->mlx.mlx_ptr, loop_game, tab);
	mlx_loop(tab->mlx.mlx_ptr);
	return (0);
}