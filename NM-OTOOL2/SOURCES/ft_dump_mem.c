/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dump_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 14:52:30 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/19 12:54:36 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void				ft_dump_mem(void *ptr, int len, int col, void *header)
{
	int		i;
	int		filetype;
	char	*mem;
	char	*init;

	mem = ptr;
	init = ptr;
	i = 0;
	filetype = ((t_mach_header_64*)header)->filetype;
	while (i < len)
	{
		if ((i == 0 || i % col == 0) && filetype == MH_OBJECT)
			ft_printf("%016lx\t", (long)ptr - (long)init);
		else if ((i == 0 || i % col == 0) && filetype == MH_EXECUTE)
			ft_printf("%016lx\t", (long)ptr - (int)header);
		else if ((i == 0 || i % col == 0) && filetype == MH_DYLIB)
			ft_printf("%016lx\t", (long)ptr - (long)header);
		else if (i == 0 || i % col == 0)
			ft_printf("%016lx\t", (long)ptr);
		ft_printf("%02hhx ", mem[i]);
		ptr++;
		i++;
		if (i == len || i % col == 0)
			ft_printf("\n");
	}
}
