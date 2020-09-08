#! /bin/bash

num=1 # let num=1

while [ $num -le 100 ]; do
	echo $num
	let num=num+1 #num=$(($num+1))
done

# -le <=
# -lt <
# -ge >=
# -gt >
