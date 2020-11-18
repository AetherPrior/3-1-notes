#!/bin/bash
for file in *xopp;
do
	filorig=$file;
	fil=$(echo $file|rev|cut -c 6-|rev);
	xournalpp --create-pdf "${fil}.pdf" "$filorig";
done;	
if [ ! -d "./pdfs" ]
then
    mkdir pdfs; 
fi;
mv *.pdf ./pdfs;
