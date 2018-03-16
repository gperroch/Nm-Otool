/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_otool.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 09:50:06 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/16 14:36:59 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void		ft_errors(int type, int value, char *file_name) // Pour OTOOL
{
	if (type == ARGS_NUMBER)
	{
		ft_printf("error: ft_otool: at least one file must be specified\n");
		exit(1); // Valeur a verifier
	}
	if (type == INVALID_FILE)
	{
//		ft_printf("ft_otool: '%s': %s\n",
//			file_name, "The file was not recognized as a valid object file"); // A mutualiser avec le message de ft_analyse
		ft_printf("%s: is not an object file\n", file_name);
	}
	if (type == MAPPING_ERROR)
		ft_printf("ERROR in ft_mapping_file() for %s.\n", file_name);
	if (type == NOT_EXISTING)
		ft_printf("ft_otool: %s: %s\n", file_name, "No such file or directory.");
	if (type == NO_PERM)
		ft_printf("ft_otool: %s: %s\n", file_name, "Permission denied.");
	if (type == CORRUPTED)
		ft_printf("ft_otool: %s truncated or malformed object\n\n", file_name);
	(void)value; // ?? A ENLEVER DANS LES DEUX ?
}
