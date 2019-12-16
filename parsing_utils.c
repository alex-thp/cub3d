/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 12:29:47 by thverney          #+#    #+#             */
/*   Updated: 2019/12/16 17:02:16 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	doc_resolution(char *str, t_map *tab)
{
	int i;

	i = 0;
	while (isnb(str[i]) == 0 && str[i] != '\0')
			i++;
	tab->res_x = ft_atoi(str + i);
	while (isnb(str[i]) == 1 && str[i] != '\0')
		i++;
	while (isnb(str[i]) == 0 && str[i] != '\0')
		i++;
	tab->res_y = ft_atoi(str + i);
	(tab->res_y == 0 || tab->res_x == 0 || str[i] == '\0' ?
	ft_error(1, tab) : 0);
}

void	doc_way(char *str, t_map *tab, int way)
{

	if (ft_strchr(str, '.') == NULL)
	{
		ft_error(4, tab);
		return ;
	}
	if (way == 0)
		tab->doc.NO = sdupfr(ft_strchr(str, '.'), 0);
	if (way == 1)
		tab->doc.SO = sdupfr(ft_strchr(str, '.'), 0);
	if (way == 2)
		tab->doc.WE = sdupfr(ft_strchr(str, '.'), 0);
	if (way == 3)
		tab->doc.EA = sdupfr(ft_strchr(str, '.'), 0);
	if (way == 4)
		tab->doc.S = sdupfr(ft_strchr(str, '.'), 0);
	doc_way_fd(tab, way);
	
}

void	doc_color_F(char *str, t_map *tab)
{
	int i;

	i = 0;
	while (isnb(str[i]) == 0 && str[i] != '\0')
		i++;
	tab->doc.F.red = ft_atoi(str + i);
	while (isnb(str[i]) == 1 && str[i] != '\0')
		i++;
	while (isnb(str[i]) == 0 && str[i] != '\0')
		i++;
	tab->doc.F.green = ft_atoi(str + i);
	while (isnb(str[i]) == 1 && str[i] != '\0')
		i++;
	while (isnb(str[i]) == 0 && str[i] != '\0')
		i++;
	tab->doc.F.blue = ft_atoi(str + i);
	(str[i] == '\0' || tab->doc.F.blue < 0 || tab->doc.F.blue > 255
	|| tab->doc.F.red < 0 || tab->doc.F.red > 255
	|| tab->doc.F.green < 0 || tab->doc.F.green > 255 ? ft_error(6, tab) : 0);
	tab->doc.F.trans = 0;
}

void	doc_color_C(char *str, t_map *tab)
{
	int i;

	i = 0;
	while (isnb(str[i]) == 0 && str[i] != '\0')
		i++;
	tab->doc.C.red = ft_atoi(str + i);
	while (isnb(str[i]) == 1 && str[i] != '\0')
		i++;
	while (isnb(str[i]) == 0 && str[i] != '\0')
		i++;
	tab->doc.C.green = ft_atoi(str + i);
	while (isnb(str[i]) == 1 && str[i] != '\0')
		i++;
	while (isnb(str[i]) == 0 && str[i] != '\0')
		i++;
	tab->doc.C.blue = ft_atoi(str + i);
	(str[i] == '\0' || tab->doc.C.blue < 0 || tab->doc.C.blue > 255
	|| tab->doc.C.red < 0 || tab->doc.C.red > 255
	|| tab->doc.C.green < 0 || tab->doc.C.green > 255 ? ft_error(6, tab) : 0);
	tab->doc.C.trans = 0;
}

void	ft_error(int error, t_map *tab)
{
	if (error == 1)
	{
		write(1, "\n(ERROR!) Invalid Resolution [Error 1]\n", 40);
		tab->error = 1;
	}
	if (error == 2)
	{
		write(1, "\n(ERROR!) Invalid Map, illegal character(s) [Error 2]\n", 55);
		tab->error = 1;
	}
	if (error == 3)
	{
		write(1, "\n(ERROR) Invalid Map, Map must be closed by '1' [Error 3]\n", 59);
		tab->error = 1;
	}

	if (error == 4)
	{
		write(1, "\n(ERROR) Invalid Path texture [Error 4]\n", 41);
		tab->error = 1;
	}	
	if (error == 5)
	{
		write(1, "\n(ERROR) Path(s) not found [Error 5]\n", 38);
		tab->error = 1;
	}
	if (error == 6)
	{
		write(1, "\n(ERROR) Illegal RGB value(s) [Error 6]\n", 41);
		tab->error = 1;
	}
	
}