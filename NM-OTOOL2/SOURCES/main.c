/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:26:40 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/12 14:16:02 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "nm_otool.h"

int						main(int argc, char **argv)
{
	char				*file_name;
	int					file_number;
	void				*file_content;
	struct stat			stats;
	int					mapping_result;

	file_number = 0;
	file_name = "";
	if (argc < 2)
	{
		ft_errors(ARGS_NUMBER, argc, "");
		file_name = ft_strdup("a.out");
		argc++;
	}
	while (++file_number < argc)
	{
		file_content = NULL;
		if (!(argc == 2 && file_number == 1 && !ft_strcmp(file_name, "a.out"))) // Va certainement poser probleme pour otool
			file_name = argv[file_number];
		if ((mapping_result = ft_mapping_file(file_name, &file_content, &stats)) > 0)
		{
			ft_analyse_file(file_content, argc, file_name, stats.st_size);
			munmap(file_content, stats.st_size);
		}
		else if (mapping_result == -1)
			ft_errors(MAPPING_ERROR, 0, file_name);
		else if (errno == EACCES)
			ft_errors(NO_PERM, 0, file_name);
		else if (errno == ENOENT)
			ft_errors(NOT_EXISTING, 0, file_name);
		else
			ft_errors(INVALID_FILE, 0, file_name);
	}
	return (0);
}
