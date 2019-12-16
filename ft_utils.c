/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 10:56:13 by thverney          #+#    #+#             */
/*   Updated: 2019/12/14 14:54:19 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_loopable(t_map *tab)
{
	if (tab->premierAffichage-- == 1 || tab->key.rotL || tab->key.rotR
	|| tab->key.front || tab->key.back || tab->key.moveL
	|| tab->key.moveR || tab->key.respawn)
		return (1);
	return (0);
}
