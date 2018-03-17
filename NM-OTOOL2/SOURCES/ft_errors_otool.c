/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_otool.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 09:50:06 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/17 16:13:23 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void		ft_errors(int type, char *file_name)
{
	if (type == ARGS_NUMBER)
	{
		ft_printf("error: ft_otool: at least one file must be specified\n");
		exit(EXIT_FAILURE);
	}
	if (type == INVALID_FILE)
		ft_printf("%s: is not an object file\n", file_name);
	if (type == MAPPING_ERROR)
		ft_printf("ERROR in ft_mapping_file() for %s.\n", file_name);
	if (type == NOT_EXISTING)
		ft_printf("ft_otool: %s: %s\n", file_name, "No such file or directory");
	if (type == NO_PERM)
		ft_printf("ft_otool: %s: %s\n", file_name, "Permission denied.");
	if (type == CORRUPTED)
		ft_printf("ft_otool: %s truncated or malformed object\n\n", file_name);
}
