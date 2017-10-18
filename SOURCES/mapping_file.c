/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 13:44:28 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/18 10:19:50 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int				ft_mapping_file(char *file_name, void **file_content,
	struct stat *stats)
{
	int			fd;

	fd = open(file_name, O_RDONLY);
	if (fstat(fd, stats))
		return (-1);
	if ((*file_content =
		mmap(0, stats->st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (-1);
	close(fd);
	return (0);
}
