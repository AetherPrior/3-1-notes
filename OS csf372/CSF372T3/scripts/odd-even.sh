#!/bin/bash

a=6

# == for pattern matching
if [ $(($a%2)) = 0 ] #spaces before and after = for logical =
then 
	echo "even"
else
	echo "odd"
fi
