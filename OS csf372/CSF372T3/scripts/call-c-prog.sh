#!/bin/bash
out=`./hello-n $1` #$1 => arg1, $2 => arg2... 
#backticks capture the output into a variable
echo $? #return address of last executed program in shell
echo "$out" #print the output
