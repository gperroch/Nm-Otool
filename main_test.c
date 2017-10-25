#include <stdio.h>
# include <mach-o/ranlib.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <string.h>

#define MACH_HEADER 3
#define SIZE_MACH_HEADER_32 sizeof(struct mach_header)
#define SIZE_MACH_HEADER_64 sizeof(struct mach_header_64)

int			ft_arch_gateway(int arch, int element);

typedef	struct		s_generic
{
	void			*header;
}					t_generic;


int							main(int arc, char **argv)
{
	t_generic				gen;
	struct mach_header		header_32;
	struct mach_header_64	header_64;
	long	i;

	if (arc < 2)
	{
		printf("Missing argument.\n");
		return (0);
	}
	if (!strcmp(argv[1], "32") || !strcmp(argv[1], "64"))
		printf("header size = %d\n", ft_arch_gateway(atoi(argv[1]), MACH_HEADER));
	else 
		printf("Unknown type.\n");

	if (!strcmp(argv[1], "64"))
	{
		char		i = 'c';
	}
	else if (!strcmp(argv[1], "32"))
	{
		long	i;
	}
	printf("=> %zu\n", sizeof(i));

	printf("OK\n");
	return (0);
}


int			ft_arch_gateway(int arch, int element)
{
	int		ret;

	if (arch != 32 && arch != 64)
		return -1;
	if (element == MACH_HEADER)
		ret = arch == 32 ? SIZE_MACH_HEADER_32 : SIZE_MACH_HEADER_64;
	return ret;
}
