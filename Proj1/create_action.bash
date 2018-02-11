#!/bin/bash

echo "Enter email"
read email
echo "Enter full name"
read name
echo "Enter apt number"
read apt
echo "Enter monthly rent amt"
read rent
echo "Enter next due date"
read due_date

balance=0

if [ -e "$email" ]
	then
		echo "Error: customer already exists"
	else
		cd ./Data
		touch $email
		echo -e "$email $name\n$apt $rent $balance $due_date" > $email
fi