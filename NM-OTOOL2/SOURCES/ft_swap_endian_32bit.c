/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_endian_32bit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:55:01 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/19 13:03:32 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int						ft_swap_endian_32bit(int nbr) // ATTENTION AUX NOMBRES DANS LES NOMS DE FONCTION
{
	int					swapped;

	swapped = ((nbr >> 24) & 0xff) |
			((nbr << 8) & 0xff0000) |
			((nbr >> 8) & 0xff00) |
			((nbr << 24) & 0xff000000);
	return (swapped);
}
