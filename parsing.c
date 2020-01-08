/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 04:13:10 by thverney          #+#    #+#             */
/*   Updated: 2020/01/08 14:05:27 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_map(t_map *tab)
{
	int		k;
	int		i;
	int		j;
	char	*res;
	
	k = -1;
	while (tab->map[++k])
	{
		if (!(res = malloc(sizeof(char) * (ft_strlen(tab->map[k]) + 1))))
			return ;
		j = 0;
		i = -1;
		while (tab->map[k][++i])
		{
			if (tab->map[k][i] != 32)
			{
				res[j++] = tab->map[k][i];
				(res[j - 1] != '1' && res[j - 1] != '0' && res[j - 1] != '2' 
				? tab->tmp_err++ : 0);
				res[j - 1] == '2' ? ft_sprites_stock((double)k, (double)i, tab) : 0;
			}
		}
		res[j] = 0;
		free(tab->map[k]);
		tab->map[k] = res;
	}
	print_sprite(tab);	
}

void	doc_checker(char *str, t_map *tab)
{
	if (str[0] == 'R')
	{
		doc_resolution(str, tab);
	}
	if ((str[0] == 'N' || str[0] == 'S') && str[1] == 'O')
		(str[0] == 'N' ? doc_way(str, tab, 0) : doc_way(str, tab, 1));
	if (str[0] == 'W' && str[1] == 'E')
		doc_way(str, tab, 2);
	if (str[0] == 'E' && str[1] == 'A')
		doc_way(str, tab, 3);
	if (str[0] == 'S' && str[1] == ' ')
		doc_way(str, tab, 4);
	if (str[0] == 'F' && str[1] == ' ')
		doc_color_F(str, tab);
	if (str[0] == 'C' && str[1] == ' ')
		doc_color_C(str, tab);

	if (str[0] == '0')
		ft_error(3, tab);
	if (str[0] == '1' || (str[0] == ' ' && ft_strchr(str, '1') != NULL))
	{
		tab->doc.map = ft_strjoin_gnl(tab->doc.map, str, 2147483647);
		tab->doc.map = ft_strjoin_gnl(tab->doc.map, ".", 2147483647);
	}
}

void	parse_map(char **av, t_map	*tab)
{
	int		fd;
	int		i;

	tab->tmp_err = 0;
	tab->error = 0;
	i = 1;
	fd = open(av[1], O_RDONLY);
	(fd == -1 ? tab->error = 1 : 0);
	tab->doc.map = malloc(1);
	tab->doc.map[0] = 0;
	while (i)
	{
		i = get_next_line(fd, &tab->doc.temp);
		doc_checker(tab->doc.temp, tab);
		if (i == 0)
			splitmap(tab->doc.temp, -1, 0, tab);
	}
	doc_way(".", tab, 5);
	tab->map = ft_split(tab->doc.map, '.');
	tab->tmp_err = 0;
	clean_map(tab);
	(tab->tmp_err > 1 ? ft_error(2, tab) : 0);
	ft_map_check(tab);
	position(tab);
}

void	position(t_map *tab)
{
	int		x;
	int		y;

	x = 0;
	while (tab->map[x])
	{
		y = 0;
		while (tab->map[x][y])
		{
			if (isnb(tab->map[x][y]) == 0)
			{
				if (tab->map[x][y] == 'E')
					tab->angle = 90;
				if (tab->map[x][y] == 'N')
					tab->angle = 180;
				if (tab->map[x][y] == 'W')
					tab->angle = 270;
				if (tab->map[x][y] == 'S')
					tab->angle = 0;
				tab->pos_y = y + 0.5;
				tab->pos_x = x + 0.5;
				tab->map[x][y] = '0';
				tab->len.spawnX = tab->pos_x;
				tab->len.spawnY = tab->pos_y;
				tab->len.spawnAngle = tab->angle;
			}
			y++;
		}
		x++;
	}
}
