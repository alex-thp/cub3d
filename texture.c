/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 20:31:16 by thverney          #+#    #+#             */
/*   Updated: 2019/12/14 09:20:29 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		*texture_resize(t_map *tab, t_text *src, int width, int height)
{
	t_text dst;
	double	size_x;
	double	size_y;
	int		x;
	int		y;
	
	size_x = (src->width / (double)width);
	size_y = (src->height / (double)height);
	
	dst.img = mlx_new_image(tab->mlx.mlx_ptr, width, height);
	src->pix = (int *)mlx_get_data_addr(src->img, &src->bpp, &src->size, &src->endian);
	dst.pix = (int *)mlx_get_data_addr(dst.img, &dst.bpp, &dst.size, &dst.endian);
	
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
		{
			dst.pix[x + (y * dst.size / 4)] = src->pix[(int)(((int)(x * size_x) + ((int)(y * size_y) * (src->size / 4))))];
		}
	}
	return (dst.pix);
}

void	get_texture(t_map *tab)
{
	t_text src;
	int width;
	int	height;
	width = tab->res_x;
	height = tab->res_y;

	src.img =  mlx_xpm_file_to_image(tab->mlx.mlx_ptr, "./texture/cubwall.xpm", &(src.width) , &(src.height)); // NORD
	tab->dst_N.pix = (int *)mlx_get_data_addr(src.img, &src.bpp, &src.size, &src.endian);
	// tab->dst_N.pix = texture_resize(tab ,&src, width, height);
	tab->dst_N.img = src.img;
	tab->dst_N.height = height;
	tab->dst_N.width = width;
}
