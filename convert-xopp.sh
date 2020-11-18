#!/bin/bash

for file in *xopp;
do
	filorig=$file;
	fil=$(echo $file|rev|cut -c 6-|rev);
	echo $fil
	
	xournalpp --create-pdf "${fil}.pdf" "$filorig";
	echo	"xournalpp --create-pdf \"${fil}.pdf\" $filorig";

done;
	
mkdir pdfs && mv *.pdf ./pdfs;
