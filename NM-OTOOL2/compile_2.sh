echo "Compilation de NM:"
gcc SOURCES/main.c SOURCES/ft_errors_nm.c SOURCES/ft_mapping_file.c SOURCES/ft_analyse_file.c ../SOURCES/dump_mem.c ../LIBFT/libft.a -I ../INCLUDES -o ft_nm
echo "Compilation de OTOOL:"
gcc SOURCES/main.c SOURCES/ft_errors_otool.c SOURCES/ft_mapping_file.c SOURCES/ft_analyse_file.c ../SOURCES/dump_mem.c ../LIBFT/libft.a -I ../INCLUDES -o ft_otool
