/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 20:31:16 by thverney          #+#    #+#             */
/*   Updated: 2019/12/17 00:39:30 by thverney         ###   ########.fr       */
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
	t_text *src;
	int width;
	int	height;

	if (!(src = (t_text*)malloc(sizeof(t_text))))
		return ;
	width = tab->res_x;
	height = tab->res_y;

	src->img =  mlx_xpm_file_to_image(tab->mlx.mlx_ptr, tab->doc.NO, &(tab->dst_N.width) , &(tab->dst_N.height)); // NORD
	tab->dst_N.pix = (int *)mlx_get_data_addr(src->img, &src->bpp, &src->size, &src->endian);
	tab->dst_N.img = src->img;
	tab->dst_N.smallval = (tab->dst_N.width <= tab->dst_N.height ? tab->dst_N.width : tab->dst_N.height);
	src->img =  mlx_xpm_file_to_image(tab->mlx.mlx_ptr, tab->doc.SO, &(tab->dst_S.width) , &(tab->dst_S.height)); // NORD
	tab->dst_S.pix = (int *)mlx_get_data_addr(src->img, &src->bpp, &src->size, &src->endian);
	tab->dst_S.img = src->img;
	tab->dst_S.smallval = (tab->dst_S.width <= tab->dst_S.height ? tab->dst_S.width : tab->dst_S.height);
	src->img =  mlx_xpm_file_to_image(tab->mlx.mlx_ptr, tab->doc.WE, &(tab->dst_W.width) , &(tab->dst_W.height)); // NORD
	tab->dst_W.pix = (int *)mlx_get_data_addr(src->img, &src->bpp, &src->size, &src->endian);
	tab->dst_W.img = src->img;
	tab->dst_W.smallval = (tab->dst_W.width <= tab->dst_W.height ? tab->dst_W.width : tab->dst_W.height);
	src->img =  mlx_xpm_file_to_image(tab->mlx.mlx_ptr, tab->doc.EA, &(tab->dst_E.width) , &(tab->dst_E.height)); // NORD
	tab->dst_E.pix = (int *)mlx_get_data_addr(src->img, &src->bpp, &src->size, &src->endian);
	tab->dst_E.img = src->img;
	tab->dst_E.smallval = (tab->dst_E.width <= tab->dst_E.height ? tab->dst_E.width : tab->dst_E.height);

}
