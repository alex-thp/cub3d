/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:15:47 by thverney          #+#    #+#             */
/*   Updated: 2019/12/16 23:40:38 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	doc_way_fd(t_map *tab, int way)
{
	int fd;
	
	fd = 0;
	if (way == 0)
		(((fd = open(tab->doc.NO, O_RDONLY)) == -1) ? ft_error(4, tab) : 0);
	if (way == 1)
		(((fd = open(tab->doc.SO, O_RDONLY)) == -1) ? ft_error(4, tab) : 0);
	if (way == 2)
		(((fd = open(tab->doc.WE, O_RDONLY)) == -1) ? ft_error(4, tab) : 0);
	if (way == 3)
		(((fd = open(tab->doc.EA, O_RDONLY)) == -1) ? ft_error(4, tab) : 0);
	if (way == 4)
		(((fd = open(tab->doc.S, O_RDONLY)) == -1) ? ft_error(4, tab) : 0);
	if (way == 5)
		if (!(tab->doc.NO) || !(tab->doc.SO) || !(tab->doc.WE)
		|| !(tab->doc.EA) || !(tab->doc.S))
			ft_error(5, tab);
}

int 	splitmap(char *str, int i, int len, t_map *tab)
{
	int j;

	j = 0;
	if (i == 0 || i == -1)
	{
		while (str[j] != '\0')
		{
			if (str[j] == '0' && i == -1)
				ft_error(3, tab);
			if (str[j] == '0')
				return (1);
			j++;
		}
	}
	if (str[0] == '0' && i != -1)
		return (1);
	if (str[len] == '0' && i != -1)
		return (1);
	return (0);
}

void	ft_map_check(t_map *tab)
{
	int i;
	int len;
	int comp;

	i = 0;
	len = ft_strlen(tab->map[i]) - 1;
	while (tab->map[i])
	{
		comp =  ft_strlen(tab->map[i]) - 1;
		if (comp != len)
		{
			ft_error(7, tab);
			break ;
		}
		if (splitmap(tab->map[i], i, len, tab) == 1)
		{
			ft_error(3, tab);
			break ;
		}
		i++;
	}
}

void	ft_exit_error(t_map *tab)
{
	if (tab->error == 1)
		exit(0);
}

void	ft_put_in_hex(t_map *tab, int i)
{
	if (i == 0)
	{
		tab->doc.F.hex = tab->doc.F.blue | tab->doc.F.red << 16 | tab->doc.F.green << 8;
	}
	if (i == 1)
	{
		tab->doc.C.hex = tab->doc.C.blue | tab->doc.C.red << 16 | tab->doc.C.green << 8;

	}
}