/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 09:01:58 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/19 15:06:40 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*tmp;

	if (!(tmp = (void*)malloc(sizeof(void) * size)))
		return (0);
//	printf("ALLOC1:%p\n", tmp); ///// NEW
	ft_bzero(tmp, size);
	return (tmp);
}
