#!/bin/bash

echo "Enter one of the following actions or press CTRL-D to exit."
echo "C - create a customer file"
echo "P - accept a customer payment"
echo "F - find customer by apartment number"

while read input; do
	if [[ $input =~  c|C ]]; then
		bash create_action.bash
	elif [[ $input =~ p|P ]]; then
		bash payment_action.bash
	elif [[ $input =~ f|F ]]; then
		bash find_action.bash
	else
		echo "Error: invalid action value"
	fi
	echo "Enter one of the following actions or press CTRL-D to exit."
	echo "C - create a customer file"
	echo "P - accept a customer payment"
	echo "F - find customer by apartment number"
done