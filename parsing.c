/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 04:13:10 by thverney          #+#    #+#             */
/*   Updated: 2019/12/12 04:30:00 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_map(char **av, t_map	*tab)
{
	int		fd;
	int		i;
	char	*tb;

	i = 1;
	fd = open(av[1], O_RDONLY);
	get_next_line(fd, &tab->doc.R);
	get_next_line(fd, &tab->doc.NO);
	get_next_line(fd, &tab->doc.SO);
	get_next_line(fd, &tab->doc.WE);
	get_next_line(fd, &tab->doc.EA);
	get_next_line(fd, &tab->doc.S);
	get_next_line(fd, &tab->doc.F);
	get_next_line(fd, &tab->doc.C);
	tab->doc.map = malloc(1);
	tab->doc.map[0] = 0;
	while (i)
	{
		i = get_next_line(fd, &tb);
		tab->doc.map = ft_strjoin_gnl(tab->doc.map, tb, 2147483647);
		tab->doc.map = ft_strjoin_gnl(tab->doc.map, ".", 2147483647);
	}
}

char	*clean_str(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = ft_strlen(str);
	if (!(res = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != 32)
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	res[j] = 0;
	free(str);
	return (res);
}

void	ft_perfect_parse(t_map *tab)
{
	int i;

	i = 0; 
	while (!(isnb(tab->doc.R[i])))
		i++;
	tab->res_x = ft_atoi(tab->doc.R + i);
	while (isnb(tab->doc.R[i]))
		i++;
	while (!(isnb(tab->doc.R[i])))
		i++;
	tab->res_y = ft_atoi(tab->doc.R + i);
	tab->doc.NO = sdupfr(ft_strchr(tab->doc.NO, '.'), 0);
	tab->doc.SO = sdupfr(ft_strchr(tab->doc.SO, '.'), 0);
	tab->doc.WE = sdupfr(ft_strchr(tab->doc.WE, '.'), 0);
	tab->doc.EA = sdupfr(ft_strchr(tab->doc.EA, '.'), 0);
	tab->doc.S = sdupfr(ft_strchr(tab->doc.S, '.'), 0);
	i = 0;
	while (!(isnb(tab->doc.F[i])))
		i++;
	tab->doc.F = tab->doc.F + i;
	i = 0;
	while (!(isnb(tab->doc.C[i])))
		i++;
	tab->doc.C = tab->doc.C + i;
}

void	clean_map(t_map *tab)
{
	int		i;

	i = 0;
	while (tab->map[i])
	{
		tab->map[i] = clean_str(tab->map[i]);
		i++;
	}
	ft_perfect_parse(tab);
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
