/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 11:18:10 by ade-temm          #+#    #+#             */
/*   Updated: 2019/12/06 19:54:26 by ade-temm         ###   ########.fr       */
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

typedef struct	s_len
{
	double		v_x;
	double		v_y;
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
}				t_len;

typedef struct	s_map
{
	int			res_y;
	int			res_x;
	char		**map;
	double		angle;
	double		pos_x;
	double		pos_y;
	double		cam_x;
	double		cam_y;
	t_color		floor;
	t_color		plafond;
}				t_map;

#endif
