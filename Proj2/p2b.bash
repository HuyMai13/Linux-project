#!/bin/bash

sed -E -f p2a.sed lastlog1.out > out1.txt
sed -E -f p2a.sed lastlog2.out > out2.txt

cat out1.txt out2.txt | sort | uniq -c | sed -E -f p2b.sed > p2b.out