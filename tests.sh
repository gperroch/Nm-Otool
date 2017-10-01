#!/bin/bash

echo "./ft_nm ft_otool" && sleep 3
./ft_nm ft_otool > res1 && nm ft_otool > res2 && diff res1 res2
echo "./ft_nm ft_nm" && sleep 3
./ft_nm ft_nm > res1 && nm ft_nm > res2 && diff res1 res2
echo "./ft_nm exeTest" && sleep 3
./ft_nm exeTest > res1 && nm exeTest > res2 && diff res1 res2
echo "./ft_nm ft_nm.o" && sleep 3
./ft_nm nm.o > res1 && nm nm.o > res2 && diff res1 res2
echo "./ft_nm libft.a" && sleep 3
./ft_nm libft/libft.a > res1 && nm libft/libft.a > res2 && diff res1 res2


echo "./ft_otool ft_otool" && sleep 3
./ft_otool ft_otool > res1 && otool -t ft_otool > res2 && diff res1 res2
echo "./ft_otool ft_nm" && sleep 3
./ft_otool ft_nm > res1 && otool -t ft_nm > res2 && diff res1 res2
echo "./ft_otool exeTest" && sleep 3
./ft_otool exeTest > res1 && otool -t exeTest > res2 && diff res1 res2
echo "./ft_otool nm.o" && sleep 3
./ft_otool nm.o > res1 && otool -t nm.o > res2 && diff res1 res2
echo "./ft_otool libft.a" && sleep 3
./ft_otool libft/libft.a > res1 && otool -t libft/libft.a > res2 && diff res1 res2
