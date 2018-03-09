/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:26:40 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/09 17:38:06 by gperroch         ###   ########.fr       */
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
	file_name = ""; // A tester en conjonction avec la ligne 31;
	if (argc < 2)
	{
		ft_errors(ARGS_NUMBER, argc, ""); // Pour nm rien ne se passe. Pour Otool si argc < 2 => exit
		file_name = ft_strdup("a.out"); // Passe ici uniquement dans le cas de NM. Ft_errors exit le programme obligatoirement dans le cas de otool (argc < 2)
		argc++;
	}
	while (++file_number < argc)
	{
		//file_name = ""; // Pourquoi la ligne 26 donc ?? Sortir celle-ci avant la ligne 23 ??
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
