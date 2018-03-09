/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_otool.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 09:50:06 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/09 09:55:05 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define ARGS_NUMBER 1
#define INVALID_FILE 2
#define MAPPING_ERROR 3
#define NOT_EXISTING 4
#define NO_PERM 5
void		ft_errors(int type, int value, char *file_name) // Pour OTOOL
{
	if (type == ARGS_NUMBER)
	{
		ft_printf("error: ft_otool: at least one file must be specified\n");
		exit(1); // Valeur a verifier
	}
	if (type == INVALID_FILE)
	{
		ft_printf("ft_otool: '%s': %s\n",
			file_name, "The file was not recognized as a valid object file"); // A mutualiser avec le message de ft_analyse
	}
	if (type == MAPPING_ERROR)
	{
		ft_printf("ERROR in ft_mapping_file() for %s.\n", file_name);
	}
	if (type == NOT_EXISTING)
	{
		ft_printf("ft_otool: %s: %s\n", file_name, "No such file or directory.");
	}
	if (type == NO_PERM)
	{
		ft_printf("ft_otool: %s: %s\n", file_name, "Permission denied.");
	}
}
