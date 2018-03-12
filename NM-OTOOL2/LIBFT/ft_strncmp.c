/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 11:23:48 by gperroch          #+#    #+#             */
/*   Updated: 2016/02/17 11:32:35 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (s1[i] != '\0' && i < n)
	{
		if (s2[i] == '\0')
			return (1);
		if (s1[i] != s2[i])
			return (((unsigned char)s1[i] > (unsigned char)s2[i]) ? 1 : -1);
		i++;
	}
	if (s2[i] != '\0' && i != n)
		return (-1);
	return (0);
}
