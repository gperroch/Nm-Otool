/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:28:37 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/07 17:32:51 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define ARGS_NUMBER 1

void		ft_errors(int type, int value) // Pour NM
{
	if (type == ARGS_NUMBER)
		return;
}






void		ft_errors(int type, int value) // Pour OTOOL
{
	if (type == ARGS_NUMBER && value < 2)
	{
		ft_printf("error: ft_otool: at least one file must be specified\n");
		exit(1); // Valeur a verifier
	}
}
