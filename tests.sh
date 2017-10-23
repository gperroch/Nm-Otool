#!/bin/bash

echo "./ft_nm ft_otool > res1 && nm ft_otool > res2 && diff res1 res2"
./ft_nm ft_otool > res1 && nm ft_otool > res2 && diff res1 res2
echo "./ft_nm ft_nm > res1 && nm ft_nm > res2 && diff res1 res2"
./ft_nm ft_nm > res1 && nm ft_nm > res2 && diff res1 res2
echo "./ft_nm OBJECTS/nm.o > res1 && nm OBJECTS/nm.o > res2 && diff res1 res2"
./ft_nm OBJECTS/nm.o > res1 && nm OBJECTS/nm.o > res2 && diff res1 res2
echo "./ft_nm libft/libft.a > res1 && nm libft/libft.a > res2 && diff res1 res2"
./ft_nm libft/libft.a > res1 && nm libft/libft.a > res2 && diff res1 res2
echo "./ft_nm INCLUDES/nm_otool.h > res1 && nm INCLUDES/nm_otool.h > res2 && diff res1 res2"
./ft_nm INCLUDES/nm_otool.h > res1 && nm INCLUDES/nm_otool.h > res2 && diff res1 res2

echo " "

echo "./ft_otool ft_otool > res1 && otool -t ft_otool > res2 && diff res1 res2"
./ft_otool ft_otool > res1 && otool -t ft_otool > res2 && diff res1 res2
echo "./ft_otool ft_nm > res1 && otool -t ft_nm > res2 && diff res1 res2"
./ft_otool ft_nm > res1 && otool -t ft_nm > res2 && diff res1 res2
echo "./ft_otool OBJECTS/nm.o > res1 && otool -t OBJECTS/nm.o > res2 && diff res1 res2"
./ft_otool OBJECTS/nm.o > res1 && otool -t OBJECTS/nm.o > res2 && diff res1 res2
echo "./ft_otool libft/libft.a > res1 && otool -t libft/libft.a > res2 && diff res1 res2"
./ft_otool libft/libft.a > res1 && otool -t libft/libft.a > res2 && diff res1 res2
echo "./ft_otool INCLUDES/nm_otool.h > res1 && otool -t INCLUDES/nm_otool.h > res2 && diff res1 res2"
./ft_otool INCLUDES/nm_otool.h > res1 && otool -t INCLUDES/nm_otool.h > res2 && diff res1 res2

echo " "

echo "TESTS MULTI-PARAMATRES:"
echo "./ft_nm ft_otool ft_nm OBJECTS/nm.o libft/libft.a > res1 && nm ft_otool ft_nm OBJECTS/nm.o libft/libft.a > res2 && diff res1 res2"
./ft_nm ft_otool ft_nm OBJECTS/nm.o libft/libft.a > res1 && nm ft_otool ft_nm OBJECTS/nm.o libft/libft.a > res2 && diff res1 res2
echo "./ft_otool ft_otool ft_nm OBJECTS/nm.o libft/libft.a > res1 && otool -t ft_otool ft_nm OBJECTS/nm.o libft/libft.a > res2 && diff res1 res2"
./ft_otool ft_otool ft_nm OBJECTS/nm.o libft/libft.a > res1 && otool -t ft_otool ft_nm OBJECTS/nm.o libft/libft.a > res2 && diff res1 res2
