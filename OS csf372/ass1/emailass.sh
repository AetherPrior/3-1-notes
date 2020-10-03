#!/bin/bash
read n;
declare -A names domains;
i=0;
while [[ $i -lt $n ]];
do
    read email
    if [[ "$email" =~ ^[a-zA-Z0-9_\-]+@[[a-zA-Z0-9]+\.[a-zA-Z]+$ ]];
    then
        OFS=$IFS;
        IFS='@';
        read -ra Eaddr <<< "$email";
        uname=${Eaddr[0]};
        if [[ "$uname" =~ ^.*[a-zA-Z0-9].*$ ]];
        then 
            names[$uname]=1
        fi
        IFS='.';
        read -ra pname <<< "${Eaddr[1]}";
        pname=${pname[0]};
        if [[ "$pname" =~ ^.*[a-zA-Z0-9].*$ ]];
        then
            domains[$pname]=1
        fi
        #echo "$uname $pname"
        IFS=$OFS;
    fi
    i=$(($i+1))
done
OFS=$IFS;
IFS=$'\n'
name=($(sort<<<${!names[*]}));
domain=($(sort<<<${!domains[*]}));
IFS=$OFS;
for i in ${name[*]};
do
    echo -n "$i "
done
echo ""
for i in ${domain[*]};
do
    echo -n "$i "
done