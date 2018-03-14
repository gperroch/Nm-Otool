/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_distance_file_object.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:04:43 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/14 12:04:53 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int					ft_calculate_distance_file_object(t_static_lib *start_obj)
{
	int				diff;
	int				distance;

	diff = (char*)start_obj->end_identifier
		+ ft_strlen(start_obj->end_identifier)
		- (char*)start_obj;
	distance = ((diff / 8) + 1) * 8;
	distance = diff % 8 > 4 ? distance + 8 : distance;
	return (distance);
}
