/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proceed_lib_nm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 11:17:20 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/21 14:41:44 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

// Meme probleme qu'avec les macho, il manque un 1 dans les adresses des objects

t_symbol_display			*ft_proceed_lib(t_generic_file *gen, int argc)
{
	(void)argc;
	ft_static_library(gen);
	return (NULL);
}
