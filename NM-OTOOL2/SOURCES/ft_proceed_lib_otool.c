/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proceed_lib_otool.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 11:17:57 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/14 14:48:55 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

t_symbol_display			*ft_proceed_lib(t_generic_file *gen, int argc)
{
	(void)argc; // ??
	ft_printf("Archive : %s\n", gen->file_name);
	ft_find_texttext_static_library(gen->file_start, gen->file_name);
	return (NULL);
}
