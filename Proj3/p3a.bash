#!/bin/bash

awk -f p3aFirst.awk unsortedNames.txt | sort | awk -f p3aLast.awk > p3a.out