/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proceed_fat_otool.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 11:16:40 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/14 14:34:28 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

// Arreter l'iteration sur les architectures inutiles
// Si identique a l'autre proceed_fat, fusionner

t_symbol_display			*ft_proceed_fat(t_generic_file *gen, int argc) // Contenu de la fonction copie sur ft_proceed_fat_nm, va surement devoir changer
{
	gen->fat_header = (struct fat_header*)(gen->file_start);
	if (argc > 2)
		ft_printf("\n%s:\n", gen->file_name);
	ft_fat_arch(gen); // Changer les params et gen
	return (NULL);
}
