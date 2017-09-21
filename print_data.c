/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 17:26:22 by gperroch          #+#    #+#             */
/*   Updated: 2017/03/27 17:35:47 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mach-o/loader.h>
#include "libft.h"

void 		print_data(char *file)
{
	char	*ptr;
	int		count;
	char	*buffer_tmp;
	char	*buffer;
	int		fd;

	fd = open(file, O_RDONLY);
	buffer_tmp = (char*)malloc(32);
	ft_bzero(buffer_tmp, 32);
	while (read(fd, buffer, 31))
	{
		buffer = ft_strjoin(buffer, buffer_tmp);
		ft_bzero(buffer_tmp, 32);
	}

	ptr = (char*)tmp;
	count = 0;
	while (count < size)
	{
		printf("%2x|", ptr[count]);
		if (count % 31 == 0)
			printf("\n");
		count++;
	}
}
