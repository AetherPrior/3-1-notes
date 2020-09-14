#!/bin/bash

echo "Number of arguments of arguments passed to this script: $#" #argc
#dont use single quotes, it doesn't dereference the variable
for i in $@; do #argv
    echo $i
done
