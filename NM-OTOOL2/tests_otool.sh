./ft_otool $1 > tmp1 && otool -t $1 > tmp2 && vimdiff tmp1 tmp2
