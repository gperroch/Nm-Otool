/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dump_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 14:52:30 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/16 17:51:12 by gperroch         ###   ########.fr       */
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
		i++;
		/*****/ // Valable pour /usr/bin/audiodevice
/*		ft_printf("%02hhx", mem[i]);
		ft_printf("%02hhx", mem[i + 1]);
		ft_printf("%02hhx", mem[i + 2]);
		ft_printf("%02hhx ", mem[i + 3]);
		i += 4;
*/		/*****/
		ptr++;
		if (i == len || i % col == 0)
			ft_printf("\n");
	}
}

void				ft_dump_mem_32(void *ptr, int len, int col, void *header)
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
			ft_printf("%08lx\t", (char*)ptr - init + 0x1000);
		else if ((i == 0 || i % col == 0) && filetype == MH_EXECUTE)
			ft_printf("%08lx\t", ptr - header + 0x1000);
		else if ((i == 0 || i % col == 0) && filetype == MH_DYLIB)
			ft_printf("%08lx\t", ptr - header + 0x1000);
		else if (i == 0 || i % col == 0)
			ft_printf("%08lx\t", ptr + 0x1000);
		ft_printf("%02hhx ", mem[i]);
		i++;
		/*****/ // Valable pour /usr/bin/audiodevice
/*		ft_printf("%02hhx", mem[i]);
		ft_printf("%02hhx", mem[i + 1]);
		ft_printf("%02hhx", mem[i + 2]);
		ft_printf("%02hhx ", mem[i + 3]);
		i += 4;
*/		/*****/
		ptr++;
		if (i == len || i % col == 0)
			ft_printf("\n");
	}
}
