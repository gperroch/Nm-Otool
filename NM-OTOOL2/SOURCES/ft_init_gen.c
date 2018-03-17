/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_gen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:16:36 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/17 16:58:32 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

t_generic_file		*ft_init_gen(char *file_name, void *file_content,
	off_t file_size)
{
	t_generic_file	*gen;

	if (!(gen = (t_generic_file *)malloc(sizeof(t_generic_file))))
		return (NULL);
	ft_bzero(gen, sizeof(t_generic_file));
	gen->file_size = file_size;
	gen->file_name = file_name;
	gen->file_start = file_content;
	gen->endian_mach = BIGEND;
	gen->endian_fat = BIGEND;
	gen->arch = 64;
	return (gen);
}
