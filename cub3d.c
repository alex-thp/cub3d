/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:54:42 by ade-temm          #+#    #+#             */
/*   Updated: 2019/12/09 13:01:39 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

t_doc	parse_map(char **av)
{
	int		fd;
	int		i;
	char	*tab;
	t_doc	res;

	i = 1;
	fd = open(av[1], O_RDONLY);
	get_next_line(fd, &res.R);
	get_next_line(fd, &res.NO);
	get_next_line(fd, &res.SO);
	get_next_line(fd, &res.WE);
	get_next_line(fd, &res.EA);
	get_next_line(fd, &res.S);
	get_next_line(fd, &res.F);
	get_next_line(fd, &res.C);
	res.map = malloc(1);
	res.map[0] = 0;
	while (i)
	{
		i = get_next_line(fd, &tab);
		res.map = ft_strjoin_gnl(res.map, tab, 2147483647);
		res.map = ft_strjoin_gnl(res.map, ".", 2147483647);
	}
	return (res);
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

void	clean_map(t_map *scene)
{
	int		i;

	i = 0;
	while (scene->map[i])
	{
		scene->map[i] = clean_str(scene->map[i]);
		i++;
	}
}

void	position(t_map *scene)
{
	int		x;
	int		y;

	x = 0;
	while (scene->map[x])
	{
		y = 0;
		while (scene->map[x][y])
		{
			if (ft_is_digit(scene->map[x][y]) == 0)
			{
				if (scene->map[x][y] == 'E')
					scene->angle = 90;
				if (scene->map[x][y] == 'N')
					scene->angle = 180;
				if (scene->map[x][y] == 'W')
					scene->angle = 270;
				if (scene->map[x][y] == 'S')
					scene->angle = 0;
				scene->pos_y = y + 0.5;
				scene->pos_x = x + 0.5;
				printf("\nMON TYPE = [%c]\n", scene->map[x][y]);
				scene->map[x][y] = '0';
			}
			y++;
		}
		x++;
	}
}

void	print_map(t_map *map)
{
	int		i;

	i = 0;
	while(map->map[i])
	{
		ft_putstr_fd(map->map[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void		calc_dist_xy(t_map *tab, t_len *dist)
{
	if (dist->rayDirX < 0)
	{
		dist->stepX = -1;
		dist->sideDistX = (tab->pos_x - tab->map_x) * dist->deltaDistX; 
	}
	else
	{
		dist->stepX = 1;
		dist->sideDistX = (tab->map_x + 1.0 - tab->pos_x) * dist->deltaDistX;
	}
	if (dist->rayDirY < 0)
	{
		dist->stepY = -1;
		dist->sideDistY = (tab->pos_y - tab->map_y) * dist->deltaDistY; 
	}
	else
	{
		dist->stepY = 1;
		dist->sideDistY = (tab->map_y + 1.0 - tab->pos_y) * dist->deltaDistY;
	}
}

void		calc_dist(t_map *tab, t_len *dist)
{
	ft_init_ray(tab, dist);
	calc_dist_xy(tab, dist);
	while (dist->hit == 0) 
	{
		if (dist->sideDistX < dist->sideDistY) 
		{
			dist->sideDistX += dist->deltaDistX;
			tab->map_x += dist->stepX;
			dist->side = 0;
		}
		else
		{
			dist->sideDistY += dist->deltaDistY;
			tab->map_y += dist->stepY;
			dist->side = 1;
		}
		if (tab->map[tab->map_x][tab->map_y] > '0')
			dist->hit = 1;
	}
	if (dist->side == 0)
		dist->perpWallDist = ((tab->map_x-tab->pos_x+(1-dist->stepX)/2)/ dist->rayDirX);
	else
		dist->perpWallDist = ((tab->map_y-tab->pos_y+(1-dist->stepY)/2)/ dist->rayDirY);
}

void		ft_init_ray(t_map *tab, t_len *dist)
{
	dist->hit = 0;
	dist->cameraX = (2 * dist->x / dist->w) - 1;
	dist->planx = cos((tab->angle + 90) * M_PI / 180) * 0.66;
	dist->plany = sin((tab->angle + 90) * M_PI / 180) * 0.66;
	dist->rayDirX = cos(tab->angle * M_PI / 180) + dist->planx * dist->cameraX;
	dist->rayDirY = sin(tab->angle * M_PI / 180) + dist->plany * dist->cameraX; 
	dist->deltaDistX = sqrt(1 + (dist->rayDirY * dist->rayDirY) / (dist->rayDirX * dist->rayDirX));
	dist->deltaDistY = sqrt(1 + (dist->rayDirX * dist->rayDirX) / (dist->rayDirY * dist->rayDirY));
	tab->map_x = (int)tab->pos_x;
	tab->map_y = (int)tab->pos_y;
	
}

int		main(int ac, char **av)
{
	t_doc	doc;
	t_map	*tab;
	t_len	*dist;
	double		i;
	
	if (!(tab = (t_map*)malloc(sizeof(t_map))))
		return (-1);
	if (!(dist = (t_len*)malloc(sizeof(t_len))))
		return (-1);
	doc = parse_map(av);
	tab->map = ft_split(doc.map, '.');
	clean_map(tab);
	position(tab); //Recupere la position de départ et remplace la lettrepar un 0. Initialise l'angle de départ.
	print_map(tab); 
	dist->x = 0;
	dist->w = 200;
	dist->h = 200;
	while (dist->x <= dist->w)
	{
		calc_dist(tab, dist);
		printf("\ndistance == |%f|\n", dist->perpWallDist);
		dist->x++;
	}

}	