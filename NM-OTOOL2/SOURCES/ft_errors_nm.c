/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_nm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:28:37 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/12 17:53:22 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void		ft_errors(int type, int value, char *file_name) // Pour NM
{
	if (type == ARGS_NUMBER)
		return;
	if (type == INVALID_FILE)
	{
		ft_printf("ft_nm: %s %s\n\n",
			file_name, "The file was not recognized as a valid object file"); // A mutualiser avec le message de ft_analyse()
	}
	if (type == MAPPING_ERROR)
		ft_printf("ERROR in ft_mapping_file() for %s.\n", file_name);
	if (type == NOT_EXISTING)
		ft_printf("ft_nm: %s: %s\n", file_name, "No such file or directory.");
	if (type == NO_PERM)
		ft_printf("ft_nm: %s: %s\n", file_name, "Permission denied.");
	if (type == CORRUPTED)
		ft_printf("ft_nm: %s truncated or malformed object\n\n", file_name);
		//ft_printf("ft_nm: %s truncated or malformed object max_addr[%p] ptr[%p]\n\n", file_name, max_addr, ptr);
	(void)value; // ?? A ENLEVER DANS LES DEUX ?
}
