/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_has_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:21:34 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/12 15:21:49 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int						ft_has_print(char *str)
{
	char				has_print;
	int					len;

	has_print = 0;
	len = ft_strlen(str);
	while (len > 0)
	{
		if (ft_isprint(str[len - 1]))
			has_print = 1;
		len--;
	}
	return (has_print);
}
