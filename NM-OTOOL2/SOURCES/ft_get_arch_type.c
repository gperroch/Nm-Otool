/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_arch_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:47:16 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/12 17:47:33 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

char					*ft_get_arch_type(int cputype) // Traiter tous les types et sous-types. Tester avec d'autres cputype et cpusubtype
{
	char				*str;

	if (cputype == CPU_TYPE_X86)
		str = ft_strdup("i386");
	else if (cputype == CPU_TYPE_X86_64)
		str = ft_strdup("x86_64");
	else if (cputype == CPU_TYPE_POWERPC)
		str = ft_strdup("ppc");
	else
		str = ft_strdup("undefined");
	return (str);
}
