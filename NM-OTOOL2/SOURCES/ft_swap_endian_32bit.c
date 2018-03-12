/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_endian_32bit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:55:01 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/12 17:55:14 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int						ft_swap_endian_32bit(int nbr) // ATTENTION AUX NOMBRES DANS LES NOMS DE FONCTION
{
	int					swapped;

	swapped =	((nbr>>24)&0xff) | // move byte 3 to byte 0
				((nbr<<8)&0xff0000) | // move byte 1 to byte 2
				((nbr>>8)&0xff00) | // move byte 2 to byte 1
				((nbr<<24)&0xff000000); // byte 0 to byte 3
	return (swapped);
}
