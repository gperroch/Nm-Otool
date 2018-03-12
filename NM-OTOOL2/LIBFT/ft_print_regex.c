/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_regex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 18:32:25 by gperroch          #+#    #+#             */
/*   Updated: 2017/10/19 19:19:11 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_print_regex(char *restrict *format, va_list ap)
{
	char	*regex_printed;
	char	specifier;
	int		len;
	int		size_s;

	len = 0;
	size_s = 1;
	specifier = ft_print_specifier(++(*format));
	if (!(regex_printed = ft_print_conv(*format, ap, specifier, &size_s)))
	{
		ft_close_regex(format, specifier);
		return (0);
	}
	(regex_printed[0] == 0 && (specifier == 'c'
		|| specifier == 'C')) ? (len++) : (0);
	regex_printed = ft_print_extra(*format, &regex_printed, specifier, size_s);
	ft_close_regex(format, specifier);
	len += ft_strlen(regex_printed);
	write(1, regex_printed, len);
	(len == 0 && (specifier == 'c' || specifier == 'C')) ? (len = 1) : (0);
	free(regex_printed);
	return (len);
}
