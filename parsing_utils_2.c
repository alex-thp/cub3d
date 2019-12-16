/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:15:47 by thverney          #+#    #+#             */
/*   Updated: 2019/12/16 22:12:58 by thverney         ###   ########.fr       */
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

int 	splitmap(char *str, int i, int len)
{
	int j;

	j = 0;
	if (i == 0 || i == -1)
	{
		while (str[j] != '\0')
		{
			if (str[j] == '0')
				return (1);
			j++;
		}
	}
	if (str[0] == '0')
		return (1);
	if (str[len] == '0')
		return (1);
	return (0);
}

void	ft_map_check(t_map *tab, int indic)
{
	int i;
	int len;
	int comp;

	if (indic == -1)
	{
		splitmap(tab->doc.temp, -1, 0) == 1 ? ft_error(3, tab) : 0;
		if (splitmap(tab->doc.temp, -1, 0) == 1)
			return ;
	}
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
		// printf("\nBAH ALORS\n");
		if (splitmap(tab->map[i], i, len) == 1)
		{
			printf("\nBAH ALORS\n");
			ft_error(3, tab);
			break ;
		}
		i++;
	}
}
