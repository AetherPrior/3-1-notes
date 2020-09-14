#! /bin/bash
n=$1
i=1

while [ $i -le $n ];
do
	out=`./factorial $i`
	out2=`/usr/bin/time -f"%e" ./factorial $i` 
	echo $out
	echo $out2
	let i=$i+1
done
