#!/bin/bash

var=$1
str="\/"
var=${var//\//$str}

awk -v var=$var -f p4a.awk p4Customer.txt

mkdir -p Emails
while read file email; do
	sed -f "$file" template.txt > Emails/$email
	rm $file
done < "name.txt"

rm -f name.txt