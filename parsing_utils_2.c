/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:15:47 by thverney          #+#    #+#             */
/*   Updated: 2019/12/16 16:47:09 by thverney         ###   ########.fr       */
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