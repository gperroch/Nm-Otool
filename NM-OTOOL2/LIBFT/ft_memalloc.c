/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 09:01:58 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/24 15:58:09 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*tmp;

	if (!(tmp = (void*)malloc(sizeof(void) * size)))
		return (0);
	ft_bzero(tmp, size);
	return (tmp);
}
