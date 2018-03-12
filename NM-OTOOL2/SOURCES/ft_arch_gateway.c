/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arch_gateway.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:45:08 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/12 17:45:28 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int			ft_arch_gateway(int arch, int element)
{
	int		ret;

	if (arch != 32 && arch != 64)
		return (-1);
	if (element == MACH_HEADER)
		ret = arch == 32 ? SIZE_MACH_HEADER_32 : SIZE_MACH_HEADER_64;
	else if (element == SEGMENT_COMMAND)
		ret = arch == 32 ? SIZE_SEGMENT_COMMAND_32 : SIZE_SEGMENT_COMMAND_64;
	else if (element == SECTION)
		ret = arch == 32 ? SIZE_SECTION_32 : SIZE_SECTION_64;
	else if (element == FAT_ARCH)
		ret = arch == 32 ? SIZE_FAT_ARCH_32 : SIZE_FAT_ARCH_64;
	else
		ret = -2;
	return (ret);
}
