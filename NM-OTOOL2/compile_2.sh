echo "Compilation de NM:"
gcc SOURCES/main.c SOURCES/ft_errors_nm.c SOURCES/ft_mapping_file.c SOURCES/ft_analyse_file.c SOURCES/ft_find_symtab.c SOURCES/ft_create_symbol_list.c SOURCES/ft_locate_symbol_table.c SOURCES/ft_find_section.c SOURCES/ft_fat_arch.c ../SOURCES/dump_mem.c ../SOURCES/ft_dump_mem.c ../LIBFT/libft.a -I INCLUDES -o ft_nm
echo "Compilation de OTOOL:"
gcc SOURCES/main.c SOURCES/ft_errors_otool.c SOURCES/ft_mapping_file.c SOURCES/ft_analyse_file.c SOURCES/ft_find_symtab.c SOURCES/ft_create_symbol_list.c SOURCES/ft_locate_symbol_table.c SOURCES/ft_find_section.c SOURCES/ft_fat_arch.c ../SOURCES/dump_mem.c ../SOURCES/ft_dump_mem.c ../LIBFT/libft.a -I INCLUDES -o ft_otool
