/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:54:42 by ade-temm          #+#    #+#             */
/*   Updated: 2019/12/12 04:06:59 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

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

	printf("\ntext_N = {%s}\n", tab->doc.NO);
	printf("\ntext_S = {%s}\n", tab->doc.SO);
	printf("\ntext_W = {%s}\n", tab->doc.WE);
	printf("\ntext_E = {%s}\n", tab->doc.EA);
	printf("\ndoc.S = {%s}\n", tab->doc.S);
	printf("\nresx = {%d}\n", tab->res_x);
	printf("\nresy = {%d}\n", tab->res_y);
	printf("\ndoc.C = {%s}\n", tab->doc.C);
	printf("\ndoc.F = {%s}\n", tab->doc.F);
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
			if (ft_is_digit(tab->map[x][y]) == 0)
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

void	wall_distance(t_map *tab)
{
	if (tab->len.side == 0)
		tab->len.perpWallDist = fabs((((double)tab->map_x - tab->pos_x + (1 - tab->len.stepX) / 2) / tab->len.rayDirX));
	else
		tab->len.perpWallDist = fabs((((double)tab->map_y - tab->pos_y + (1 - tab->len.stepY) / 2) / tab->len.rayDirY));
	tab->len.heightline = (tab->key.sprint ? abs((int)((double)tab->len.h / tab->len.perpWallDist)) * 1.35 :
	abs((int)((double)tab->len.h / tab->len.perpWallDist)) * 1.7);
	tab->len.ray_start = (int)(-(tab->len.heightline / 2) + tab->len.h / 2);
	tab->len.ray_end = (int)((tab->len.heightline / 2) + tab->len.h / 2);
	
	if (tab->len.ray_start < 0)
		tab->len.ray_start = 0;
	if (tab->len.ray_end >= tab->len.h)
		tab->len.ray_end = tab->len.h - 1;
}

void		calc_dist_xy(t_map *tab)
{
	if (tab->len.rayDirX < 0)
	{
		tab->len.stepX = -1;
		tab->len.sideDistX = (tab->pos_x - tab->map_x) * tab->len.deltaDistX; 
	}
	else
	{
		tab->len.stepX = 1;
		tab->len.sideDistX = (tab->map_x + 1.0 - tab->pos_x) * tab->len.deltaDistX;
	}
	if (tab->len.rayDirY < 0)
	{
		tab->len.stepY = -1;
		tab->len.sideDistY = (tab->pos_y - tab->map_y) * tab->len.deltaDistY; 
	}
	else
	{
		tab->len.stepY = 1;
		tab->len.sideDistY = (tab->map_y + 1.0 - tab->pos_y) * tab->len.deltaDistY;
	}
}

void		ft_init_ray(t_map *tab)
{
	(tab->angle < 0 ? tab->angle += 360 : 0);
	(tab->angle > 360 ? tab->angle -= 360 : 0);
	tab->len.w = tab->res_x;
	tab->len.h = tab->res_y;
	tab->len.cameraX = (2 * (double)tab->len.x / (double)tab->len.w) - 1;
	if (tab->key.sprint)
	{
		tab->len.rayDirX = cos((tab->angle + (40 * tab->len.cameraX)) * (M_PI / 180));
		tab->len.rayDirY = sin((tab->angle + (40 * tab->len.cameraX)) * (M_PI / 180));
	}
	else if (tab->key.fovgod)
	{
		tab->len.rayDirX = cos((tab->angle + (180 * tab->len.cameraX)) * (M_PI / 180));
		tab->len.rayDirY = sin((tab->angle + (180 * tab->len.cameraX)) * (M_PI / 180));
	}
	else
	{
		tab->len.rayDirX = cos((tab->angle + (30 * tab->len.cameraX)) * (M_PI / 180));
		tab->len.rayDirY = sin((tab->angle + (30 * tab->len.cameraX)) * (M_PI / 180));
	}
	tab->len.deltaDistX = sqrt(1 + (tab->len.rayDirY * tab->len.rayDirY) / (tab->len.rayDirX * tab->len.rayDirX));
	tab->len.deltaDistY = sqrt(1 + (tab->len.rayDirX * tab->len.rayDirX) / (tab->len.rayDirY * tab->len.rayDirY));
	tab->len.hit = 0;
	tab->map_x = (int)tab->pos_x;
	tab->map_y = (int)tab->pos_y;
}

void		calc_dist(t_map *tab)
{
	ft_init_ray(tab);
	calc_dist_xy(tab);
	while (tab->len.hit == 0) 
	{
		if (tab->len.sideDistX < tab->len.sideDistY) 
		{
			tab->len.sideDistX += tab->len.deltaDistX;
			tab->map_x += tab->len.stepX;
			tab->len.side = 0;
		}
		else
		{
			tab->len.sideDistY += tab->len.deltaDistY;
			tab->map_y += tab->len.stepY;
			tab->len.side = 1;
		}
		if (tab->map[tab->map_x][tab->map_y] > '0')
			tab->len.hit = 1;
	}
	wall_distance(tab);
}

void	ft_init_mlx(t_map *tab)
{
	int		lol;

	tab->premierAffichage = 1;
	tab->mlx.mlx_ptr = mlx_init();
	tab->mlx.win = mlx_new_window(tab->mlx.mlx_ptr, tab->res_x, tab->res_y, "cub3d");
	tab->mlx.img = mlx_new_image(tab->mlx.mlx_ptr, tab->res_x, tab->res_x);
	tab->mlx.pix = (int *)mlx_get_data_addr(tab->mlx.img, &lol, &lol, &lol);

}

void	display_ray(t_map *tab)
{
	int i;
	int y; // ajouter des bordures noirs
	i = -1;

	while (++i <= (int)tab->len.ray_start)
		tab->mlx.pix[i * tab->res_x + tab->len.x] = 0x96ceb4;
	y = --i + 1; // ajouter des bordures noirs
	while(++i <= (int)tab->len.ray_end)
	{
		if (tab->len.side == 1 && tab->map_y < tab->pos_y)
			tab->mlx.pix[i * tab->res_x + tab->len.x] = 0xff0000;
		else if (tab->len.side == 1)
			tab->mlx.pix[i * tab->res_x + tab->len.x] = 0xbb9b49;
		if (tab->len.side == 0 && tab->map_x < tab->pos_x)
			tab->mlx.pix[i * tab->res_x + tab->len.x] = 0x400000;
		else if (tab->len.side == 0)
			tab->mlx.pix[i * tab->res_x + tab->len.x] = 0xffcc5c;
		(i == y ? tab->mlx.pix[i * tab->res_x + tab->len.x] = 0x000000 : 0); // ajouter des bordures noirs
		(i == tab->len.ray_end ? tab->mlx.pix[i * tab->res_x + tab->len.x] = 0x000000 : 0); // ajouter des bordures noirs
	}
	i--;
	while (++i < tab->res_y)
	{
		tab->mlx.pix[i * tab->res_x + tab->len.x] = 0xffeead;
	}
}

void	handle_angle(t_map *tab)
{
	if (tab->key.respawn)
	{
		tab->pos_x = tab->len.spawnX;
		tab->pos_y = tab->len.spawnY;
		tab->angle = tab->len.spawnAngle;
	}
	if (tab->key.tournerG)
		tab->angle -= 2.5;
	if (tab->key.tournerD)
		tab->angle += 2.5;
}

void	handle_mouv(t_map *tab)
{
	tab->key.vitMarche = (tab->key.sprint == 1 ? 0.3: 0.15);
	if (tab->key.avancer)
	{
		if (tab->map[(int)(tab->pos_x + cos(tab->angle * (M_PI / 180)) * tab->key.vitMarche)][(int)tab->pos_y] == '0')
			tab->pos_x += cos(tab->angle * (M_PI / 180)) * tab->key.vitMarche;
		if (tab->map[(int)tab->pos_x][(int)(tab->pos_y + sin(tab->angle * (M_PI / 180)) * tab->key.vitMarche)] == '0')
			tab->pos_y += sin(tab->angle * (M_PI / 180)) * tab->key.vitMarche;
	}
	if (tab->key.reculer)
	{
		if (tab->map[(int)(tab->pos_x - cos(tab->angle * (M_PI / 180)) * tab->key.vitMarche)][(int)tab->pos_y] == '0')
			tab->pos_x -= cos(tab->angle * (M_PI / 180)) * tab->key.vitMarche;
		if (tab->map[(int)tab->pos_x][(int)(tab->pos_y - sin(tab->angle * (M_PI / 180)) * tab->key.vitMarche)] == '0')
			tab->pos_y -= sin(tab->angle * (M_PI / 180)) * tab->key.vitMarche;
	}
	if (tab->key.gauche)
	{
		tab->len.planx = cos((tab->angle + 90) * M_PI / 180) * 0.66;
		if (tab->map[(int)(tab->pos_x - tab->len.planx * tab->key.vitMarche)][(int)tab->pos_y] == '0')
			tab->pos_x -= tab->len.planx * tab->key.vitMarche;
		tab->len.plany = sin((tab->angle + 90) * M_PI / 180) * 0.66;
		if (tab->map[(int)tab->pos_x][(int)(tab->pos_y - tab->len.plany * tab->key.vitMarche)] == '0')
			tab->pos_y -= tab->len.plany * tab->key.vitMarche;
	}
	if (tab->key.droite)
	{
		tab->len.planx = cos((tab->angle + 90) * M_PI / 180) * 0.66;
		if (tab->map[(int)(tab->pos_x + tab->len.planx * tab->key.vitMarche)][(int)tab->pos_y] == '0')
			tab->pos_x += tab->len.planx * tab->key.vitMarche;
		tab->len.plany = sin((tab->angle + 90) * M_PI / 180) * 0.66;
		if (tab->map[(int)tab->pos_x][(int)(tab->pos_y + tab->len.plany * tab->key.vitMarche)] == '0')
			tab->pos_y += tab->len.plany * tab->key.vitMarche;
	}

}

int key_press(int keycode, t_map *tab)
{
	tab->key.tournerG = (keycode == 123 ? 1 : tab->key.tournerG); // fleche gauche rotation gauche
	tab->key.tournerD = (keycode == 124 ? 1 : tab->key.tournerD); // fleche gauche rotation droite
	tab->key.avancer = (keycode == 13 ? 1 : tab->key.avancer);   // W avancer
	tab->key.reculer = (keycode == 1 ? 1 : tab->key.reculer);    // S reculer
	tab->key.gauche = (keycode == 0 ? 1 : tab->key.gauche);     // A aller a gauche
	tab->key.droite = (keycode == 2 ? 1 : tab->key.droite);     // D aller a droite
	tab->key.sprint = (keycode == 257 ? 1 : tab->key.sprint);     // shift sprint
	tab->key.respawn = (keycode == 15 ? 1 : tab->key.respawn);     // respawn
	tab->key.fovgod = (keycode == 3 ? 1 : tab->key.fovgod);     // respawn
	printf("%d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(tab->mlx.mlx_ptr, tab->mlx.win);
		exit(0);
	}
	return (0);
}

int	key_release(int keycode, t_map *tab)
{

	(keycode == 123 ? tab->key.tournerG-- : 0);
	(keycode == 124 ? tab->key.tournerD-- : 0);
	(keycode == 13 ? tab->key.avancer-- : 0);
	(keycode == 1 ? tab->key.reculer-- : 0);
	(keycode == 0 ? tab->key.gauche-- : 0);
	(keycode == 2 ? tab->key.droite-- : 0);
	(keycode == 257 ? tab->key.sprint-- : 0);
	(keycode == 15 ? tab->key.respawn-- : 0);
	(keycode == 3 ? tab->key.fovgod-- : 0);
	
	return (0);
}

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
			// if (tab->len.x == tab->res_x / 2)
			// {
				// printf("rayDirX = %f", tab->len.rayDirX);	
				// printf("angle = |%f|", tab->angle);
				// printf("distance[%d] == |%f|\n", tab->len.x, tab->len.perpWallDist);
			// }
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