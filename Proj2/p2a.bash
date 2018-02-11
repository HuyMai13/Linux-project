#!/bin/bash

sed -E -f p2aDollar.sed lastlog1.out > outDollar.txt
sed -E -f p2a.sed lastlog2.out > out.txt

grep -f outDollar.txt out.txt > p2a.out
