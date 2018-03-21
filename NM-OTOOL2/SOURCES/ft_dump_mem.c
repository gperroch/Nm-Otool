/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dump_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 14:52:30 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/21 17:31:56 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void				ft_dump_mem(void *ptr, int len, int col, t_generic_file *gen)
{
	int		i;
	int		filetype;
	char	*mem;
	char	*init;

	mem = ptr;
	init = ptr;
	i = 0;
	filetype = ((t_mach_header_64*)(gen->header))->filetype;
//	ft_printf("g_isppc = %d\n", g_isppc);
	while (i < len)
	{
		if ((i == 0 || i % col == 0) && filetype == MH_OBJECT)
			ft_printf("%016lx\t", (long)ptr - (long)init);
		else if ((i == 0 || i % col == 0) && filetype == MH_EXECUTE)
			ft_printf("%016lx\t", (long)ptr - (int)(gen->header));
		else if ((i == 0 || i % col == 0) && filetype == MH_DYLIB)
			ft_printf("%016lx\t", (long)ptr - (long)(gen->header));
		else if (i == 0 || i % col == 0)
			ft_printf("%016lx\t", (long)ptr);

		if (g_isppc)
			ft_dump_mem_ppc(&ptr, &i, mem);
		else
			ft_printf("%02hhx ", mem[i]);
		i++;
		ptr++;
		if (i == len || i % col == 0)
			ft_printf("\n");
	}
}

void				ft_dump_mem_32(void *ptr, int len, int col, t_generic_file *gen)
{
	int		i;
	int		filetype;
	char	*mem;
	char	*init;

	mem = ptr;
	init = ptr;
	i = 0;
	filetype = ((t_mach_header_64*)(gen->header))->filetype;
	while (i < len)
	{
		if ((i == 0 || i % col == 0) && filetype == MH_OBJECT)
			ft_printf("%08lx\t", (char*)ptr - init + 0x1000);
		else if ((i == 0 || i % col == 0) && filetype == MH_EXECUTE)
			ft_printf("%08lx\t", ptr - (void*)(gen->header) + 0x1000);
		else if ((i == 0 || i % col == 0) && (filetype == MH_DYLIB || g_isppc))
			ft_printf("%08lx\t", ptr - (void*)(gen->header) + 0x1000);
		else if (i == 0 || i % col == 0)
			ft_printf("%08lx\t", ptr + 0x1000);

		if (g_isppc)
			ft_dump_mem_ppc(&ptr, &i, mem);
		else
			ft_printf("%02hhx ", mem[i]);
		i++;
		ptr++;
		if (i == len || i % col == 0)
			ft_printf("\n");
	}
}

void				ft_dump_mem_ppc(void **ptr, int *i, char *mem)
{
		ft_printf("%02hhx", mem[*i]);
		ft_printf("%02hhx", mem[*i + 1]);
		ft_printf("%02hhx", mem[*i + 2]);
		ft_printf("%02hhx ", mem[*i + 3]);
		*i += 3;
		*ptr += 3;
}

/*void				ft_dump_mem_ppc(void *ptr, int len, int col, t_generic_file *gen)
{
	int		i;
	int		filetype;
	char	*mem;
	char	*init;

	mem = ptr;
	init = ptr;
	i = 0;
	filetype = ((t_mach_header_64*)(gen->header))->filetype;
//	ft_printf("g_isppc = %d\n", g_isppc);
	while (i < len)
	{
//		ft_printf("\nptr[%08lx] init[%08lx] gen->header[%08lx] (ptr - init)[%08lx] (ptr - gen->header)[%08lx]\n", ptr, init, gen->header, (char*)ptr - init, (char*)ptr - (char*)(gen->header));
		if ((i == 0 || i % col == 0) && filetype == MH_OBJECT)
			ft_printf("%08lx\t", (char*)ptr - init + 0x1000);
		else if ((i == 0 || i % col == 0) && filetype == MH_EXECUTE)
			ft_printf("%08lx\t", ptr - (void*)(gen->header) + 0x1000);
		else if ((i == 0 || i % col == 0) && filetype == MH_DYLIB)
			ft_printf("%08lx\t", ptr - (void*)(gen->header) + 0x1000);

		else if ((i == 0 || i % col == 0) && g_isppc)
			ft_printf("%08lx\t", ptr - (void*)(gen->header) + 0x1000);

		else if (i == 0 || i % col == 0)
			ft_printf("%08lx\t", ptr + 0x1000);

		// Valable pour /usr/bin/audiodevice
		ft_printf("%02hhx", mem[i]);
		ft_printf("%02hhx", mem[i + 1]);
		ft_printf("%02hhx", mem[i + 2]);
		ft_printf("%02hhx ", mem[i + 3]);
		i += 4;

		ptr += 4;
		if (i == len || i % col == 0)
			ft_printf("\n");
	}
}*/
