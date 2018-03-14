/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_section_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:20:24 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/14 18:53:25 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

char						ft_section_type(t_section_64 *section, t_generic_file *gen)
{
	char					res;

	(void)gen; // A ENLEVER SI INUTILISEE
	if (!ft_has_print(section->sectname))
		return (0);
	//ft_printf("[%p][%s]\n", section, section->sectname);
	res = 'S';
	res = !ft_strcmp(section->sectname, "__text") ? 'T' : res;
	res = !ft_strcmp(section->sectname, "__data") ? 'D' : res;
	res = !ft_strcmp(section->sectname, "__bss") ? 'B' : res;
	res = !ft_strcmp(section->sectname, "__common") &&
			ft_strcmp(section->segname, "__DATA") ? 'C' : res;
	return (res);
}
