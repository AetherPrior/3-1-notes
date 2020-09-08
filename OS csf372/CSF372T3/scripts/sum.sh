#! /bin/bash

#either chmod the script or the folder in which the script exists
# don't make +x default

# permissions work differently in different filesystems


a=5 #NO SPACES!
b=7 #it's like running something on the terminal 

c=$((a+b)) #Evaluate a+b in 2 brackets, otherwise, a+b is treated as a command
c=$(( $a+$b ))  

echo $c
echo c #prints c, double quotes not necessary
