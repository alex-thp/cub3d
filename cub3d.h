/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 11:18:10 by ade-temm          #+#    #+#             */
/*   Updated: 2019/12/14 08:45:34 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"

typedef struct	s_color
{
	int			blue;
	int			green;
	int			red;
	int			trans;
	char		*text;
}				t_color;


typedef struct	s_doc
{
	char		*R;
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	char		*S;
	char		*F;
	char		*C;
	char		*map;

}				t_doc;

typedef struct	s_key
{
	double		vitMarche;
	double		vitRotation;
	int			avancer;
	int			reculer;
	int			tournerG;
	int			tournerD;
	int			droite;
	int			gauche;
	int			sprint;
	int			respawn;
	int			fovgod;
}				t_key;

typedef struct	s_text
{
	int			width;
	int			height;
	void		*img;
	int			*pix;
	int			bpp;
	int			size;
	int			endian;

}				t_text;

typedef struct	s_libx
{
	void	*mlx_ptr;
	void	*win;
	void	*img;
	void	*img_floor;
	void	*img_sky;
	int		*pix;
}				t_libx;

typedef struct	s_len
{	
	double			spawnX;
	double			spawnY;
	double			spawnAngle;
	double 		planx;
	double 		plany;
	int			x;
	int			w;
	int			h;
	double		heightline;
	int			ray_start;
	int			ray_end;
	double		cameraX;
	double		perpWallDist;
	double		rayDirX;
	double		rayDirY;
	double		deltaDistX;
	double		deltaDistY;
	int 		entier_x;
	int 		entier_y;
	double		stepX;
	double		stepY;
	double		norme;
	int			hit;
	double		sideDistX;
	double		sideDistY;
	int			side;
	double		wallX;
	int 		textX;
	double 		textY;
}				t_len;


typedef struct	s_map
{
	int			res_y;
	int			res_x;
	char		**map;
	double		angle;
	double		pos_x;
	double		pos_y;
	int			map_x;
	int			map_y;
	int			premierAffichage;
	t_doc		doc;
	t_key		key;
	t_len		len;
	t_libx		mlx;
	t_text 		dst_N;
	t_text 		dst_S;
	t_text 		dst_W;
	t_text 		dst_E;
}				t_map;

void	parse_map(char **av, t_map	*tab);
char	*clean_str(char *str);
void	ft_perfect_parse(t_map *tab);
void	clean_map(t_map *tab);
void	position(t_map *tab);
void	wall_distance(t_map *tab);
void	ft_init_ray(t_map *tab);
void	calc_dist_xy(t_map *tab);
void	calc_dist(t_map *tab);
void	ft_init_mlx(t_map *tab);
void	display_ray(t_map *tab);
void	handle_angle(t_map *tab);
void	handle_mouv(t_map *tab);
int		key_release(int keycode, t_map *tab);
int 	key_press(int keycode, t_map *tab);
int		loop_game(t_map *tab);
int 	*texture_resize(t_map *tab, t_text *src, int	width, int height);
void	get_texture(t_map *tab);
#endif
