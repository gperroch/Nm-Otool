/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapping_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:26:40 by gperroch          #+#    #+#             */
/*   Updated: 2018/03/07 17:38:15 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int						main(int argc, char **argv)
{
	char				*file_name;
	int					file_number;
	void				*file_content;
	struct stat			stats;
	int					mapping_result;

	file_number = 0;
	if (argc < 2)
	{
		ft_errors(ARGS_NUMBER, argc); // Pour nm rien ne se passe. Pour Otool si argc < 2 => exit
		file_name = ft_strdup("a.out"); // Passe ici uniquement dans le cas de NM. Bloque par ft_errors
		argc++;
	}
	while (++file_number < argc)
	{
		file_name = ""; // Pourquoi la ligne 25 donc ?? Sortir celle-ci avant la ligne 22 ??
		file_content = NULL;
		if (!(argc == 2 && file_number == 1 && !ft_strcmp(file_name, "a.out")))
			file_name = argv[file_number];
		if ((mapping_result = ft_mapping_file(file_name, &file_content, &stats)) > 0)
		{
			ft_analyse_file(file_content, file_name, argc, stats.st_size); // Cette fonction va radicalement changer.
			munmap(file_content, stats.st_size);
		}
		else if (mapping_result == -1)
			ft_printf("ERROR in ft_mapping_file() for %s.\n", file_name);
		else if (errno == EACCES)
			ft_printf("ft_nm: %s: %s\n", file_name, "Permission denied.");
		else if (errno == ENOENT)
			ft_printf("ft_nm: %s: %s\n", file_name, "No such file or directory.");
		else
			ft_printf("ft_nm: %s %s\n\n",
				file_name, "The file was not recognized as a valid object file"); // A mutualiser avec le message de ft_analyse()
	}
	return (0);
}
