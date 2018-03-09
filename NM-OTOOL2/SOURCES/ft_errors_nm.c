/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_nm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:28:37 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/09 09:55:10 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Ajouter des params variables comme dans printf
#include "libft.h"
#define ARGS_NUMBER 1
#define INVALID_FILE 2
#define MAPPING_ERROR 3
#define NOT_EXISTING 4
#define NO_PERM 5
void		ft_errors(int type, int value, char *file_name) // Pour NM
{
	if (type == ARGS_NUMBER)
		return;
	if (type == INVALID_FILE)
	{
		ft_printf("ft_nm: %s %s\n\n",
			file_name, "The file was not recognized as a valid object file"); // A mutualiser avec le message de ft_analyse()
	}
	if (type == NOT_EXISTING)
	{
		ft_printf("ft_nm: %s: %s\n", file_name, "No such file or directory.");
	}
	if (type == NO_PERM)
	{
		ft_printf("ft_nm: %s: %s\n", file_name, "Permission denied.");
	}
}
