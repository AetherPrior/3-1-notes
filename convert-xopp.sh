#!/bin/bash
for file in *xopp;
do
	xournalpp -p "$(echo $file|rev|cut -c 6-|rev).pdf" "$file";
done;	
if [ ! -d "./pdfs" ]
then
    mkdir pdfs; 
fi;
mv *.pdf ./pdfs;
