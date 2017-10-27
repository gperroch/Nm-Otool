#!/bin/bash

I=0
LIST=`ls -1 /usr/bin`
MAX=`ls -l /usr/bin | wc -l`
while [ "$I" -lt "$MAX" ]
do
	FILE=`ls -1 /usr/bin | sed -n "${I}p"`
	echo "Diff on $FILE ($I)"
	./ft_nm /usr/bin/$FILE > diff1
	nm /usr/bin/$FILE > diff2
	diff diff1 diff2 > DIFF/diff_$FILE
	I=$(( $I + 1 ))
done
