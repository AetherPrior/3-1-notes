#!/bin/bash
declare -A depts;
let m=0;
md=" ";
let ms=0;let fs=0;
read n;
let i=0;
IFS=$' ';
while [[ $i -lt $n ]];
    do
        read name dept age gender;
        if [[ '$gender' = 'M' ]];
            then
                ms=$(($ms+1));
            else
                fs=$(($fs+1));
        fi
        depts[$dept]=$((${depts[$dept]}+1));
        if [[ $m -lt ${depts[$dept]} ]];
            then
                m=${depts[$dept]};
                md=$dept;
        fi
        i=$(($i+1));
    done

let c=0;
for i in "${!depts[@]}";
    do 
        c=$(($c+1));
    done
echo $c
echo "$ms $fs"
echo $md
 


