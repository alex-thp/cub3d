//* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:54:42 by ade-temm          #+#    #+#             */
/*   Updated: 2019/12/16 10:52:58 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		loop_game(t_map *tab)
{
	tab->len.x = -1;
	handle_move(tab);
	if (is_loopable(tab))
	{
		while (++tab->len.x <= tab->res_x)
		{
			calc_dist(tab);
			display_ray(tab);

	// 		if (tab->len.x == tab->res_x /2)
	// 		{
	// 			// printf("\ntab->len.wallX = %f\n",tab->len.wallX);
	// 			// printf("\nresYY = %d\n",tab->res_y);				
	// 			// printf("\nH = %d et W = %d\n", tab->dst_N.height, tab->dst_N.width);
	// 			// printf("\nH %d W %d\n", tab->dst_S.height, tab->dst_S.width);
	// 			// printf("\nresX %d et resY %d\n", tab->res_x, tab->res_y);
	// 		}
		}
		mlx_put_image_to_window(tab->mlx.mlx_ptr, tab->mlx.win, tab->mlx.img, 0, 0);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_map	*tab;
	
	(void)ac;
	// int i;
	if (!(tab = (t_map*)malloc(sizeof(t_map))))
		return (-1);
	parse_map(av, tab);
	ft_exit_error(tab);
	// printf("\nF  =|%d|\n", tab->doc.F.hex);
	// printf("\nC  =|%d|\n", tab->doc.C.hex);
	// printf("\nres_x = |%d|\n", tab->res_x);
	// printf("\nres_y = |%d|\n", tab->res_y);
	// printf("\ntexture Nord = |%s|\n", tab->doc.NO);
	// printf("\ntexture  Sud = |%s|\n", tab->doc.SO);
	// printf("\ntexture West = |%s|\n", tab->doc.WE);
	// printf("\ntexture  Est = |%s|\n", tab->doc.EA);
	// printf("\ntextu Sprite = |%s|\n", tab->doc.S);
	// printf("\ntextur Floor = |%d|\n", tab->doc.F.red);
	// printf("\ntextur Floor = |%d|\n", tab->doc.F.green);
	// printf("\ntextur Floor = |%d|\n", tab->doc.F.blue);
	// printf("\ntextur Floor = |%d|\n", tab->doc.F.trans);
	// printf("\ntext Cealing = |%d|\n", tab->doc.C.red);
	// printf("\ntext Cealing = |%d|\n", tab->doc.C.green);
	// printf("\ntext Cealing = |%d|\n", tab->doc.C.blue);
	// printf("\ntext Cealing = |%d|\n", tab->doc.C.trans);
	// printf("\nerror        = |%d|\n", tab->error);
	// i = 0;

	// while (tab->map[i])
	// {
		// printf("\n|%s|\n", tab->map[i]);
		// i++;
	// }
	ft_init_mlx(tab);
	mlx_hook (tab->mlx.win, 2, 0, key_press, tab);
	mlx_hook (tab->mlx.win, 3, 0, key_release, tab);
	mlx_loop_hook (tab->mlx.mlx_ptr, loop_game, tab);
	mlx_loop(tab->mlx.mlx_ptr);
	return (0);
}
