/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 11:18:10 by ade-temm          #+#    #+#             */
/*   Updated: 2019/12/16 23:36:03 by thverney         ###   ########.fr       */
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
	int			hex;
}				t_color;


typedef struct	s_doc
{
	char		*R;
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	char		*S;
	t_color		F;
	t_color		C;
	char		*map;
	char		*temp;

}				t_doc;

typedef struct	s_key
{
	double		speed;
	int			front;
	int			back;
	int			rotL;
	int			rotR;
	int			moveR;
	int			moveL;
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
	int			smallval;

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
	int 		textXN;
	int 		textXS;
	int 		textXW;
	int 		textXE;
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
	int			error;
	int			tmp_err;
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
void	clean_map(t_map *tab);
void	position(t_map *tab);
void	wall_distance(t_map *tab);
void	ft_init_ray(t_map *tab);
void	calc_dist_xy(t_map *tab);
void	calc_dist(t_map *tab);
void	ft_init_mlx(t_map *tab);
void	display_ray(t_map *tab);
void	handle_angle(t_map *tab);
void	handle_move(t_map *tab);
void	back_front(t_map *tab);
void	left_right(t_map *tab);
int		key_release(int keycode, t_map *tab);
int 	key_press(int keycode, t_map *tab);
int		loop_game(t_map *tab);
int 	*texture_resize(t_map *tab, t_text *src, int	width, int height);
void	get_texture(t_map *tab);
int		is_loopable(t_map *tab);
void	get_texture_X(t_map *tab);
void	doc_checker(char *str, t_map *tab);
void	doc_resolution(char *str, t_map *tab);
void	doc_way(char *str, t_map *tab, int way);
void	doc_color_F(char *str, t_map *tab);
void	doc_color_C(char *str, t_map *tab);
void	ft_error(int error, t_map *tab);
void	doc_way_fd(t_map *tab, int way);
void	ft_map_check(t_map *tab);
int 	splitmap(char *str, int i, int len, t_map *tab);
void	ft_exit_error(t_map *tab);
void	ft_put_in_hex(t_map *tab, int i);
#endif