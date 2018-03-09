/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapping_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 13:44:28 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/09 09:59:06 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int						ft_mapping_file(char *file_name, void **file_content,
	struct stat *stats)
{
	int					fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0 || fstat(fd, stats) || stats->st_size == 0)
		return (-2);
	else if (stats->st_size != 0 && (*file_content =
		mmap(0, stats->st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (-1);
	close(fd);
	return (1);
}

void					ft_free_list_symbols(t_symbol_display *list)
{
	t_symbol_display	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp)
			free(tmp);
	}
}
