/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:54:42 by ade-temm          #+#    #+#             */
/*   Updated: 2019/12/06 20:07:31 by ade-temm         ###   ########.fr       */
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
					scene->angle = 0;
				if (scene->map[x][y] == 'N')
					scene->angle = 90;
				if (scene->map[x][y] == 'W')
					scene->angle = 180;
				if (scene->map[x][y] == 'S')
					scene->angle = 270;
				scene->pos_y = y;
				scene->pos_x = x;
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

t_len		calc_v(t_map *tab)
{
	t_len		dist;
	dist.hit = 0;

	dist.v_y = cos(tab->angle * M_PI / 180);
	dist.v_y = sin(tab->angle * M_PI / 180);
	printf("\ndistvx = |%f|\n", dist.v_x);
	printf("\ndistvy = |%f|\n", dist.v_y);
	// dist.deltaDistX = dist.v_x;
	// dist.deltaDistY = dist.v_y;
	dist.deltaDistX = sqrt(1 + (dist.v_y * dist.v_y) / (dist.v_x * dist.v_x));
	dist.deltaDistY = sqrt(1 + (dist.v_x * dist.v_x) / (dist.v_y * dist.v_y));
	printf("\ndeltax = |%f|\n", dist.deltaDistX);
	printf("\ndeltay = |%f|\n", dist.deltaDistY);
	dist.norme = sqrt((dist.v_x * dist.v_x) + (dist.v_y * dist.v_y));
	return (dist);
}

double		calc_dist(t_map *tab, t_len dist)
{
	tab->cam_x = tab->pos_x;
	tab->cam_y = tab->pos_y;
	// printf("\nangle = [%f]\n", tab->angle);
	if (tab->angle <= 90)
	{
		dist.stepX = -1;
		dist.sideDistX = (tab->cam_x - (int)tab->cam_x) * dist.deltaDistX; 
		printf("\nsideDistX1 = |%f|\n", dist.sideDistX);
		// printf("\nentier1 x=|%f| y=|%f|\n", tab->cam_x, tab->cam_y);
	}
	else
	{
		// printf("\nentier2 x=|%f| y=|%f|\n", tab->cam_x, tab->cam_y);
		dist.stepX = 1;
		dist.sideDistX = ((int)tab->cam_x + 1.0 - tab->cam_x) * dist.deltaDistX;
		printf("\nsideDistX2 = |%f|\n", dist.sideDistX);
	}
	if (tab->angle > 90 && tab->angle < 270)
	{
		// printf("\nentier3 x=|%f| y=|%f|\n", tab->cam_x, tab->cam_y);
		dist.stepY = -1;
		dist.sideDistY = (tab->cam_y - (int)tab->cam_y) * dist.deltaDistY; 
		printf("\nsideDistY1 = |%f|\n", dist.sideDistY);
	}
	else
	{
		// printf("\nentier4 x=|%f| y=|%f|\n", tab->cam_x, tab->cam_y);
		dist.stepY = 1;
		dist.sideDistY = ((int)tab->cam_y + 1.0 - tab->cam_y) * dist.deltaDistY;
		printf("\nsideDistY1 = |%f|\n", dist.sideDistY);
	}
	while (dist.hit == 0) 
	{
		if (dist.sideDistX < dist.sideDistY) 
		{
			// printf("\nentrer if x=|%f| y=|%f|\n", tab->cam_x, tab->cam_y);
			dist.sideDistX += dist.deltaDistX;
			tab->cam_x += dist.stepX;
			dist.side = 0;
			// printf("\nsortie if x=|%f| y=|%f|\n", tab->cam_x, tab->cam_y);
		}
		else
		{
			// printf("\nentrer else x=|%f| y=|%f|\n", tab->cam_x, tab->cam_y);
			dist.sideDistY += dist.deltaDistY;
			tab->cam_y += dist.stepY;
			dist.side = 1;
			// printf("\nsortie else x=|%f| y=|%f|\n", tab->cam_x, tab->cam_y);
		}
		// printf("\ncam_x = |%f| cam_y = |%f|\n", tab->cam_x, tab->cam_y);
		if (tab->map[(int)tab->cam_x][(int)tab->cam_y] > '0')
			dist.hit = 1;
	}
	// printf();
	return (dist.sideDistX <= dist.sideDistY ? dist.sideDistX : dist.sideDistY);

}

int		main(int ac, char **av)
{
	t_doc	doc;
	t_map	*scene;
	t_len	dist;
	double		i;
	
	if (!(scene = (t_map*)malloc(sizeof(t_map))))
		return (-1);
	doc = parse_map(av);
	scene->map = ft_split(doc.map, '.');
	clean_map(scene);
	position(scene); //Recupere la position de départ et remplace la lettrepar un 0. Initialise l'angle de départ.
	print_map(scene);  
	dist = calc_v(scene);
	i = calc_dist(scene, dist);
	if (i >= 0)
		printf("\ndistance == |%f|\n", i);
	else
		printf("\ndistance == |%f|\n", i * -1);

}	
